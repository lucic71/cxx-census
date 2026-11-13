#include <clang/AST/DeclTemplate.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/PrettyPrinter.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Lex/Lexer.h>

#include <map>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

PrintingPolicy policy(const ASTContext &Ctx) {
  PrintingPolicy Policy(Ctx.getLangOpts());
  Policy.SuppressInlineNamespace =
      static_cast<unsigned>(PrintingPolicy::SuppressInlineNamespaceMode::All);
  Policy.SuppressUnwrittenScope = true;
  return Policy;
}

std::string path(const NamedDecl *D);

std::string recordPath(const RecordDecl *RD) {
  std::string Name;
  llvm::raw_string_ostream OS(Name);
  const auto *Partial = dyn_cast<ClassTemplatePartialSpecializationDecl>(RD);
  if (const auto *Spec = dyn_cast<ClassTemplateSpecializationDecl>(RD)) {
    if (!Partial) {
      if (const auto *From =
              Spec->getSpecializedTemplateOrPartial()
                  .dyn_cast<ClassTemplatePartialSpecializationDecl *>())
        return recordPath(From);
      return path(Spec->getSpecializedTemplate());
    }
    OS << path(Spec->getSpecializedTemplate());
  } else if (const auto *Outer = dyn_cast<RecordDecl>(RD->getDeclContext())) {
    OS << recordPath(Outer) << "::" << RD->getName();
    return Name;
  } else {
    RD->printQualifiedName(OS, policy(RD->getASTContext()));
    return Name;
  }
  std::string Args;
  llvm::raw_string_ostream AOS(Args);
  for (const TemplateArgumentLoc &Arg :
       Partial->getTemplateArgsAsWritten()->arguments()) {
    if (Arg.getArgument().isDependent())
      continue;
    AOS << (Args.empty() ? "" : ", ");
    Arg.getArgument().print(policy(RD->getASTContext()), AOS, true);
  }
  if (!Args.empty())
    OS << "<" << Args << ">";
  return Name;
}

std::string memberPath(const RecordDecl *RD, const NamedDecl *Member) {
  if (isa<CXXConstructorDecl>(Member))
    return recordPath(RD) + "::" + RD->getNameAsString();
  std::string Name;
  llvm::raw_string_ostream OS(Name);
  Member->printName(OS, policy(RD->getASTContext()));
  return recordPath(RD) + "::" + Name;
}

std::string path(const NamedDecl *D) {
  if (const auto *RD = dyn_cast<RecordDecl>(D))
    return recordPath(RD);
  if (const auto *RD = dyn_cast<RecordDecl>(D->getDeclContext()))
    return memberPath(RD, D);
  std::string Name;
  llvm::raw_string_ostream OS(Name);
  D->printQualifiedName(OS, policy(D->getASTContext()));
  return Name;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }
  bool shouldVisitImplicitCode() const { return true; }

  bool TraverseDecl(Decl *D) {
    if (D && !isa<TranslationUnitDecl>(D) &&
        SM.isInSystemHeader(D->getLocation()))
      return true;
    return RecursiveASTVisitor::TraverseDecl(D);
  }

  bool VisitTypeLoc(TypeLoc TL) {
    QualType T = TL.getType();
    if (const auto *TT = T->getAs<TypedefType>())
      add(TT->getDecl(), TL.getBeginLoc());
    else if (const TagDecl *Tag = T->getAsTagDecl())
      add(Tag, TL.getBeginLoc());
    return true;
  }

  bool VisitDeclRefExpr(DeclRefExpr *E) {
    if (const auto *FD = dyn_cast<FunctionDecl>(E->getDecl());
        FD && FD->isOverloadedOperator() && !isa<CXXMethodDecl>(FD))
      return true;
    add(E->getDecl(), E->getLocation());
    return true;
  }

  bool VisitCXXOperatorCallExpr(CXXOperatorCallExpr *E) {
    const auto *FD = dyn_cast_or_null<FunctionDecl>(E->getCalleeDecl());
    if (!FD || isa<CXXMethodDecl>(FD) || !IsInSystemHeader(FD))
      return true;
    for (const Expr *Arg : E->arguments()) {
      const RecordDecl *RD =
          Arg->IgnoreParenImpCasts()->getType()->getAsRecordDecl();
      if (RD && IsInSystemHeader(RD)) {
        add(memberPath(RD, FD), E->getOperatorLoc());
        return true;
      }
    }
    add(FD, E->getOperatorLoc());
    return true;
  }

  bool VisitMemberExpr(MemberExpr *E) {
    SourceLocation Loc =
        E->getMemberLoc().isValid() ? E->getMemberLoc() : E->getBeginLoc();
    const ValueDecl *Member = E->getMemberDecl();
    const auto *Owner = dyn_cast<RecordDecl>(Member->getDeclContext());
    QualType Object = E->getBase()->IgnoreParenImpCasts()->getType();
    if (E->isArrow())
      Object = Object->getPointeeType();
    const RecordDecl *RD = Object->getAsRecordDecl();
    if (Owner && RD && RD != Owner && Owner->getName().starts_with("_") &&
        IsInSystemHeader(RD))
      add(memberPath(RD, Member), Loc);
    else
      add(Member, Loc);
    return true;
  }

  bool VisitCXXStdInitializerListExpr(CXXStdInitializerListExpr *E) {
    if (const RecordDecl *RD = E->getType()->getAsRecordDecl())
      add(path(RD) + "::{}", E->getBeginLoc());
    return true;
  }

  bool VisitCXXConstructExpr(CXXConstructExpr *E) {
    add(E->getConstructor(), E->getBeginLoc());
    return true;
  }

  bool VisitInitListExpr(InitListExpr *E) {
    if (const RecordDecl *RD = E->getType()->getAsRecordDecl();
        RD && IsInSystemHeader(RD))
      add(path(RD) + "::{}", E->getBeginLoc());
    return true;
  }

  bool VisitIntegerLiteral(IntegerLiteral *E) {
    SourceLocation Loc = E->getBeginLoc();
    if (Loc.isMacroID() && SM.isInSystemMacro(Loc))
      add(Lexer::getImmediateMacroName(Loc, SM, Ctx.getLangOpts()).str(), Loc);
    return true;
  }

  void emit() {
    for (const auto &[Key, Loc] : Keys)
      report(Ctx, "stl-usage", Loc, Key);
  }

private:
  void add(const NamedDecl *D, SourceLocation Loc) {
    if (D && IsInSystemHeader(D))
      add(path(D), Loc);
  }

  void add(const std::string &Key, SourceLocation Loc) {
    if (!Key.empty() && !SM.isInSystemHeader(SM.getExpansionLoc(Loc)))
      Keys.try_emplace(Key, Loc);
  }

  ASTContext &Ctx;
  const SourceManager &SM;
  std::map<std::string, SourceLocation> Keys;
};

} // namespace

void Filters::HasStlUsage(ASTContext &Ctx) {
  Visitor V(Ctx);
  V.TraverseDecl(Ctx.getTranslationUnitDecl());
  V.emit();
}

} // namespace census

#include <clang/AST/DeclTemplate.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool hasDataMembers(const CXXRecordDecl *RD) {
  RD = RD->getDefinition();
  if (!RD)
    return false;
  if (!RD->field_empty())
    return true;
  for (const CXXBaseSpecifier &B : RD->bases())
    if (const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl())
      if (hasDataMembers(Base))
        return true;
  return false;
}

bool isEmptyBase(const CXXRecordDecl *RD) {
  if (!RD->isEmpty() || RD->getNumBases() != 0)
    return false;
  for (const CXXMethodDecl *M : RD->methods())
    if (!M->isImplicit())
      return false;
  return true;
}

bool isTagBase(const CXXRecordDecl *RD) {
  const auto *Spec = dyn_cast<ClassTemplateSpecializationDecl>(RD);
  if (!Spec)
    return false;
  StringRef Name = Spec->getSpecializedTemplate()->getName();
  return (Name == "integral_constant" || Name == "bool_constant") &&
         IsInSystemHeader(RD);
}

std::string baseIssues(const CXXBaseSpecifier &B) {
  const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl();
  if (!Base || !Base->getDefinition())
    return "";
  Base = Base->getDefinition();
  if (isEmptyBase(Base) || isTagBase(Base))
    return "";

  std::string Issues;
  auto Add = [&](StringRef Issue) { Issues += " " + Issue.str(); };

  if (B.isVirtual())
    Add("virtual-base");
  if (B.getAccessSpecifier() != AS_public)
    Add("non-public-base");
  if (!Base->isAbstract())
    Add("non-abstract-base");
  if (hasDataMembers(Base))
    Add("data-members");

  bool DefaultMethod = false, ConcreteMethod = false, Ctor = false,
       Dtor = false;
  for (const CXXMethodDecl *M : Base->methods()) {
    if (M->isImplicit())
      continue;
    if (isa<CXXDestructorDecl>(M)) {
      Dtor |= M->isUserProvided();
      continue;
    }
    if (isa<CXXConstructorDecl>(M)) {
      Ctor |= M->isUserProvided();
      continue;
    }
    if (M->isVirtual()) {
      const FunctionDecl *Def = nullptr;
      DefaultMethod |= !M->isPureVirtual() && M->isDefined(Def);
    } else if (!M->isStatic()) {
      ConcreteMethod = true;
    }
  }
  if (DefaultMethod)
    Add("default-method");
  if (ConcreteMethod)
    Add("concrete-method");
  if (Ctor)
    Add("constructor");
  if (Dtor)
    Add("destructor");
  return Issues;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXRecordDecl(CXXRecordDecl *D) {
    if (!D->isThisDeclarationADefinition() || D->isDependentContext() ||
        D->getNumBases() == 0 || IsInSystemHeader(D))
      return true;

    std::string Detail;
    for (const CXXBaseSpecifier &B : D->bases()) {
      std::string Issues = baseIssues(B);
      if (!Issues.empty())
        Detail += " [" + B.getType().getAsString() + ":" + Issues + "]";
    }
    if (D->getNumBases() > 1)
      Detail += " [multiple-bases]";
    if (!Detail.empty())
      report(Ctx, "inheritance", D->getLocation(),
             D->getQualifiedNameAsString() + " :" + Detail);
    return true;
  }

  bool VisitMemberExpr(MemberExpr *E) {
    MemberBases.insert(E->getBase()->IgnoreParens());
    return true;
  }

  bool VisitCastExpr(CastExpr *E) {
    if ((E->getCastKind() != CK_DerivedToBase &&
         E->getCastKind() != CK_UncheckedDerivedToBase) ||
        MemberBases.count(E))
      return true;
    QualType From = E->getSubExpr()->getType();
    if (From->isPointerType())
      From = From->getPointeeType();
    const CXXRecordDecl *Derived = From->getAsCXXRecordDecl();
    if (!Derived || IsInSystemHeader(Derived))
      return true;
    std::string Detail;
    for (const CXXBaseSpecifier *B : E->path()) {
      const CXXRecordDecl *Base = B->getType()->getAsCXXRecordDecl();
      Base = Base ? Base->getDefinition() : nullptr;
      if (!Base || (Base->isAbstract() && !hasDataMembers(Base)))
        continue;
      std::string Issues = baseIssues(*B);
      if (!Issues.empty())
        Detail += " [" + B->getType().getAsString() + ":" + Issues + "]";
    }
    if (!Detail.empty())
      reportExpr("upcast", E->getBeginLoc(),
                 E->getSubExpr()->getType().getAsString() + " ->" + Detail);
    return true;
  }

  bool VisitCXXDynamicCastExpr(CXXDynamicCastExpr *E) {
    reportExpr("dynamic_cast", E->getBeginLoc(),
               E->getTypeAsWritten().getAsString());
    return true;
  }

  bool VisitCXXTypeidExpr(CXXTypeidExpr *E) {
    if (!E->isPotentiallyEvaluated())
      return true;
    reportExpr("typeid", E->getBeginLoc(),
               E->isTypeOperand()
                   ? E->getTypeOperand(Ctx).getAsString()
                   : E->getExprOperand()->getType().getAsString());
    return true;
  }

private:
  void reportExpr(StringRef What, SourceLocation Loc, StringRef Type) {
    SourceLocation Exp = SM.getExpansionLoc(Loc);
    if (SM.isInSystemHeader(Exp))
      return;
    report(Ctx, "inheritance", Loc, What.str() + " " + Type.str());
  }

  llvm::SmallPtrSet<const Expr *, 16> MemberBases;
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasInheritance(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

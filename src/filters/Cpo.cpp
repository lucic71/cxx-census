#include <clang/AST/DeclCXX.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

bool inStd(const Decl *D) {
  const DeclContext *DC = D->getDeclContext();
  const NamespaceDecl *Top = nullptr;
  for (; DC; DC = DC->getParent())
    if (const auto *NS = dyn_cast<NamespaceDecl>(DC))
      Top = NS;
  return Top && Top->getName() == "std";
}

bool hasCallOperator(const CXXRecordDecl *RD) {
  RD = RD ? RD->getDefinition() : nullptr;
  if (!RD)
    return false;
  DeclarationName Call =
      RD->getASTContext().DeclarationNames.getCXXOperatorName(OO_Call);
  if (!RD->lookup(Call).empty())
    return true;
  for (const CXXBaseSpecifier &B : RD->bases())
    if (hasCallOperator(B.getType()->getAsCXXRecordDecl()))
      return true;
  return false;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitDeclRefExpr(DeclRefExpr *E) {
    const auto *V = dyn_cast<VarDecl>(E->getDecl());
    if (!V || !V->isConstexpr() || !inStd(V) ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getLocation())))
      return true;
    if (!hasCallOperator(V->getType()->getAsCXXRecordDecl()))
      return true;
    std::string Name;
    llvm::raw_string_ostream OS(Name);
    PrintingPolicy Policy(Ctx.getLangOpts());
    Policy.SuppressInlineNamespace =
        static_cast<unsigned>(PrintingPolicy::SuppressInlineNamespaceMode::All);
    V->printQualifiedName(OS, Policy);
    report(Ctx, "cpo", E->getLocation(), Name);
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasCpo(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

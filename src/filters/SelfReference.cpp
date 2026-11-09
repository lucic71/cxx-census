#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool references(const Stmt *S, const VarDecl *D) {
  if (!S)
    return false;
  if (const auto *Ref = dyn_cast<DeclRefExpr>(S))
    return Ref->getDecl()->getCanonicalDecl() == D->getCanonicalDecl();
  for (const Stmt *Child : S->children())
    if (references(Child, D))
      return true;
  return false;
}

bool usesThis(const Stmt *S) {
  if (!S)
    return false;
  if (isa<CXXThisExpr>(S))
    return true;
  for (const Stmt *Child : S->children())
    if (usesThis(Child))
      return true;
  return false;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitVarDecl(VarDecl *D) {
    if (!D->hasInit() || D->getType()->isDependentType() ||
        IsInSystemHeader(D) || !references(D->getInit(), D))
      return true;
    StringRef Kind = D->getType()->isReferenceType()              ? "reference"
                     : D->isLocalVarDecl() && !D->isStaticLocal() ? "variable"
                                                                  : "static";
    report(Ctx, "self-reference", D->getLocation(),
           Kind.str() + " " + D->getQualifiedNameAsString() +
               " initialized with itself");
    return true;
  }

  bool VisitCXXConstructorDecl(CXXConstructorDecl *D) {
    if (!D->isThisDeclarationADefinition() || D->isDependentContext() ||
        IsInSystemHeader(D))
      return true;
    for (const CXXCtorInitializer *Init : D->inits())
      if (Init->isWritten() && usesThis(Init->getInit()))
        report(Ctx, "self-reference", Init->getSourceLocation(),
               D->getParent()->getQualifiedNameAsString() +
                   " passes this in a member initializer");
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasSelfReference(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

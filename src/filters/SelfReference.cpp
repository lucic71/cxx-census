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

void selfUses(const Stmt *S, std::string &Uses) {
  if (!S)
    return;
  if (const auto *M = dyn_cast<MemberExpr>(S);
      M && isa<CXXThisExpr>(M->getBase()->IgnoreParenImpCasts())) {
    Uses += isa<CXXMethodDecl>(M->getMemberDecl()) ? " calls " : " reads ";
    Uses += M->getMemberDecl()->getNameAsString();
    for (const Stmt *Child : S->children())
      if (Child != M->getBase())
        selfUses(Child, Uses);
    return;
  }
  if (isa<CXXThisExpr>(S)) {
    Uses += " this";
    return;
  }
  for (const Stmt *Child : S->children())
    selfUses(Child, Uses);
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
    for (const CXXCtorInitializer *Init : D->inits()) {
      if (!Init->isWritten())
        continue;
      std::string Uses;
      selfUses(Init->getInit(), Uses);
      if (!Uses.empty())
        report(Ctx, "self-reference", Init->getSourceLocation(),
               D->getParent()->getQualifiedNameAsString() +
                   " member initializer" + Uses);
    }
    return true;
  }

  bool VisitFieldDecl(FieldDecl *D) {
    if (!D->hasInClassInitializer() || D->getParent()->isDependentContext() ||
        IsInSystemHeader(D))
      return true;
    std::string Uses;
    selfUses(D->getInClassInitializer(), Uses);
    if (!Uses.empty())
      report(Ctx, "self-reference", D->getLocation(),
             D->getQualifiedNameAsString() + " default initializer" + Uses);
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

#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

bool isNothrow(const Expr *E) {
  const CXXRecordDecl *RD = E->getType()->getAsCXXRecordDecl();
  return RD && RD->getName() == "nothrow_t";
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXNewExpr(CXXNewExpr *E) {
    if (E->getNumPlacementArgs() == 0 ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    bool Nothrow =
        E->getNumPlacementArgs() == 1 && isNothrow(E->getPlacementArg(0));
    report(Ctx, "placement-new", E->getBeginLoc(),
           std::string(Nothrow ? "nothrow-new " : "placement-new ") +
               E->getAllocatedType().getAsString() +
               (E->isArray() ? "[]" : ""));
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasPlacementNew(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

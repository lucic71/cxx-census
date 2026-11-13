#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitFunctionDecl(FunctionDecl *D) {
    switch (D->getOverloadedOperator()) {
    case OO_New:
    case OO_Delete:
    case OO_Array_New:
    case OO_Array_Delete:
      break;
    default:
      return true;
    }
    if (D->isImplicit() || IsInSystemHeader(D) || !D->isFirstDecl())
      return true;
    const auto *M = dyn_cast<CXXMethodDecl>(D);
    report(Ctx, "operator-new", D->getLocation(),
           (M ? M->getParent()->getQualifiedNameAsString() + "::"
              : std::string("::")) +
               D->getNameAsString());
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasOperatorNew(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

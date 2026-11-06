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

  bool VisitCXXConstructorDecl(CXXConstructorDecl *D) {
    if (D->isDependentContext() || D != D->getCanonicalDecl())
      return true;
    if (!IsUserDefinedDecl(D))
      return true;

    unsigned Quals = 0;
    if (!D->isCopyConstructor(Quals) || (Quals & Qualifiers::Const))
      return true;

    std::string Detail = D->getParent()->getQualifiedNameAsString() + "(" +
                         D->getParamDecl(0)->getType().getAsString() + ")";
    if (D->isDeleted())
      Detail += " = delete";
    else if (D->isExplicitlyDefaulted())
      Detail += " = default";
    report(Ctx, "non-const-copy-constructor", D->getLocation(), Detail);
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Criteria::HasNonConstCopyConstructor(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

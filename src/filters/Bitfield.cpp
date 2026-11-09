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

  bool VisitFieldDecl(FieldDecl *D) {
    if (!D->isBitField() || D->getParent()->isDependentContext() ||
        IsInSystemHeader(D))
      return true;
    std::string Width = D->getBitWidth()->isValueDependent()
                            ? "?"
                            : std::to_string(D->getBitWidthValue());
    report(Ctx, "bitfield", D->getLocation(),
           D->getQualifiedNameAsString() + " : " + D->getType().getAsString() +
               " : " + Width);
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasBitfield(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

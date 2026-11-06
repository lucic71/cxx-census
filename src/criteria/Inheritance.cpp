#include "Census.h"

#include "clang/AST/RecursiveASTVisitor.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXRecordDecl(CXXRecordDecl *D) {
    if (!D->isThisDeclarationADefinition() || D->isDependentContext() ||
        D->getNumBases() == 0)
      return true;
    if (Ctx.getSourceManager().isInSystemHeader(D->getLocation()))
      return true;

    std::string Detail = D->getQualifiedNameAsString() + " :";
    for (const CXXBaseSpecifier &B : D->bases())
      Detail += " " + B.getType().getAsString();
    report(Ctx, "inheritance", D->getLocation(), Detail);
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Criteria::HasInheritance(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

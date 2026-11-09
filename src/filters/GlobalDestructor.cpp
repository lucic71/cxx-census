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

  bool VisitVarDecl(VarDecl *D) {
    if (!D->hasGlobalStorage() || D->getType()->isDependentType() ||
        D->isThisDeclarationADefinition() != VarDecl::Definition ||
        IsInSystemHeader(D))
      return true;
    const CXXRecordDecl *RD =
        Ctx.getBaseElementType(D->getType())->getAsCXXRecordDecl();
    if (!RD || !RD->hasDefinition() || RD->hasTrivialDestructor())
      return true;
    StringRef Kind = D->isStaticLocal()        ? "static-local"
                     : D->isStaticDataMember() ? "static-member"
                                               : "global";
    report(Ctx, "global-destructor", D->getLocation(),
           Kind.str() + " " + D->getQualifiedNameAsString() + " : " +
               D->getType().getAsString());
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasGlobalDestructor(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

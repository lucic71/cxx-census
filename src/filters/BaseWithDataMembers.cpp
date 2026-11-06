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

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXRecordDecl(CXXRecordDecl *D) {
    if (!D->isThisDeclarationADefinition() || D->isDependentContext())
      return true;
    if (!IsUserDefinedDecl(D))
      return true;

    std::string Bases;
    for (const CXXBaseSpecifier &B : D->bases()) {
      const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl();
      if (Base && hasDataMembers(Base))
        Bases += " " + B.getType().getAsString();
    }
    if (!Bases.empty())
      report(Ctx, "base-with-data-members", D->getLocation(),
             D->getQualifiedNameAsString() + " :" + Bases);
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasBaseWithDataMembers(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

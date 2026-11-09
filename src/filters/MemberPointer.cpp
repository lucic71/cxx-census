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

  bool VisitDeclaratorDecl(DeclaratorDecl *D) {
    if (!isa<VarDecl, FieldDecl>(D) || D->getType()->isDependentType() ||
        IsInSystemHeader(D))
      return true;
    if (const auto *FD = dyn_cast<FunctionDecl>(D->getDeclContext());
        FD && FD->isTemplateInstantiation())
      return true;
    QualType T = Ctx.getBaseElementType(D->getType()).getNonReferenceType();
    if (!T->isMemberPointerType())
      return true;
    StringRef Kind = isa<FieldDecl>(D)     ? "field"
                     : isa<ParmVarDecl>(D) ? "parameter"
                                           : "variable";
    report(Ctx, "member-pointer", D->getLocation(),
           Kind.str() + " " + D->getQualifiedNameAsString() + " : " +
               T.getAsString());
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasMemberPointer(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

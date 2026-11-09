#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/SmallPtrSet.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool hasUserDestructor(const CXXRecordDecl *RD,
                       llvm::SmallPtrSetImpl<const CXXRecordDecl *> &Seen) {
  RD = RD ? RD->getDefinition() : nullptr;
  if (!RD || IsInSystemHeader(RD) || !Seen.insert(RD).second)
    return false;
  if (const CXXDestructorDecl *D = RD->getDestructor();
      D && D->isUserProvided())
    return true;
  for (const FieldDecl *F : RD->fields())
    if (hasUserDestructor(RD->getASTContext()
                              .getBaseElementType(F->getType())
                              ->getAsCXXRecordDecl(),
                          Seen))
      return true;
  for (const CXXBaseSpecifier &B : RD->bases())
    if (hasUserDestructor(B.getType()->getAsCXXRecordDecl(), Seen))
      return true;
  return false;
}

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
    llvm::SmallPtrSet<const CXXRecordDecl *, 8> Seen;
    if (!hasUserDestructor(RD, Seen))
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

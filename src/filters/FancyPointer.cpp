#include <clang/AST/DeclTemplate.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

const TypedefNameDecl *member(const CXXRecordDecl *RD, StringRef Name) {
  for (const NamedDecl *D : RD->lookup(&RD->getASTContext().Idents.get(Name)))
    if (const auto *T = dyn_cast<TypedefNameDecl>(D))
      return T;
  return nullptr;
}

bool hasMethod(const CXXRecordDecl *RD, StringRef Name) {
  return !RD->lookup(&RD->getASTContext().Idents.get(Name)).empty();
}

bool isFancy(const TypedefNameDecl *P) {
  if (!P)
    return false;
  QualType T = P->getUnderlyingType();
  return !T->isPointerType() && !T->isVoidType() && !T->isNullPtrType();
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXRecordDecl(CXXRecordDecl *D) {
    if (!D->isThisDeclarationADefinition() ||
        isa<ClassTemplateSpecializationDecl>(D) || IsInSystemHeader(D) ||
        !hasMethod(D, "allocate"))
      return true;
    if (const TypedefNameDecl *P = member(D, "pointer"); isFancy(P))
      report(Ctx, "fancy-pointer", D->getLocation(),
             "allocator " + D->getQualifiedNameAsString() + " pointer " +
                 P->getUnderlyingType().getAsString());
    return true;
  }

  bool VisitDeclaratorDecl(DeclaratorDecl *D) {
    if (!isa<VarDecl>(D) && !isa<FieldDecl>(D))
      return true;
    QualType T = D->getType().getNonReferenceType();
    if (T->isDependentType() || IsInSystemHeader(D))
      return true;
    const auto *Spec = dyn_cast_or_null<ClassTemplateSpecializationDecl>(
        T->getAsCXXRecordDecl());
    if (!Spec || !Spec->isInStdNamespace() || !Spec->hasDefinition())
      return true;
    Spec = cast<ClassTemplateSpecializationDecl>(Spec->getDefinition());
    if (Spec->getName() != "unique_ptr" && !member(Spec, "allocator_type"))
      return true;
    if (const TypedefNameDecl *P = member(Spec, "pointer"); isFancy(P))
      report(Ctx, "fancy-pointer", D->getLocation(),
             D->getNameAsString() + " " + T.getAsString() + " pointer " +
                 P->getUnderlyingType().getCanonicalType().getAsString());
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasFancyPointer(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

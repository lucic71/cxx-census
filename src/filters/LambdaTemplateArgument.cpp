#include <clang/AST/DeclTemplate.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool hasClosureArgument(QualType T) {
  const auto *RD = T->getAsCXXRecordDecl();
  const auto *Spec = dyn_cast_or_null<ClassTemplateSpecializationDecl>(RD);
  if (!Spec || !Spec->isInStdNamespace())
    return false;
  for (const TemplateArgument &A : Spec->getTemplateArgs().asArray()) {
    if (A.getKind() != TemplateArgument::Type)
      continue;
    const auto *Arg = A.getAsType()->getAsCXXRecordDecl();
    if ((Arg && Arg->isLambda()) || hasClosureArgument(A.getAsType()))
      return true;
  }
  return false;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitDeclaratorDecl(DeclaratorDecl *D) {
    if (!isa<VarDecl>(D) && !isa<FieldDecl>(D))
      return true;
    if (D->getType()->isDependentType() || IsInSystemHeader(D))
      return true;
    QualType T = D->getType().getNonReferenceType();
    if (hasClosureArgument(T))
      report(Ctx, "lambda-template-argument", D->getLocation(),
             D->getNameAsString() + " " + T.getAsString());
    return true;
  }

private:
  ASTContext &Ctx;
};

} // namespace

void Filters::HasLambdaTemplateArgument(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

#include <clang/AST/DeclTemplate.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

bool isEmptyStdArray(QualType T) {
  const auto *Spec = dyn_cast_or_null<ClassTemplateSpecializationDecl>(
      T->getAsCXXRecordDecl());
  if (!Spec || !Spec->isInStdNamespace() || Spec->getName() != "array")
    return false;
  const TemplateArgumentList &Args = Spec->getTemplateArgs();
  return Args.size() == 2 && Args[1].getKind() == TemplateArgument::Integral &&
         Args[1].getAsIntegral() == 0;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitTemplateSpecializationTypeLoc(TemplateSpecializationTypeLoc TL) {
    QualType T = TL.getType();
    if (T->isDependentType() || !isEmptyStdArray(T) ||
        SM.isInSystemHeader(SM.getExpansionLoc(TL.getBeginLoc())))
      return true;
    report(Ctx, "empty-array", TL.getBeginLoc(),
           T.getCanonicalType().getAsString());
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasEmptyArray(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

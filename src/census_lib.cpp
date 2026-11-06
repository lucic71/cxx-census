#include "census_lib.h"

#include <clang/AST/ASTContext.h>
#include <clang/AST/DeclTemplate.h>
#include <clang/Basic/SourceManager.h>
#include <llvm/ADT/STLExtras.h>

using namespace clang;

namespace census {

bool IsUserDefinedDecl(const Decl *D) {
  const SourceManager &SM = D->getASTContext().getSourceManager();
  auto UseDefinition = [&](auto *Redeclarable, const Decl *Definition) {
    if (Definition) {
      D = Definition;
      return true;
    }
    return llvm::none_of(Redeclarable->redecls(), [&](auto *Redecl) {
      return SM.isInSystemHeader(Redecl->getLocation());
    });
  };

  if (const auto *FD = dyn_cast<FunctionDecl>(D)) {
    const FunctionDecl *Definition = nullptr;
    FD->isDefined(Definition);
    if (!UseDefinition(FD, Definition))
      return false;
  } else if (const auto *VD = dyn_cast<VarDecl>(D)) {
    if (!UseDefinition(VD, VD->getDefinition()))
      return false;
  } else if (const auto *TD = dyn_cast<TagDecl>(D)) {
    if (!UseDefinition(TD, TD->getDefinition()))
      return false;
  }

  SourceLocation Loc = D->getLocation();
  if (const auto *Spec = dyn_cast<ClassTemplateSpecializationDecl>(D);
      Spec &&
      (Spec->getSpecializationKind() == TSK_ExplicitInstantiationDeclaration ||
       Spec->getSpecializationKind() == TSK_ExplicitInstantiationDefinition))
    Loc = Spec->getSpecializedTemplate()->getLocation();

  return D->getBeginLoc().isValid() && !D->isImplicit() &&
         !SM.isInSystemHeader(Loc) && !SM.isInSystemMacro(Loc);
}

} // namespace census

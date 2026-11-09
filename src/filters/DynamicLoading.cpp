#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/StringSet.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

const llvm::StringSet<> Functions = {
    "dlopen",         "dlmopen",        "dlsym",        "dlvsym",
    "dlclose",        "dlerror",        "dladdr",       "dladdr1",
    "dlinfo",         "LoadLibraryA",   "LoadLibraryW", "LoadLibraryExA",
    "LoadLibraryExW", "GetProcAddress", "FreeLibrary",
};

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCallExpr(CallExpr *E) {
    const FunctionDecl *FD = E->getDirectCallee();
    if (!FD || !FD->getDeclName().isIdentifier() ||
        !Functions.contains(FD->getName()) ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    report(Ctx, "dynamic-loading", E->getBeginLoc(),
           "call " + FD->getName().str());
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasDynamicLoading(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

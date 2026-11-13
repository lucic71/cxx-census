#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/StringSet.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

const llvm::StringSet<> NonLocalJumps = {
    "setjmp",      "_setjmp",    "__setjmp",   "sigsetjmp",  "__sigsetjmp",
    "longjmp",     "_longjmp",   "__longjmp",  "siglongjmp", "__longjmp_chk",
    "getcontext",  "setcontext", "makecontext", "swapcontext", "vfork",
    "__builtin_setjmp", "__builtin_longjmp", "kernel_setjmp", "kernel_longjmp"};

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCallExpr(CallExpr *E) {
    const FunctionDecl *FD = E->getDirectCallee();
    if (!FD || SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    StringRef Name = FD->getDeclName().isIdentifier() ? FD->getName() : "";
    if (FD->hasAttr<ReturnsTwiceAttr>() || NonLocalJumps.contains(Name))
      report(Ctx, "setjmp", E->getBeginLoc(),
             Name.empty() ? FD->getNameAsString() : Name.str());
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasSetjmp(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

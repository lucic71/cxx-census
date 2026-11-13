#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/StringSet.h>
#include <llvm/Support/Path.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

const llvm::StringSet<> Headers = {"termios.h", "curses.h",  "ncurses.h",
                                   "term.h",    "termcap.h", "panel.h",
                                   "menu.h",    "form.h"};

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCallExpr(CallExpr *E) {
    const FunctionDecl *FD = E->getDirectCallee();
    if (!FD || !FD->getDeclName().isIdentifier() ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    SourceLocation Decl = SM.getExpansionLoc(FD->getLocation());
    if (!SM.isInSystemHeader(Decl))
      return true;
    StringRef Header = llvm::sys::path::filename(SM.getFilename(Decl));
    if (Headers.contains(Header))
      report(Ctx, "terminal", E->getBeginLoc(),
             "call " + FD->getName().str() + " " + Header.str());
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasTerminal(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

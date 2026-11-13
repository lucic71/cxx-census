#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/StmtCXX.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCoawaitExpr(CoawaitExpr *E) { return add(E, "co_await"); }
  bool VisitCoyieldExpr(CoyieldExpr *E) { return add(E, "co_yield"); }
  bool VisitCoreturnStmt(CoreturnStmt *S) { return add(S, "co_return"); }

private:
  bool add(const Stmt *S, StringRef What) {
    if (!S->getBeginLoc().isValid() ||
        SM.isInSystemHeader(SM.getExpansionLoc(S->getBeginLoc())))
      return true;
    report(Ctx, "coroutines", S->getBeginLoc(), What);
    return true;
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasCoroutines(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

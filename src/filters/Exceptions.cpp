#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/StmtCXX.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXThrowExpr(CXXThrowExpr *E) {
    const Expr *Sub = E->getSubExpr();
    reportStmt(E->getBeginLoc(),
               Sub ? "throw " + Sub->getType().getAsString() : "rethrow");
    return true;
  }

  bool VisitCXXTryStmt(CXXTryStmt *S) {
    std::string Detail = "try";
    for (unsigned I = 0; I < S->getNumHandlers(); ++I) {
      const CXXCatchStmt *H = S->getHandler(I);
      Detail += H->getExceptionDecl()
                    ? " catch " + H->getCaughtType().getAsString()
                    : " catch ...";
    }
    reportStmt(S->getBeginLoc(), Detail);
    return true;
  }

private:
  void reportStmt(SourceLocation Loc, StringRef Detail) {
    if (SM.isInSystemHeader(SM.getExpansionLoc(Loc)))
      return;
    report(Ctx, "exceptions", Loc, Detail);
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasExceptions(ASTContext &Ctx) {
  const SourceManager &SM = Ctx.getSourceManager();
  report(Ctx, "exceptions", SM.getLocForStartOfFile(SM.getMainFileID()),
         Ctx.getLangOpts().CXXExceptions ? "exceptions-enabled"
                                         : "exceptions-disabled");
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

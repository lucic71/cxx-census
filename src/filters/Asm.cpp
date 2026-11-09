#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitGCCAsmStmt(GCCAsmStmt *S) {
    reportLoc(S->getBeginLoc(), "asm " + S->getAsmString());
    return true;
  }

  bool VisitMSAsmStmt(MSAsmStmt *S) {
    reportLoc(S->getBeginLoc(), "asm " + S->getAsmString().str());
    return true;
  }

private:
  void reportLoc(SourceLocation Loc, StringRef Detail) {
    if (!SM.isInSystemHeader(SM.getExpansionLoc(Loc)))
      report(Ctx, "asm", Loc, Detail);
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasAsm(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

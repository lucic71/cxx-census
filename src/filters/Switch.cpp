#include <clang/AST/ParentMapContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

const Stmt *unwrapLabels(const Stmt *S) {
  while (const auto *L = dyn_cast<LabelStmt>(S))
    S = L->getSubStmt();
  return S;
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitSwitchStmt(SwitchStmt *S) {
    if (SM.isInSystemHeader(SM.getExpansionLoc(S->getBeginLoc())))
      return true;
    const auto *Body = dyn_cast_or_null<CompoundStmt>(S->getBody());
    if (!Body) {
      report(Ctx, "switch", S->getBeginLoc(), "body-not-block");
      return true;
    }
    for (const Stmt *Child : Body->body()) {
      if (isa<SwitchCase>(unwrapLabels(Child)))
        break;
      report(Ctx, "switch", Child->getBeginLoc(), "statement-before-case");
    }
    for (const SwitchCase *C = S->getSwitchCaseList(); C;
         C = C->getNextSwitchCase())
      if (!atTop(C, Body))
        report(Ctx, "switch", C->getBeginLoc(), "nested-case");
    return true;
  }

private:
  bool atTop(const Stmt *S, const CompoundStmt *Body) {
    while (true) {
      auto Parents = Ctx.getParents(*S);
      const Stmt *P = Parents.empty() ? nullptr : Parents[0].get<Stmt>();
      if (!P)
        return false;
      if (P == Body)
        return true;
      if (!isa<SwitchCase>(P) && !isa<LabelStmt>(P))
        return false;
      S = P;
    }
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasSwitch(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

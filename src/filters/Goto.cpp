#include <clang/AST/ParentMapContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitGotoStmt(GotoStmt *S) {
    if (inSystemHeader(S->getBeginLoc()))
      return true;
    const LabelStmt *L = S->getLabel()->getStmt();
    if (!L) {
      report(Ctx, "goto", S->getBeginLoc(), "no-label");
      return true;
    }
    const Stmt *Top = L;
    while (const auto *P = parent<LabelStmt>(Top))
      Top = P;
    const auto *Block = parent<CompoundStmt>(Top);
    if (!Block)
      report(Ctx, "goto", S->getBeginLoc(),
             "label-not-in-block " + std::string(L->getName()));
    else if (!encloses(Block, S))
      report(Ctx, "goto", S->getBeginLoc(),
             "jump-into-block " + std::string(L->getName()));
    return true;
  }

  bool VisitIndirectGotoStmt(IndirectGotoStmt *S) {
    if (!inSystemHeader(S->getBeginLoc()))
      report(Ctx, "goto", S->getBeginLoc(), "computed-goto");
    return true;
  }

  bool VisitAddrLabelExpr(AddrLabelExpr *E) {
    if (!inSystemHeader(E->getBeginLoc()))
      report(Ctx, "goto", E->getBeginLoc(),
             "label-address " + E->getLabel()->getName().str());
    return true;
  }

private:
  bool inSystemHeader(SourceLocation Loc) const {
    return SM.isInSystemHeader(SM.getExpansionLoc(Loc));
  }

  template <typename T> const T *parent(const Stmt *S) {
    auto Parents = Ctx.getParents(*S);
    return Parents.empty() ? nullptr : Parents[0].get<T>();
  }

  bool encloses(const Stmt *Outer, const Stmt *S) {
    while (true) {
      auto Parents = Ctx.getParents(*S);
      if (Parents.empty())
        return false;
      S = Parents[0].get<Stmt>();
      if (!S)
        return false;
      if (S == Outer)
        return true;
    }
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasGoto(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

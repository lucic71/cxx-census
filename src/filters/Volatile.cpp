#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitImplicitCastExpr(ImplicitCastExpr *E) {
    if (E->getCastKind() == CK_LValueToRValue)
      check(E->getSubExpr(), "read");
    return true;
  }

  bool VisitBinaryOperator(BinaryOperator *E) {
    if (E->isAssignmentOp())
      check(E->getLHS(), "write");
    return true;
  }

  bool VisitUnaryOperator(UnaryOperator *E) {
    if (E->isIncrementDecrementOp())
      check(E->getSubExpr(), "write");
    return true;
  }

private:
  void check(const Expr *E, StringRef What) {
    QualType T = E->getType();
    if (!T.isVolatileQualified() ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return;
    report(Ctx, "volatile", E->getBeginLoc(),
           What.str() + " " + T.getUnqualifiedType().getAsString());
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasVolatile(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

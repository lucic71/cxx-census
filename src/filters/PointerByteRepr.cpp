#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/StringSet.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

const llvm::StringSet<> Allocators = {"malloc", "calloc", "realloc",
                                      "aligned_alloc", "reallocarray"};

bool hasPointerFields(const CXXRecordDecl *RD,
                      llvm::SmallPtrSetImpl<const CXXRecordDecl *> &Seen) {
  RD = RD ? RD->getDefinition() : nullptr;
  if (!RD || !Seen.insert(RD).second)
    return false;
  for (const FieldDecl *F : RD->fields()) {
    QualType T = RD->getASTContext().getBaseElementType(F->getType());
    if (T->isPointerType() || T->isMemberPointerType())
      return true;
    if (hasPointerFields(T->getAsCXXRecordDecl(), Seen))
      return true;
  }
  for (const CXXBaseSpecifier &B : RD->bases())
    if (hasPointerFields(B.getType()->getAsCXXRecordDecl(), Seen))
      return true;
  return false;
}

bool isBytePointer(QualType T) {
  if (!T->isPointerType())
    return false;
  QualType P = T->getPointeeType().getUnqualifiedType();
  return P->isCharType() || P->isVoidType() || P->isStdByteType();
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCallExpr(CallExpr *E) {
    const FunctionDecl *FD = E->getDirectCallee();
    if (FD && FD->getDeclName().isIdentifier() && FD->getName() == "free")
      for (const Expr *Arg : E->arguments())
        Freed.insert(Arg);
    return true;
  }

  bool VisitCastExpr(CastExpr *E) {
    if (Freed.count(E) ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    QualType From = E->getSubExpr()->getType(), To = E->getType();
    if (E->getCastKind() == CK_IntegralToPointer)
      report(Ctx, "pointer-byterepr", E->getBeginLoc(),
             "int-to-ptr " + From.getAsString() + " -> " + To.getAsString());
    else if (E->getCastKind() == CK_PointerToIntegral)
      report(Ctx, "pointer-byterepr", E->getBeginLoc(),
             "ptr-to-int " + From.getAsString() + " -> " + To.getAsString());

    if (!To->isPointerType() || !From->isPointerType())
      return true;
    if (isBytePointer(To) && !isBytePointer(From))
      return reportBytes(E, From, "byte-cast");
    if (!isBytePointer(From) || isBytePointer(To))
      return true;
    const auto *Call =
        dyn_cast<CallExpr>(E->getSubExpr()->IgnoreParenImpCasts());
    const FunctionDecl *FD = Call ? Call->getDirectCallee() : nullptr;
    if (FD && FD->getDeclName().isIdentifier() &&
        Allocators.contains(FD->getName()))
      return reportBytes(E, To, FD->getName());
    return reportBytes(E, To, "bytes-to-struct");
  }

private:
  llvm::SmallPtrSet<const Expr *, 8> Freed;
  bool reportBytes(const CastExpr *E, QualType T, StringRef What) {
    QualType Pointee = Ctx.getBaseElementType(T->getPointeeType());
    llvm::SmallPtrSet<const CXXRecordDecl *, 8> Seen;
    if (hasPointerFields(Pointee->getAsCXXRecordDecl(), Seen))
      report(Ctx, "pointer-byterepr", E->getBeginLoc(),
             What.str() + " struct-with-pointers " + Pointee.getAsString());
    return true;
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasPointerByteRepr(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

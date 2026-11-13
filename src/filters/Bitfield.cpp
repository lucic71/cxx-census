#include <clang/AST/Attr.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include <map>
#include <set>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitFieldDecl(FieldDecl *D) {
    if (D->getParent()->isDependentContext() || IsInSystemHeader(D))
      return true;
    if (D->isBitField())
      Features[canonical(D->getParent())]["bitfields"]++;
    if (D->hasAttr<NoUniqueAddressAttr>())
      Features[canonical(D->getParent())]["no_unique_address"]++;
    return true;
  }

  bool VisitRecordDecl(RecordDecl *D) {
    if (!D->isThisDeclarationADefinition() || D->isDependentContext() ||
        IsInSystemHeader(D))
      return true;
    auto &F = Features[canonical(D)];
    if (D->hasAttr<PackedAttr>())
      F["packed"]++;
    if (D->hasAttr<MaxFieldAlignmentAttr>())
      F["packed pragma"]++;
    if (D->hasAttr<AlignedAttr>())
      F["aligned"]++;
    if (D->isUnion())
      F["union"]++;
    if (const auto *CD = dyn_cast<CXXRecordDecl>(D)) {
      if (CD->isPolymorphic())
        F["vptr"]++;
      if (CD->getNumBases() > 0)
        F["bases"]++;
    }
    if (!F.size())
      Features.erase(canonical(D));
    return true;
  }

  bool VisitUnaryExprOrTypeTraitExpr(UnaryExprOrTypeTraitExpr *E) {
    if (E->getKind() == UETT_SizeOf || E->getKind() == UETT_AlignOf)
      observe(E->isArgumentType() ? E->getArgumentType()
                                  : E->getArgumentExpr()->getType(),
              E->getKind() == UETT_SizeOf ? "sizeof" : "alignof",
              E->getBeginLoc());
    return true;
  }

  bool VisitOffsetOfExpr(OffsetOfExpr *E) {
    observe(E->getTypeSourceInfo()->getType(), "offsetof", E->getBeginLoc());
    return true;
  }

  bool VisitCastExpr(CastExpr *E) {
    QualType To = E->getType();
    if (!To->isPointerType())
      return true;
    QualType Pointee = To->getPointeeType().getUnqualifiedType();
    if (Pointee->isCharType() || Pointee->isVoidType() ||
        Pointee->isStdByteType())
      observePointer(E->getSubExpr(), "byte-cast", E->getBeginLoc());
    return true;
  }

  void emit() {
    for (const auto &[RD, F] : Features) {
      auto It = Observed.find(RD);
      bool Packed = F.count("packed") || F.count("packed pragma");
      if (F.empty() || (It == Observed.end() && !Packed))
        continue;
      std::string Detail = RD->getQualifiedNameAsString() + " :";
      for (const auto &[Name, Count] : F)
        Detail += " " + Name + (Count > 1 ? "=" + std::to_string(Count) : "");
      if (It != Observed.end()) {
        Detail += " :";
        for (const std::string &How : It->second)
          Detail += " " + How;
      }
      report(Ctx, "bitfield", RD->getLocation(), Detail);
    }
  }

private:
  const RecordDecl *canonical(const RecordDecl *RD) {
    return cast<RecordDecl>(RD->getCanonicalDecl());
  }

  void observe(QualType T, StringRef How, SourceLocation Loc) {
    if (T.isNull() || T->isDependentType() ||
        SM.isInSystemHeader(SM.getExpansionLoc(Loc)))
      return;
    T = Ctx.getBaseElementType(T);
    if (const auto *RD = T->getAsRecordDecl())
      Observed[canonical(RD)].insert(How.str());
  }

  void observePointer(const Expr *E, StringRef How, SourceLocation Loc) {
    E = E->IgnoreParenImpCasts();
    while (const auto *Cast = dyn_cast<CastExpr>(E))
      E = Cast->getSubExpr()->IgnoreParenImpCasts();
    QualType T = E->getType();
    if (const auto *Unary = dyn_cast<UnaryOperator>(E);
        Unary && Unary->getOpcode() == UO_AddrOf)
      T = Unary->getSubExpr()->getType();
    else if (T->isPointerType() || T->isReferenceType())
      T = T->getPointeeType();
    observe(T, How, Loc);
  }

  ASTContext &Ctx;
  const SourceManager &SM;
  std::map<const RecordDecl *, std::map<std::string, unsigned>> Features;
  std::map<const RecordDecl *, std::set<std::string>> Observed;
};

} // namespace

void Filters::HasBitfield(ASTContext &Ctx) {
  Visitor V(Ctx);
  V.TraverseDecl(Ctx.getTranslationUnitDecl());
  V.emit();
}

} // namespace census

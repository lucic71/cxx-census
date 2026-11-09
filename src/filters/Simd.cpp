#include <clang/AST/Attr.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool isVector(QualType T) {
  return T->isVectorType() || T->isExtVectorType();
}

bool isStdSimd(QualType T) {
  const CXXRecordDecl *RD = T->getAsCXXRecordDecl();
  if (!RD)
    return false;
  StringRef Name = RD->getName();
  if (Name != "simd" && Name != "basic_simd" && Name != "simd_mask" &&
      Name != "basic_simd_mask")
    return false;
  return StringRef(RD->getQualifiedNameAsString()).starts_with("std::");
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitValueDecl(ValueDecl *D) {
    if (isa<FunctionDecl>(D) || IsInSystemHeader(D))
      return true;
    checkType(D->getType(), D->getLocation());
    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *D) {
    if (IsInSystemHeader(D))
      return true;
    if (const auto *A = D->getAttr<TargetAttr>())
      report(Ctx, "simd", D->getLocation(),
             "target-attribute " + A->getFeaturesStr().str() + " " +
                 D->getQualifiedNameAsString());
    checkType(D->getReturnType(), D->getLocation());
    return true;
  }

  bool VisitCallExpr(CallExpr *E) {
    const FunctionDecl *FD = E->getDirectCallee();
    if (!FD || SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    StringRef Name = FD->getName();
    bool Intrinsic = FD->getBuiltinID() && isVectorBuiltin(Name);
    if (!Intrinsic && SM.isInSystemHeader(FD->getLocation())) {
      Intrinsic = Name.starts_with("_mm") || isVector(FD->getReturnType());
      for (const ParmVarDecl *P : FD->parameters())
        Intrinsic |= isVector(P->getType());
    }
    if (Intrinsic)
      report(Ctx, "simd", E->getBeginLoc(), "intrinsic " + Name.str());
    return true;
  }

private:
  static bool isVectorBuiltin(StringRef Name) {
    return Name.starts_with("__builtin_ia32_") ||
           Name.starts_with("__builtin_neon_") ||
           Name.starts_with("__builtin_arm_") ||
           Name.starts_with("__builtin_sve_") ||
           Name.starts_with("__builtin_altivec_") ||
           Name.starts_with("__builtin_wasm_") ||
           Name.starts_with("__builtin_riscv_") ||
           Name.starts_with("__builtin_elementwise_") ||
           Name.starts_with("__builtin_reduce_") ||
           Name.starts_with("__builtin_shufflevector") ||
           Name.starts_with("__builtin_convertvector");
  }

  void checkType(QualType T, SourceLocation Loc) {
    T = Ctx.getBaseElementType(T);
    while (T->isPointerType() || T->isReferenceType())
      T = T->getPointeeType();
    if (isVector(T))
      report(Ctx, "simd", Loc, "vector-type " + T.getAsString());
    else if (isStdSimd(T))
      report(Ctx, "simd", Loc, "std-simd " + T.getAsString());
  }

  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasSimd(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

#include <clang/AST/Attr.h>
#include <clang/AST/DeclTemplate.h>
#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecordLayout.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/StringSet.h>

#include <map>
#include <set>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

bool hasDataMembers(const CXXRecordDecl *RD) {
  RD = RD->getDefinition();
  if (!RD)
    return false;
  if (!RD->field_empty())
    return true;
  for (const CXXBaseSpecifier &B : RD->bases())
    if (const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl())
      if (hasDataMembers(Base))
        return true;
  return false;
}

bool isEmptyBase(const CXXRecordDecl *RD) {
  if (!RD->isEmpty() || RD->getNumBases() != 0)
    return false;
  for (const CXXMethodDecl *M : RD->methods())
    if (!M->isImplicit())
      return false;
  return true;
}

bool isTagBase(const CXXRecordDecl *RD) {
  const auto *Spec = dyn_cast<ClassTemplateSpecializationDecl>(RD);
  if (!Spec)
    return false;
  StringRef Name = Spec->getSpecializedTemplate()->getName();
  return (Name == "integral_constant" || Name == "bool_constant") &&
         IsInSystemHeader(RD);
}

std::string baseIssues(const CXXBaseSpecifier &B) {
  const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl();
  if (!Base || !Base->getDefinition())
    return "";
  Base = Base->getDefinition();
  if (isEmptyBase(Base) || isTagBase(Base))
    return "";

  std::string Issues;
  auto Add = [&](StringRef Issue) { Issues += " " + Issue.str(); };

  if (B.isVirtual())
    Add("virtual-base");
  if (Base->isPolymorphic())
    Add("virtual");
  if (B.getAccessSpecifier() != AS_public)
    Add("non-public-base");
  if (!Base->isAbstract())
    Add("non-abstract-base");
  if (hasDataMembers(Base))
    Add("data-members");

  bool DefaultMethod = false, ConcreteMethod = false, Ctor = false,
       Dtor = false;
  for (const CXXMethodDecl *M : Base->methods()) {
    if (M->isImplicit())
      continue;
    if (isa<CXXDestructorDecl>(M)) {
      Dtor |= M->isUserProvided();
      continue;
    }
    if (isa<CXXConstructorDecl>(M)) {
      Ctor |= M->isUserProvided();
      continue;
    }
    if (M->isVirtual()) {
      const FunctionDecl *Def = nullptr;
      DefaultMethod |= !M->isPureVirtual() && M->isDefined(Def);
    } else if (!M->isStatic()) {
      ConcreteMethod = true;
    }
  }
  if (DefaultMethod)
    Add("default-method");
  if (ConcreteMethod)
    Add("concrete-method");
  if (Ctor)
    Add("constructor");
  if (Dtor)
    Add("destructor");
  if ((Issues == " virtual" || Issues == " virtual destructor") &&
      Base->isAbstract())
    return " interface";
  return Issues;
}

const CXXRecordDecl *polymorphicPointee(QualType T) {
  if (!T->isPointerType())
    return nullptr;
  const CXXRecordDecl *RD = T->getPointeeType()->getAsCXXRecordDecl();
  RD = RD ? RD->getDefinition() : nullptr;
  return RD && RD->isPolymorphic() ? RD : nullptr;
}

const llvm::StringSet<> KeyedContainers = {
    "set",           "multiset",          "map",
    "multimap",      "unordered_set",     "unordered_multiset",
    "unordered_map", "unordered_multimap"};

bool overrides(const CXXMethodDecl *M, const CXXMethodDecl *Target) {
  for (const CXXMethodDecl *O : M->overridden_methods())
    if (O->getCanonicalDecl() == Target->getCanonicalDecl() ||
        overrides(O, Target))
      return true;
  return false;
}

void collectBases(const CXXRecordDecl *RD,
                  std::vector<const CXXRecordDecl *> &Out) {
  for (const CXXBaseSpecifier &B : RD->bases())
    if (const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl())
      if ((Base = Base->getDefinition())) {
        Out.push_back(Base);
        collectBases(Base, Out);
      }
}

class Visitor : public RecursiveASTVisitor<Visitor> {
  using Base = RecursiveASTVisitor<Visitor>;

public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitCXXRecordDecl(CXXRecordDecl *D) {
    if (!D->isThisDeclarationADefinition() || D->isDependentContext() ||
        IsInSystemHeader(D))
      return true;
    if (D->getNumBases() == 0) {
      if (D->isPolymorphic() && !D->isAbstract())
        report(Ctx, "inheritance", D->getLocation(),
               "polymorphic-root " + D->getQualifiedNameAsString());
      return true;
    }

    std::string Detail;
    for (const CXXBaseSpecifier &B : D->bases()) {
      if (const CXXRecordDecl *Base = B.getType()->getAsCXXRecordDecl())
        Bases.insert(Base->getCanonicalDecl());
      std::string Issues = baseIssues(B);
      if (!Issues.empty())
        Detail += " [" + B.getType().getAsString() + ":" + Issues + "]";
    }
    if (D->getNumBases() > 1)
      Detail += " [multiple-bases]";
    if (!Detail.empty())
      report(Ctx, "inheritance", D->getLocation(),
             "class " + D->getQualifiedNameAsString() + " :" + Detail);
    hiding(D);
    return true;
  }

  bool TraverseCXXMethodDecl(CXXMethodDecl *D) {
    return inMethod(D, [&] { return Base::TraverseCXXMethodDecl(D); });
  }
  bool TraverseCXXConstructorDecl(CXXConstructorDecl *D) {
    return inMethod(D, [&] { return Base::TraverseCXXConstructorDecl(D); });
  }
  bool TraverseCXXDestructorDecl(CXXDestructorDecl *D) {
    return inMethod(D, [&] { return Base::TraverseCXXDestructorDecl(D); });
  }
  bool TraverseCXXConversionDecl(CXXConversionDecl *D) {
    return inMethod(D, [&] { return Base::TraverseCXXConversionDecl(D); });
  }

  bool VisitCXXMemberCallExpr(CXXMemberCallExpr *E) {
    const CXXMethodDecl *Callee = E->getMethodDecl();
    if (!Current || !Callee || !Callee->isVirtual() ||
        Callee->hasAttr<FinalAttr>())
      return true;
    const auto *ME = dyn_cast<MemberExpr>(E->getCallee()->IgnoreParens());
    if (!ME || ME->hasQualifier())
      return true;
    const Expr *Obj = E->getImplicitObjectArgument();
    if (!Obj || !isa<CXXThisExpr>(Obj->IgnoreParenImpCasts()))
      return true;
    const CXXRecordDecl *Class = Current->getParent();
    if (Class->isLambda() || Class->hasAttr<FinalAttr>())
      return true;
    StringRef What = isa<CXXConstructorDecl>(Current)  ? "virtual-call-in-ctor"
                     : isa<CXXDestructorDecl>(Current) ? "virtual-call-in-dtor"
                                                       : "this-virtual-call";
    reportExpr(What, E->getBeginLoc(),
               Current->getQualifiedNameAsString() + " -> " +
                   Callee->getQualifiedNameAsString());
    return true;
  }

  bool VisitCXXConstructExpr(CXXConstructExpr *E) {
    const CXXConstructorDecl *Ctor = E->getConstructor();
    if (Ctor && Ctor->isCopyOrMoveConstructor() && E->getNumArgs() >= 1)
      markSlice(E->getArg(0));
    if (E->getConstructionKind() != CXXConstructionKind::Complete || !Ctor ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    const CXXRecordDecl *RD = Ctor->getParent();
    if (!IsInSystemHeader(RD))
      Instances.emplace(RD->getCanonicalDecl(), E->getBeginLoc());
    return true;
  }

  bool VisitCXXOperatorCallExpr(CXXOperatorCallExpr *E) {
    if (E->getOperator() != OO_Equal || E->getNumArgs() != 2)
      return true;
    const auto *M = dyn_cast_or_null<CXXMethodDecl>(E->getCalleeDecl());
    if (M && (M->isCopyAssignmentOperator() || M->isMoveAssignmentOperator()))
      markSlice(E->getArg(1));
    return true;
  }

  bool VisitBinaryOperator(BinaryOperator *E) {
    const Expr *L = E->getLHS(), *R = E->getRHS();
    if (E->isComparisonOp()) {
      if (L->isNullPointerConstant(Ctx, Expr::NPC_ValueDependentIsNotNull) ||
          R->isNullPointerConstant(Ctx, Expr::NPC_ValueDependentIsNotNull))
        return true;
      if (const CXXRecordDecl *RD = polymorphicPointee(L->getType()))
        reportExpr("poly-ptr-compare", E->getOperatorLoc(),
                   RD->getQualifiedNameAsString());
      return true;
    }
    if (E->isAdditiveOp() || E->getOpcode() == BO_AddAssign ||
        E->getOpcode() == BO_SubAssign) {
      const CXXRecordDecl *RD = polymorphicPointee(L->getType());
      if (!RD)
        RD = polymorphicPointee(R->getType());
      if (RD)
        reportExpr("poly-ptr-arith", E->getOperatorLoc(),
                   RD->getQualifiedNameAsString());
    }
    return true;
  }

  bool VisitUnaryOperator(UnaryOperator *E) {
    if (!E->isIncrementDecrementOp())
      return true;
    if (const CXXRecordDecl *RD =
            polymorphicPointee(E->getSubExpr()->getType()))
      reportExpr("poly-ptr-arith", E->getOperatorLoc(),
                 RD->getQualifiedNameAsString());
    return true;
  }

  bool VisitArraySubscriptExpr(ArraySubscriptExpr *E) {
    if (const CXXRecordDecl *RD = polymorphicPointee(E->getBase()->getType()))
      reportExpr("poly-ptr-arith", E->getBeginLoc(),
                 RD->getQualifiedNameAsString());
    return true;
  }

  bool VisitDeclaratorDecl(DeclaratorDecl *D) {
    if ((!isa<VarDecl>(D) && !isa<FieldDecl>(D)) ||
        D->getType()->isDependentType() || IsInSystemHeader(D))
      return true;
    const auto *Spec = dyn_cast_or_null<ClassTemplateSpecializationDecl>(
        D->getType().getNonReferenceType()->getAsCXXRecordDecl());
    if (!Spec || !Spec->isInStdNamespace() ||
        !KeyedContainers.contains(Spec->getName()) ||
        Spec->getTemplateArgs().size() == 0 ||
        Spec->getTemplateArgs()[0].getKind() != TemplateArgument::Type)
      return true;
    if (const CXXRecordDecl *RD =
            polymorphicPointee(Spec->getTemplateArgs()[0].getAsType()))
      reportExpr("poly-ptr-key", D->getLocation(),
                 Spec->getName().str() + " " + RD->getQualifiedNameAsString());
    return true;
  }

  void emit() {
    for (const auto &[RD, Loc] : Instances) {
      const auto *Def = RD->getDefinition();
      if (Def && Bases.count(RD) && !isEmptyBase(Def) && !isTagBase(Def))
        reportExpr("base-instantiated", Loc, Def->getQualifiedNameAsString());
    }
  }

  bool VisitMemberExpr(MemberExpr *E) {
    MemberBases.insert(E->getBase()->IgnoreParens());
    return true;
  }

  bool VisitCastExpr(CastExpr *E) {
    QualType To = E->getType();
    if (const CXXRecordDecl *RD =
            polymorphicPointee(E->getSubExpr()->getType());
        RD && To->isPointerType() &&
        (To->getPointeeType()->isVoidType() ||
         To->getPointeeType()->isCharType()))
      reportExpr("poly-ptr-erase", E->getBeginLoc(),
                 RD->getQualifiedNameAsString() + " -> " + To.getAsString());
    if (E->getCastKind() == CK_BaseToDerived) {
      reportExpr("downcast", E->getBeginLoc(),
                 E->getSubExpr()->getType().getAsString() + " -> " +
                     To.getAsString());
      return true;
    }
    if ((E->getCastKind() != CK_DerivedToBase &&
         E->getCastKind() != CK_UncheckedDerivedToBase) ||
        MemberBases.count(E))
      return true;
    QualType From = E->getSubExpr()->getType();
    if (From->isPointerType())
      From = From->getPointeeType();
    const CXXRecordDecl *Derived = From->getAsCXXRecordDecl();
    if (!Derived || IsInSystemHeader(Derived))
      return true;
    std::string Detail;
    const CXXRecordDecl *Step = Derived->getDefinition();
    for (const CXXBaseSpecifier *B : E->path()) {
      const CXXRecordDecl *BaseRD = B->getType()->getAsCXXRecordDecl();
      BaseRD = BaseRD ? BaseRD->getDefinition() : nullptr;
      if (!BaseRD)
        break;
      CharUnits Offset = CharUnits::Zero();
      if (Step && !Step->isDependentType() && !Step->isInvalidDecl()) {
        const ASTRecordLayout &L = Ctx.getASTRecordLayout(Step);
        Offset = B->isVirtual() ? L.getVBaseClassOffset(BaseRD)
                                : L.getBaseClassOffset(BaseRD);
      }
      Step = BaseRD;
      if (BaseRD->isAbstract() && !hasDataMembers(BaseRD))
        continue;
      std::string Issues = baseIssues(*B);
      if (!Offset.isZero())
        Issues += " offset=" + std::to_string(Offset.getQuantity());
      if (!Issues.empty())
        Detail += " [" + B->getType().getAsString() + ":" + Issues + "]";
    }
    if (!Detail.empty())
      reportExpr(Slices.count(E) ? "slice" : "upcast", E->getBeginLoc(),
                 E->getSubExpr()->getType().getAsString() + " ->" + Detail);
    return true;
  }

  bool VisitCXXDynamicCastExpr(CXXDynamicCastExpr *E) {
    reportExpr("dynamic_cast", E->getBeginLoc(),
               E->getTypeAsWritten().getAsString());
    return true;
  }

  bool VisitCXXTypeidExpr(CXXTypeidExpr *E) {
    if (!E->isPotentiallyEvaluated())
      return true;
    reportExpr("typeid", E->getBeginLoc(),
               E->isTypeOperand()
                   ? E->getTypeOperand(Ctx).getAsString()
                   : E->getExprOperand()->getType().getAsString());
    return true;
  }

private:
  template <typename F> bool inMethod(const CXXMethodDecl *D, F Traverse) {
    const CXXMethodDecl *Saved = Current;
    Current = D;
    bool R = Traverse();
    Current = Saved;
    return R;
  }

  void markSlice(const Expr *E) {
    while (true) {
      E = E->IgnoreParens();
      if (const auto *M = dyn_cast<MaterializeTemporaryExpr>(E)) {
        E = M->getSubExpr();
        continue;
      }
      const auto *C = dyn_cast<ImplicitCastExpr>(E);
      if (!C)
        return;
      if (C->getCastKind() == CK_DerivedToBase ||
          C->getCastKind() == CK_UncheckedDerivedToBase) {
        Slices.insert(C);
        return;
      }
      if (C->getCastKind() != CK_NoOp)
        return;
      E = C->getSubExpr();
    }
  }

  void hiding(const CXXRecordDecl *D) {
    std::vector<const CXXRecordDecl *> All;
    collectBases(D, All);
    for (const CXXMethodDecl *M : D->methods()) {
      if (M->isImplicit() || isa<CXXConstructorDecl>(M) ||
          isa<CXXDestructorDecl>(M) || isa<CXXConversionDecl>(M) ||
          M->isOverloadedOperator() || !M->getDeclName().isIdentifier())
        continue;
      for (const CXXMethodDecl *O : M->overridden_methods())
        if (!Ctx.hasSameType(M->getReturnType(), O->getReturnType())) {
          report(Ctx, "inheritance", M->getLocation(),
                 "covariant " + M->getQualifiedNameAsString());
          break;
        }
      for (const CXXRecordDecl *BaseRD : All) {
        bool Hidden = false;
        for (const NamedDecl *N : BaseRD->lookup(M->getDeclName())) {
          const auto *BM = dyn_cast<CXXMethodDecl>(N->getUnderlyingDecl());
          if (!BM)
            continue;
          if (BM->isVirtual() && overrides(M, BM))
            continue;
          Hidden = true;
        }
        if (Hidden) {
          report(Ctx, "inheritance", M->getLocation(),
                 "hides " + M->getQualifiedNameAsString() + " " +
                     BaseRD->getQualifiedNameAsString());
          break;
        }
      }
    }
  }

  void reportExpr(StringRef What, SourceLocation Loc, StringRef Type) {
    SourceLocation Exp = SM.getExpansionLoc(Loc);
    if (SM.isInSystemHeader(Exp))
      return;
    report(Ctx, "inheritance", Loc, What.str() + " " + Type.str());
  }

  llvm::SmallPtrSet<const Expr *, 16> MemberBases;
  llvm::SmallPtrSet<const Expr *, 16> Slices;
  std::set<const CXXRecordDecl *> Bases;
  std::multimap<const CXXRecordDecl *, SourceLocation> Instances;
  const CXXMethodDecl *Current = nullptr;
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasInheritance(ASTContext &Ctx) {
  Visitor V(Ctx);
  V.TraverseDecl(Ctx.getTranslationUnitDecl());
  V.emit();
}

} // namespace census

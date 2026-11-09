#include <clang/AST/ExprCXX.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/StmtCXX.h>
#include <clang/AST/StmtOpenMP.h>
#include <llvm/ADT/StringSet.h>

#include "Census.h"
#include "census_lib.h"

using namespace clang;

namespace census {
namespace {

const llvm::StringSet<> StdTypes = {
    "thread",
    "jthread",
    "mutex",
    "recursive_mutex",
    "timed_mutex",
    "recursive_timed_mutex",
    "shared_mutex",
    "shared_timed_mutex",
    "lock_guard",
    "unique_lock",
    "scoped_lock",
    "shared_lock",
    "once_flag",
    "condition_variable",
    "condition_variable_any",
    "future",
    "shared_future",
    "promise",
    "packaged_task",
    "latch",
    "barrier",
    "counting_semaphore",
    "stop_token",
    "stop_source",
    "stop_callback",
};

const llvm::StringSet<> StdFunctions = {
    "std::async",
    "std::call_once",
    "std::this_thread::sleep_for",
    "std::this_thread::sleep_until",
    "std::this_thread::yield",
    "std::this_thread::get_id",
    "std::atomic_thread_fence",
    "std::atomic_signal_fence",
};

bool isStdRecord(const CXXRecordDecl *RD) {
  const DeclContext *DC = RD->getDeclContext();
  while (DC && DC->isInlineNamespace())
    DC = DC->getParent();
  const auto *NS = dyn_cast_or_null<NamespaceDecl>(DC);
  return NS && NS->getName() == "std" && !NS->getParent()->isNamespace();
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool shouldVisitTemplateInstantiations() const { return true; }

  bool VisitVarDecl(VarDecl *D) {
    if (IsInSystemHeader(D))
      return true;
    checkType(D->getType(), D->getLocation());
    return true;
  }

  bool VisitFieldDecl(FieldDecl *D) {
    if (!IsInSystemHeader(D))
      checkType(D->getType(), D->getLocation());
    return true;
  }

  bool VisitCXXConstructExpr(CXXConstructExpr *E) {
    if (!isa<CXXTemporaryObjectExpr>(E))
      return true;
    if (!SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      checkType(E->getType(), E->getBeginLoc());
    return true;
  }

  bool VisitCXXFunctionalCastExpr(CXXFunctionalCastExpr *E) {
    if (!SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      checkType(E->getType(), E->getBeginLoc());
    return true;
  }

  bool VisitCallExpr(CallExpr *E) {
    const FunctionDecl *FD = E->getDirectCallee();
    if (!FD || SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    if (!FD->getDeclName().isIdentifier())
      return true;
    std::string Name = FD->getQualifiedNameAsString();
    StringRef Base = FD->getName();
    if (StdFunctions.contains(Name) || Base.starts_with("pthread_") ||
        Base.starts_with("omp_") || Base.starts_with("__atomic_") ||
        Base.starts_with("__sync_"))
      report(Ctx, "concurrency", E->getBeginLoc(), std::string("call ") + Name);
    return true;
  }

  bool VisitAtomicExpr(AtomicExpr *E) {
    if (!SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      report(Ctx, "concurrency", E->getBeginLoc(),
             ("atomic-builtin " + E->getOpAsString()).str());
    return true;
  }

  bool VisitOMPExecutableDirective(OMPExecutableDirective *S) {
    if (!SM.isInSystemHeader(SM.getExpansionLoc(S->getBeginLoc())))
      report(Ctx, "concurrency", S->getBeginLoc(),
             std::string("openmp ") +
                 getOpenMPDirectiveName(S->getDirectiveKind(),
                                        Ctx.getLangOpts().OpenMP)
                     .str());
    return true;
  }

  bool VisitCoroutineBodyStmt(CoroutineBodyStmt *S) {
    if (SM.isInSystemHeader(SM.getExpansionLoc(S->getBeginLoc())))
      return true;
    std::string Name = "coroutine";
    if (const auto *FD = dyn_cast_or_null<FunctionDecl>(Fn))
      Name += " " + FD->getQualifiedNameAsString();
    report(Ctx, "concurrency", S->getBeginLoc(), Name);
    return true;
  }

  bool TraverseFunctionDecl(FunctionDecl *D) {
    const Decl *Saved = Fn;
    Fn = D;
    bool R = RecursiveASTVisitor::TraverseFunctionDecl(D);
    Fn = Saved;
    return R;
  }

  bool TraverseCXXMethodDecl(CXXMethodDecl *D) {
    const Decl *Saved = Fn;
    Fn = D;
    bool R = RecursiveASTVisitor::TraverseCXXMethodDecl(D);
    Fn = Saved;
    return R;
  }

private:
  void checkType(QualType T, SourceLocation Loc) {
    T = Ctx.getBaseElementType(T);
    while (T->isPointerType() || T->isReferenceType())
      T = T->getPointeeType();
    const CXXRecordDecl *RD = T->getAsCXXRecordDecl();
    if (!RD || !isStdRecord(RD))
      return;
    if (StdTypes.contains(RD->getName()))
      report(Ctx, "concurrency", Loc,
             "type " + T.getUnqualifiedType().getAsString());
  }

  ASTContext &Ctx;
  const SourceManager &SM;
  const Decl *Fn = nullptr;
};

} // namespace

void Filters::HasConcurrency(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

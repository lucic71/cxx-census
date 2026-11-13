#include <clang/AST/RecursiveASTVisitor.h>
#include <llvm/ADT/StringSet.h>

#include "Census.h"

using namespace clang;

namespace census {
namespace {

const llvm::StringSet<> SyncTypes = {
    "atomic_t",        "atomic64_t",       "atomic_long_t",
    "refcount_t",      "kref",             "spinlock_t",
    "raw_spinlock_t",  "rwlock_t",         "mutex",
    "rw_semaphore",    "semaphore",        "percpu_rw_semaphore",
    "seqcount_t",      "seqlock_t",        "completion",
    "wait_queue_head", "swait_queue_head", "rcu_head",
    "callback_head",   "srcu_struct",      "local_lock_t"};

StringRef syncTypeName(QualType T) {
  while (true) {
    if (const auto *TT = T->getAs<TypedefType>()) {
      StringRef Name = TT->getDecl()->getName();
      if (SyncTypes.contains(Name))
        return Name;
      T = TT->getDecl()->getUnderlyingType();
      continue;
    }
    if (const RecordDecl *RD = T->getAsRecordDecl())
      if (RD->getIdentifier() && SyncTypes.contains(RD->getName()))
        return RD->getName();
    return "";
  }
}

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext &Ctx) : Ctx(Ctx), SM(Ctx.getSourceManager()) {}

  bool VisitUnaryOperator(UnaryOperator *E) {
    if (E->getOpcode() != UO_AddrOf ||
        SM.isInSystemHeader(SM.getExpansionLoc(E->getBeginLoc())))
      return true;
    StringRef Name = syncTypeName(E->getSubExpr()->getType());
    if (!Name.empty())
      report(Ctx, "linux-concurrency", E->getBeginLoc(), Name);
    return true;
  }

private:
  ASTContext &Ctx;
  const SourceManager &SM;
};

} // namespace

void Filters::HasLinuxConcurrency(ASTContext &Ctx) {
  Visitor(Ctx).TraverseDecl(Ctx.getTranslationUnitDecl());
}

} // namespace census

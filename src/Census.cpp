#include "Census.h"

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <llvm/ADT/StringMap.h>

#include <vector>

using namespace clang;

namespace census {

void report(const ASTContext &Ctx, StringRef Criterion, SourceLocation Loc,
            StringRef Detail) {
  const SourceManager &SM = Ctx.getSourceManager();
  PresumedLoc P = SM.getPresumedLoc(SM.getFileLoc(Loc));
  if (P.isInvalid())
    return;
  llvm::errs() << "census: " << Criterion << ": " << P.getFilename() << ":"
               << P.getLine() << ":" << P.getColumn() << ": " << Detail << "\n";
}

namespace {

using CriterionFn = void (*)(ASTContext &);

const llvm::StringMap<CriterionFn> AllCriteria = {
    {"base-with-data-members", Criteria::HasBaseWithDataMembers},
    {"non-const-copy-constructor", Criteria::HasNonConstCopyConstructor},
};

class Consumer : public ASTConsumer {
public:
  explicit Consumer(std::vector<CriterionFn> Selected)
      : Selected(std::move(Selected)) {}

  void HandleTranslationUnit(ASTContext &Ctx) override {
    for (CriterionFn Run : Selected)
      Run(Ctx);
  }

private:
  std::vector<CriterionFn> Selected;
};

class Action : public PluginASTAction {
protected:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &,
                                                 StringRef) override {
    return std::make_unique<Consumer>(Selected);
  }

  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &Args) override {
    for (const std::string &Name : Args) {
      auto It = AllCriteria.find(Name);
      if (It == AllCriteria.end()) {
        DiagnosticsEngine &D = CI.getDiagnostics();
        D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                   "census: unknown criterion '%0'"))
            << Name;
        return false;
      }
      Selected.push_back(It->second);
    }

    if (Args.empty())
      for (const auto &E : AllCriteria)
        Selected.push_back(E.second);
    return true;
  }

  ActionType getActionType() override { return AddBeforeMainAction; }

private:
  std::vector<CriterionFn> Selected;
};

} // namespace
} // namespace census

static FrontendPluginRegistry::Add<census::Action> X("census",
                                                     "C++ feature census");

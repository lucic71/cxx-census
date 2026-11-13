#include "Census.h"

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <llvm/ADT/StringMap.h>

#include <vector>

using namespace clang;

namespace census {

void report(const ASTContext &Ctx, StringRef Filter, SourceLocation Loc,
            StringRef Detail) {
  const SourceManager &SM = Ctx.getSourceManager();
  PresumedLoc P = SM.getPresumedLoc(SM.getFileLoc(Loc));
  if (P.isInvalid())
    return;
  llvm::errs() << "census: " << Filter << ": " << P.getFilename() << ":"
               << P.getLine() << ":" << P.getColumn() << ": " << Detail << "\n";
}

namespace {

using FilterFn = void (*)(ASTContext &);

const llvm::StringMap<FilterFn> AllFilters = {
    {"non-const-copy-constructor", Filters::HasNonConstCopyConstructor},
    {"inheritance", Filters::HasInheritance},
    {"exceptions", Filters::HasExceptions},
    {"concurrency", Filters::HasConcurrency},
    {"simd", Filters::HasSimd},
    {"asm", Filters::HasAsm},
    {"pointer-byterepr", Filters::HasPointerByteRepr},
    {"placement-new", Filters::HasPlacementNew},
    {"dynamic-loading", Filters::HasDynamicLoading},
    {"stl-usage", Filters::HasStlUsage},
    {"member-pointer", Filters::HasMemberPointer},
    {"self-reference", Filters::HasSelfReference},
    {"bitfield", Filters::HasBitfield},
    {"global-destructor", Filters::HasGlobalDestructor},
    {"goto", Filters::HasGoto},
    {"terminal", Filters::HasTerminal},
    {"coroutines", Filters::HasCoroutines},
    {"switch", Filters::HasSwitch},
    {"lambda-template-argument", Filters::HasLambdaTemplateArgument},
    {"operator-new", Filters::HasOperatorNew},
    {"cpo", Filters::HasCpo},
    {"std-specialization", Filters::HasStdSpecialization},
    {"empty-array", Filters::HasEmptyArray},
    {"fancy-pointer", Filters::HasFancyPointer},
    {"linux-concurrency", Filters::HasLinuxConcurrency},
    {"volatile", Filters::HasVolatile},
};

class Consumer : public ASTConsumer {
public:
  explicit Consumer(std::vector<FilterFn> Selected)
      : Selected(std::move(Selected)) {}

  void HandleTranslationUnit(ASTContext &Ctx) override {
    for (FilterFn Run : Selected)
      Run(Ctx);
  }

private:
  std::vector<FilterFn> Selected;
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
      if (Name == "list") {
        for (const auto &E : AllFilters)
          llvm::outs() << E.first() << "\n";
        continue;
      }
      auto It = AllFilters.find(Name);
      if (It == AllFilters.end()) {
        DiagnosticsEngine &D = CI.getDiagnostics();
        D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                   "census: unknown filter '%0'"))
            << Name;
        return false;
      }
      Selected.push_back(It->second);
    }

    if (Args.empty())
      for (const auto &E : AllFilters)
        Selected.push_back(E.second);
    return true;
  }

  ActionType getActionType() override { return AddBeforeMainAction; }

private:
  std::vector<FilterFn> Selected;
};

} // namespace
} // namespace census

static FrontendPluginRegistry::Add<census::Action> X("census",
                                                     "C++ feature census");

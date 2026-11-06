#include "Census.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

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

class Consumer : public ASTConsumer {
public:
  void HandleTranslationUnit(ASTContext &Ctx) override {
    Criteria::HasBaseWithDataMembers(Ctx);
  }
};

class Action : public PluginASTAction {
protected:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &,
                                                 StringRef) override {
    return std::make_unique<Consumer>();
  }

  bool ParseArgs(const CompilerInstance &,
                 const std::vector<std::string> &) override {
    return true;
  }

  ActionType getActionType() override { return AddBeforeMainAction; }
};

} // namespace
} // namespace census

static FrontendPluginRegistry::Add<census::Action> X("census",
                                                     "C++ feature census");

#pragma once

#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"

namespace census {

void report(const clang::ASTContext &Ctx, llvm::StringRef Criterion,
            clang::SourceLocation Loc, llvm::StringRef Detail);

namespace Criteria {
void HasInheritance(clang::ASTContext &Ctx);
} // namespace Criteria

} // namespace census

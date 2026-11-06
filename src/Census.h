#pragma once

#include <clang/AST/ASTContext.h>
#include <clang/Basic/SourceManager.h>

namespace census {

void report(const clang::ASTContext &Ctx, llvm::StringRef Filter,
            clang::SourceLocation Loc, llvm::StringRef Detail);

namespace Filters {
void HasBaseWithDataMembers(clang::ASTContext &Ctx);
void HasNonConstCopyConstructor(clang::ASTContext &Ctx);
} // namespace Filters

} // namespace census

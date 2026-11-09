#pragma once

#include <clang/AST/ASTContext.h>
#include <clang/Basic/SourceManager.h>

namespace census {

void report(const clang::ASTContext &Ctx, llvm::StringRef Filter,
            clang::SourceLocation Loc, llvm::StringRef Detail);

namespace Filters {
void HasNonConstCopyConstructor(clang::ASTContext &Ctx);
void HasInheritance(clang::ASTContext &Ctx);
void HasExceptions(clang::ASTContext &Ctx);
void HasConcurrency(clang::ASTContext &Ctx);
void HasSimd(clang::ASTContext &Ctx);
void HasAsm(clang::ASTContext &Ctx);
void HasPointerByteRepr(clang::ASTContext &Ctx);
void HasPlacementNew(clang::ASTContext &Ctx);
void HasDynamicLoading(clang::ASTContext &Ctx);
void HasStlUsage(clang::ASTContext &Ctx);
} // namespace Filters

} // namespace census

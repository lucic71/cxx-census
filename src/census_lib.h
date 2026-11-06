#pragma once

#include <clang/AST/Decl.h>

namespace census {

bool IsInSystemHeader(const clang::Decl *D);

} // namespace census

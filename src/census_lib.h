#pragma once

#include <clang/AST/Decl.h>

namespace census {

bool IsUserDefinedDecl(const clang::Decl *D);

} // namespace census

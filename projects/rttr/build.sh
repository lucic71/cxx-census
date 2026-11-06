#!/bin/bash -eu

cmake -S "$SRC/rttr" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_EXAMPLES=OFF \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -DCATCH_CONFIG_NO_POSIX_SIGNALS -Wno-implicit-const-int-float-conversion -Wno-ordered-compare-function-pointers -Wno-error=deprecated-builtins -Wno-error=self-assign-overloaded"
cmake --build "$BUILD" -j "$(nproc)"

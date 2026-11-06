#!/bin/bash -eu

cmake -S "$SRC/wasmedge" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DLLVM_DIR=/usr/lib/llvm-18/lib/cmake/llvm -DLLD_DIR=/usr/lib/llvm-18/lib/cmake/lld
cmake --build "$BUILD" -j "$(nproc)"

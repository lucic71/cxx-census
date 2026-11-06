#!/bin/bash -eu

cmake -S "$SRC/rpcs3" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DUSE_LTO=OFF -DUSE_SYSTEM_SDL=OFF -DUSE_SYSTEM_FFMPEG=ON -DLLVM_DIR=/usr/lib/llvm-$CLANG_VERSION/lib/cmake/llvm
cmake --build "$BUILD" -j "$(nproc)"

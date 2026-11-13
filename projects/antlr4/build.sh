#!/bin/bash -eu

cmake -S "$SRC/antlr4/runtime/Cpp" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DANTLR_BUILD_CPP_TESTS=OFF
cmake --build "$BUILD" -j "$(nproc)"

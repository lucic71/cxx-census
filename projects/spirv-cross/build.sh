#!/bin/bash -eu

cmake -S "$SRC/spirv-cross" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DSPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS=ON -DSPIRV_CROSS_ENABLE_TESTS=ON
cmake --build "$BUILD" -j "$(nproc)"

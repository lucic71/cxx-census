#!/bin/bash -eu

cmake -S "$SRC/re2" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DRE2_BUILD_TESTING=ON
cmake --build "$BUILD" -j "$(nproc)"

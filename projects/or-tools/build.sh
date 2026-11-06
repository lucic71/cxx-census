#!/bin/bash -eu

cmake -S "$SRC/or-tools" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_DEPS=ON \
  -DCMAKE_CXX_FLAGS="$CXXFLAGS -Wno-c2y-extensions"
cmake --build "$BUILD" -j "$(nproc)"

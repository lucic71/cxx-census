#!/bin/bash -eu

cmake -S "$SRC/ninja" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DNINJA_BUILD_BINARY=ON
cmake --build "$BUILD" -j "$(nproc)"

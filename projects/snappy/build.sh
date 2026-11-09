#!/bin/bash -eu

cmake -S "$SRC/snappy" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DSNAPPY_BUILD_TESTS=ON -DSNAPPY_BUILD_BENCHMARKS=OFF
cmake --build "$BUILD" -j "$(nproc)"

#!/bin/bash -eu

cmake -S "$SRC/leveldb" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DLEVELDB_BUILD_TESTS=ON -DLEVELDB_BUILD_BENCHMARKS=OFF
cmake --build "$BUILD" -j "$(nproc)"

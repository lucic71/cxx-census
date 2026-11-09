#!/bin/bash -eu

cmake -S "$SRC/double-conversion" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DBUILD_TESTING=ON
cmake --build "$BUILD" -j "$(nproc)"

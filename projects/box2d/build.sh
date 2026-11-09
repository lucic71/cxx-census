#!/bin/bash -eu

cmake -S "$SRC/box2d" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="$CXXFLAGS -fno-exceptions" -DBOX2D_BUILD_UNIT_TESTS=ON -DBOX2D_BUILD_TESTBED=OFF
cmake --build "$BUILD" -j "$(nproc)"

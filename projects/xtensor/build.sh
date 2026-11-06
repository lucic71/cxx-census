#!/bin/bash -eu

cmake -S "$SRC/xtensor" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTS=ON
cmake --build "$BUILD" -j "$(nproc)"

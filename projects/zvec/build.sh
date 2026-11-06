#!/bin/bash -eu

cmake -S "$SRC/zvec" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD" -j "$(nproc)"

#!/bin/bash -eu

cmake -S "$SRC/cli11" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCLI11_PRECOMPILED=ON
cmake --build "$BUILD" -j "$(nproc)"

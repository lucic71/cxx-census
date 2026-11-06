#!/bin/bash -eu

cmake -S "$SRC/ton" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DTON_USE_JEMALLOC=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"

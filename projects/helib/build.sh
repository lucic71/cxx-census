#!/bin/bash -eu

cmake -S "$SRC/helib" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DPEDANTIC_BUILD=OFF
cmake --build "$BUILD" -j "$(nproc)"

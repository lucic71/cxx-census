#!/bin/bash -eu

cmake -S "$SRC/root" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Dbuiltin_civetweb=ON
cmake --build "$BUILD" -j "$(nproc)"

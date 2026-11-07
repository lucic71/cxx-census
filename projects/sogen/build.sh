#!/bin/bash -eu

cmake -S "$SRC/sogen" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSOGEN_ENABLE_AVX2=OFF
cmake --build "$BUILD" -j "$(nproc)"

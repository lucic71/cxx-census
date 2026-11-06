#!/bin/bash -eu

cmake -S "$SRC/onetbb" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DTBB_TEST=OFF -DTBB_STRICT=OFF
cmake --build "$BUILD" -j "$(nproc)"

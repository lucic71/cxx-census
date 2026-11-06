#!/bin/bash -eu

cmake -S "$SRC/openscad" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD" -j "$(nproc)"

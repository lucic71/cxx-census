#!/bin/bash -eu

cmake -S "$SRC/woff2" -B "$BUILD"
cmake --build "$BUILD" -j "$(nproc)"

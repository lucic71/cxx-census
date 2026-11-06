#!/bin/bash -eu

cmake -S "$SRC/brunsli" -B "$BUILD" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD" --config Release -j "$(nproc)"

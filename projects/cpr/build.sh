#!/bin/bash -eu

cmake -S "$SRC/cpr" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCPR_USE_SYSTEM_CURL=ON
cmake --build "$BUILD" -j "$(nproc)"

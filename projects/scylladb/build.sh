#!/bin/bash -eu

cmake -S "$SRC/scylladb" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"

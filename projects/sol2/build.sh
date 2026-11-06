#!/bin/bash -eu

cmake -S "$SRC/sol2" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DSOL2_BUILD_LUA=ON -DSOL2_TESTS=ON -DSOL2_EXAMPLES=ON
cmake --build "$BUILD" -j "$(nproc)"

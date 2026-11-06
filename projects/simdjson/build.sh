#!/bin/bash -eu

cmake -S "$SRC/simdjson" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DSIMDJSON_DEVELOPER_MODE=ON
cmake --build "$BUILD" -j "$(nproc)"

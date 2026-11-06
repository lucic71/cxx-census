#!/bin/bash -eu

cmake -S "$SRC/cereal" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DWITH_WERROR=OFF
cmake --build "$BUILD" -j "$(nproc)"

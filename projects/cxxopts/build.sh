#!/bin/bash -eu

cmake -S "$SRC/cxxopts" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCXXOPTS_CXX_STANDARD=17
cmake --build "$BUILD" -j "$(nproc)"

#!/bin/bash -eu

cmake -S "$SRC/yaml-cpp" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DYAML_CPP_BUILD_TESTS=OFF
cmake --build "$BUILD" -j "$(nproc)"

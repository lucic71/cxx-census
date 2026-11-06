#!/bin/bash -eu

cmake -S "$SRC/cgal" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCGAL_WITH_examples=ON -DCGAL_WITH_demos=ON
cmake --build "$BUILD" -j "$(nproc)" --target examples demos

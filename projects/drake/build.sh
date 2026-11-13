#!/bin/bash -eu

mkdir -p "$BUILD"
for f in $CXXFLAGS; do echo "build --cxxopt=$f --host_cxxopt=$f"; done > "$BUILD/drake.bazelrc"
for f in $CFLAGS; do echo "build --conlyopt=$f --host_conlyopt=$f"; done >> "$BUILD/drake.bazelrc"
echo "build --subcommands --jobs=$(nproc)" >> "$BUILD/drake.bazelrc"
cmake -S "$SRC/drake" -B "$BUILD" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD" -j "$(nproc)"

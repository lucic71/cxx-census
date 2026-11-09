#!/bin/bash -eu

mkdir -p "$BUILD"
cd "$SRC/double-conversion"
$CXX $CXXFLAGS -fno-exceptions -O2 -I. -o "$BUILD/cctest" double-conversion/*.cc test/cctest/*.cc

#!/bin/bash -eu

cd "$SRC/lodepng"
$CXX $CXXFLAGS -fno-exceptions -O2 -o "$BUILD/lodepng_unittest" lodepng.cpp lodepng_util.cpp lodepng_unittest.cpp

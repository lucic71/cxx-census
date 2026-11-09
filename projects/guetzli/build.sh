#!/bin/bash -eu

make -C "$SRC/guetzli" config=release -j "$(nproc)" CXX="$CXX" CXXFLAGS="$CXXFLAGS -fno-exceptions"

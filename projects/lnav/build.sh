#!/bin/bash -eu

cd "$SRC/lnav" && ./autogen.sh
mkdir -p "$BUILD" && cd "$BUILD"
"$SRC/lnav/configure" CXXFLAGS="-O2 $CXXFLAGS"
make -j "$(nproc)" V=1

#!/bin/bash -eu

cd "$SRC/redex" && autoreconf -ivf
mkdir -p "$BUILD" && cd "$BUILD"
"$SRC/redex/configure" --enable-protobuf --disable-tests --disable-kotlin-tests CXXFLAGS="-std=gnu++20 -Wno-error $CXXFLAGS"
make -j "$(nproc)" V=1

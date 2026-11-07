#!/bin/bash -eu

m() { meson setup "$BUILD/$1" "$2" --buildtype=release -Dcpp_args="$CXXFLAGS -Qunused-arguments"; ninja -C "$BUILD/$1" -j "$(nproc)"; }
m auth "$SRC/pdns"
m recursor "$SRC/pdns/pdns/recursordist"
m dnsdist "$SRC/pdns/pdns/dnsdistdist"

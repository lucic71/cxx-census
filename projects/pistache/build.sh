#!/bin/bash -eu

meson setup "$BUILD" "$SRC/pistache" --buildtype=release -Dcpp_args="$CXXFLAGS -Qunused-arguments"
meson compile -C "$BUILD" -j "$(nproc)"

#!/bin/bash -eu

meson setup "$BUILD" "$SRC/waybar" --buildtype=release --force-fallback-for=fmt,spdlog -Dcpp_args="$CXXFLAGS -Qunused-arguments"
ninja -C "$BUILD" -j "$(nproc)"

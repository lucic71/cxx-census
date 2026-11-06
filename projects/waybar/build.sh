#!/bin/bash -eu

meson setup "$BUILD" "$SRC/waybar" --buildtype=release --force-fallback-for=fmt,spdlog
ninja -C "$BUILD" -j "$(nproc)"

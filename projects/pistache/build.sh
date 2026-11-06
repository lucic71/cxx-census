#!/bin/bash -eu

meson setup "$BUILD" "$SRC/pistache" --buildtype=release
meson compile -C "$BUILD" -j "$(nproc)"

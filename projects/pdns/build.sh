#!/bin/bash -eu

meson setup "$BUILD/auth" "$SRC/pdns" --buildtype=release
ninja -C "$BUILD/auth" -j "$(nproc)"
meson setup "$BUILD/recursor" "$SRC/pdns/pdns/recursordist" --buildtype=release
ninja -C "$BUILD/recursor" -j "$(nproc)"
meson setup "$BUILD/dnsdist" "$SRC/pdns/pdns/dnsdistdist" --buildtype=release
ninja -C "$BUILD/dnsdist" -j "$(nproc)"

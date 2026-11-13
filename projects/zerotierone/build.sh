#!/bin/bash -eu

cp -a "$SRC/zerotierone" "$BUILD"
make -C "$BUILD" -j "$(nproc)" CXXFLAGS="-O3 -fstack-protector $CXXFLAGS" CFLAGS="-O3 -fstack-protector $CFLAGS" all selftest

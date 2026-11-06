#!/bin/bash -eu

cp -a "$SRC/zerotierone" "$BUILD"
make -C "$BUILD" -j "$(nproc)" CXXFLAGS="-O3 -fstack-protector $CXXFLAGS" all selftest

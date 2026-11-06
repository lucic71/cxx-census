#!/bin/bash -eu

REPO=https://github.com/google/brunsli.git
COMMIT=c18b9625ef045b0b89ebb4439ae2339e2160df71

if [ ! -d "$SRC" ]; then
  git clone "$REPO" "$SRC"
  git -C "$SRC" checkout "$COMMIT"
  git -C "$SRC" submodule update --init --recursive
fi

cmake -S "$SRC" -B "$BUILD" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD" --config Release -j "$(nproc)"

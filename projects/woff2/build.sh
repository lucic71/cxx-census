#!/bin/bash -eu

REPO=https://github.com/google/woff2.git
COMMIT=7b67e12355fe7da148db5c19d4261f0a498a9537

if [ ! -d "$SRC" ]; then
  git clone "$REPO" "$SRC"
  git -C "$SRC" checkout "$COMMIT"
fi

cmake -S "$SRC" -B "$BUILD"
cmake --build "$BUILD" -j "$(nproc)"

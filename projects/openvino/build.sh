#!/bin/bash -eu

cmake -S "$SRC/openvino" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_WHEEL=OFF
cmake --build "$BUILD" -j "$(nproc)"

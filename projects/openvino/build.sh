#!/bin/bash -eu

cmake -S "$SRC/openvino" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_WHEEL=OFF -DCMAKE_DISABLE_FIND_PACKAGE_RapidJSON=ON
cmake --build "$BUILD" -j "$(nproc)"

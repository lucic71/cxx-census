#!/bin/bash -eu

cd "$SRC/runanywhere-sdks"
cmake --preset linux-release -B "$BUILD" -DRAC_BUILD_BACKENDS=ON -DRAC_BUILD_SERVER=ON -DRAC_GPU_VULKAN=OFF
cmake --build "$BUILD" -j "$(nproc)"

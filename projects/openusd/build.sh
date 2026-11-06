#!/bin/bash -eu

osd() {
  cmake -S "$SRC/opensubdiv" -B "$BUILD/osd" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$BUILD/deps" \
    -DCMAKE_CXX_FLAGS="${CXXFLAGS:-}" -DNO_EXAMPLES=ON -DNO_TUTORIALS=ON -DNO_REGRESSION=ON -DNO_DOC=ON -DNO_OMP=ON \
    -DNO_CUDA=ON -DNO_OPENCL=ON -DNO_DX=ON -DNO_TESTS=ON -DNO_GLEW=ON -DNO_GLFW=ON -DNO_PTEX=ON -DNO_TBB=ON \
    -DOSD_PATCH_SHADER_SOURCE_GLSL=ON && cmake --build "$BUILD/osd" -j "$(nproc)" && cmake --install "$BUILD/osd"
}
osd || { echo "census: dep opensubdiv built without plugin"; rm -rf "$BUILD/osd"; (unset CXXFLAGS; osd); }

cmake -S "$SRC/openusd" -B "$BUILD/usd" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_PREFIX_PATH="$BUILD/deps" -DPXR_BUILD_USDVIEW=OFF
cmake --build "$BUILD/usd" -j "$(nproc)"

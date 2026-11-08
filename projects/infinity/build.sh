#!/bin/bash -eu

deps() { cd "$SRC/infinity" && "$VCPKG_ROOT/vcpkg" install --overlay-ports=ports --x-install-root="$BUILD/vcpkg_installed"; }
deps || { rm -rf "$BUILD/vcpkg_installed" "$VCPKG_ROOT/buildtrees"; echo "census: dep vcpkg built without plugin"; (unset CXXFLAGS; deps); }
cmake -S "$SRC/infinity" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DVCPKG_MANIFEST_INSTALL=OFF -DLLVM_STRIP_EXECUTABLE=/usr/lib/llvm-23/bin/llvm-strip -DCMAKE_CXX_STDLIB_MODULES_JSON=/usr/lib/gcc/x86_64-linux-gnu/15/libstdc++.modules.json
cmake --build "$BUILD" -j "$(nproc)"

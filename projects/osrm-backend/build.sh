#!/bin/bash -eu

T="$BUILD/triplets/x64-linux-census.cmake"
mkdir -p "$BUILD/triplets"
printf 'include($ENV{VCPKG_ROOT}/triplets/x64-linux.cmake)\nset(VCPKG_BUILD_TYPE release)\nset(VCPKG_C_FLAGS "%s")\nset(VCPKG_CXX_FLAGS "%s")\n' "$CFLAGS" "$CXXFLAGS" > "$T"
deps() { env -u CXXFLAGS -u CFLAGS "$VCPKG_ROOT/vcpkg" install --x-manifest-root="$SRC/osrm-backend" \
  --x-install-root="$BUILD/vcpkg_installed" --overlay-triplets="$BUILD/triplets" --triplet=x64-linux-census \
  --clean-buildtrees-after-build --clean-packages-after-build; }
if ! deps; then
  rm -rf "$BUILD/vcpkg_installed" "$VCPKG_ROOT/buildtrees" "$VCPKG_ROOT/packages" ~/.cache/vcpkg
  printf 'set(VCPKG_C_FLAGS "")\nset(VCPKG_CXX_FLAGS "")\n' >> "$T"
  deps
  echo "census: dep vcpkg-ports built without plugin"
fi
C=$("$VCPKG_ROOT/vcpkg" fetch cmake | tail -n 1)
"$C" -S "$SRC/osrm-backend" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-linux-census \
  -DVCPKG_INSTALLED_DIR="$BUILD/vcpkg_installed" -DVCPKG_MANIFEST_INSTALL=OFF
"$C" --build "$BUILD" -j "$(nproc)"

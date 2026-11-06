#!/bin/bash -eu

D="$BUILD/deps"
cd "$SRC/boost_1_89_0" && ./bootstrap.sh
echo "using clang : 23 : clang++-23 ;" > "$BUILD/user-config.jam"
b2() {
  ./b2 -j"$(nproc)" --user-config="$BUILD/user-config.jam" --build-dir="$BUILD/boost" --prefix="$D" \
    toolset=clang-23 link=shared variant=release "$@" install \
    --with-context --with-coroutine --with-iostreams --with-url --with-container --with-regex --with-thread
}
b2 cxxflags="$CXXFLAGS" || { rm -rf "$BUILD/boost"; echo "census: dep boost built without plugin"; env -u CXXFLAGS b2; }
cmk() {
  cmake -S "$1" -B "$BUILD/$2" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$D" "${@:3}"
  ninja -C "$BUILD/$2" -j "$(nproc)" install
}
cmk "$SRC/curl" curl -DCURL_USE_OPENSSL=ON -DBUILD_TESTING=OFF -DBUILD_CURL_EXE=OFF
cmk "$SRC/libgit2" libgit2 -DBUILD_TESTS=OFF -DBUILD_CLI=OFF
cmk "$SRC/blake3/c" blake3 -DBUILD_SHARED_LIBS=ON

export PKG_CONFIG_PATH="$D/lib/pkgconfig" BOOST_ROOT="$D" LD_LIBRARY_PATH="$D/lib"
meson setup "$BUILD/nix" "$SRC/nix" --buildtype=release -Djson-schema-checks=false -Dcpp_link_args="-Wl,-rpath,$D/lib"
ninja -C "$BUILD/nix" -j "$(nproc)"

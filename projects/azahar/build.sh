#!/bin/bash -eu

ffmpeg() {
  rm -rf "$BUILD/ffmpeg" && mkdir -p "$BUILD/ffmpeg" && cd "$BUILD/ffmpeg" \
    && "$SRC/ffmpeg/configure" --prefix="$BUILD/deps" --cc="$CC" --cxx="$CXX" --extra-cxxflags="$1" \
         --enable-shared --disable-static --disable-programs --disable-doc \
    && make -j"$(nproc)" V=1 install
}
ffmpeg "${CXXFLAGS:-}" || { ffmpeg ""; echo "census: dep ffmpeg built without plugin"; }
export PKG_CONFIG_PATH="$BUILD/deps/lib/pkgconfig"
cmake -S "$SRC/azahar" -B "$BUILD/azahar" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$BUILD/deps" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD/azahar" -j "$(nproc)"

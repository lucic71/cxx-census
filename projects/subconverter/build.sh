#!/bin/bash -eu

D="$BUILD/deps"
qjs() {
  cmake -S "$SRC/quickjspp" -B "$BUILD/qjs" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="${CXXFLAGS:-}" \
    && cmake --build "$BUILD/qjs" --target quickjs -j "$(nproc)" \
    && install -D -m644 "$BUILD/qjs/quickjs/libquickjs.a" "$D/lib/quickjs/libquickjs.a" \
    && install -D -m644 -t "$D/include/quickjs" "$SRC/quickjspp/quickjs/quickjs.h" "$SRC/quickjspp/quickjs/quickjs-libc.h" \
    && install -m644 "$SRC/quickjspp/quickjspp.hpp" "$D/include/"
}
cron() {
  cmake -S "$SRC/libcron" -B "$BUILD/cron" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$D" \
    -DCMAKE_CXX_FLAGS="${CXXFLAGS:-}" && cmake --build "$BUILD/cron" --target libcron -j "$(nproc)" \
    && cmake --install "$BUILD/cron"
}
qjs || { echo "census: dep quickjs built without plugin"; rm -rf "$BUILD/qjs"; (unset CXXFLAGS; qjs); }
cron || { echo "census: dep libcron built without plugin"; rm -rf "$BUILD/cron"; (unset CXXFLAGS; cron); }

cmake -S "$SRC/subconverter" -B "$BUILD/subconverter" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_PREFIX_PATH="$D"
cmake --build "$BUILD/subconverter" -j "$(nproc)"

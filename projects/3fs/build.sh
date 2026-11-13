#!/bin/bash -eu

fuse() { rm -rf "$BUILD/fuse" && meson setup "$BUILD/fuse" /opt/fuse-3.16.2 --prefix="$BUILD/deps" --libdir=lib \
  -Ddefault_library=both -Dutils=false -Dexamples=false -Dtests=false && ninja -C "$BUILD/fuse" install; }
fuse || { env -u CXXFLAGS -u CFLAGS bash -c "$(declare -f fuse); fuse" && echo "census: dep libfuse built without plugin"; }
cat > "$BUILD/clang++" <<'W'
#!/bin/bash
args=()
for a; do [ "$a" = -fcoroutines-ts ] || args+=("$a"); done
[[ $PWD == */apache-arrow-cpp* && "$*" == */arrow/ipc/* ]] && args+=(-fdelayed-template-parsing)
exec clang++-23 "${args[@]}" -Wno-error
W
chmod +x "$BUILD/clang++"
export CXX="$BUILD/clang++" CXXFLAGS="$CXXFLAGS -DFMT_CONSTEVAL= -include cstdint -include fstream -Wno-error=extraneous-template-head -Wno-error=missing-template-arg-list-after-template-kw" CPATH="$BUILD/deps/include" \
  LIBRARY_PATH="$BUILD/deps/lib" LD_LIBRARY_PATH="$BUILD/deps/lib"
cmake -S "$SRC/3fs" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release -DSHUFFLE_METHOD=g++11 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$BUILD" -j "$(nproc)"

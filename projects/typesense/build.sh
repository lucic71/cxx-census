#!/bin/bash -eu

w="-Wno-error -Wno-unknown-warning-option -Wno-fuse-ld-path -Wno-error=implicit-function-declaration"
w="$w -Wno-error=int-conversion -Wno-error=unterminated-string-initialization"
mkdir -p "$BUILD/cc"
printf '#!/bin/sh\nexec %s "$@" %s\n' /usr/lib/llvm-23/bin/clang "$w" > "$BUILD/cc/clang"
printf '#!/bin/sh\ncase "$*" in *onnxruntime.build_tmpdir*) set -- "$@" -fdelayed-template-parsing;; esac\nexec %s "$@" %s\n' \
  /usr/lib/llvm-23/bin/clang++ "$w -include cstdint $CXXFLAGS" > "$BUILD/cc/clang++"
chmod +x "$BUILD/cc/clang" "$BUILD/cc/clang++"
opts=()
for f in $CXXFLAGS -include cstdint; do opts+=(--cxxopt="$f" --host_cxxopt="$f"); done
export LC_ALL=C.UTF-8
cd "$SRC/typesense"
bazel --output_user_root="$BUILD" build --jobs="$(nproc)" --repo_env=CC="$BUILD/cc/clang" "${opts[@]}" //:typesense-server

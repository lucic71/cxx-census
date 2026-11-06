#!/bin/bash -eu

opts=()
for f in $CXXFLAGS; do opts+=(--cxxopt="$f" --host_cxxopt="$f"); done
cd "$SRC/typesense"
bazel --output_user_root="$BUILD" build --jobs="$(nproc)" --repo_env=CC="$CC" --repo_env=CXX="$CXX" \
  "${opts[@]}" //:typesense-server

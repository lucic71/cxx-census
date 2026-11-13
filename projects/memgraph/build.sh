#!/bin/bash -eu

cd "$SRC/memgraph"
mkdir -p "$BUILD" && ln -sfn "$BUILD" build
F=$(python3 -c 'import json,os,shlex; print(json.dumps(shlex.split(os.environ["CXXFLAGS"]) + ["-fno-builtin-std-forward_like"]))')
FC=$(python3 -c 'import json,os,shlex; print(json.dumps(shlex.split(os.environ["CFLAGS"])))')
unset CXXFLAGS CFLAGS
conan profile detect --force
conan config install conan_config
conan remote add memgraph-recipes "$PWD/conan_recipes" -t local-recipes-index --force
conan install . --build=missing -pr:h default -pr:h memgraph_linux_base -pr:b memgraph_build_profile \
  -s build_type=Release -s os.distro=ubuntu-24.04 -o "&:bundled_toolchain=False" --lockfile-partial \
  -c:a tools.build:compiler_executables='{"c": "clang-23", "cpp": "clang++-23"}' -c:a tools.build:cxxflags="$F" -c:a tools.build:cflags="$FC" \
  -c:a 'aws-sdk-cpp/*:tools.cmake.cmaketoolchain:extra_variables={"AWS_SDK_WARNINGS_ARE_ERRORS": "OFF"}'
source build/generators/conanbuild.sh
cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DMG_TOOLCHAIN_ROOT=/usr -DMG_ENABLE_TESTING=OFF
cmake --build --preset conan-release -j "$(nproc)"

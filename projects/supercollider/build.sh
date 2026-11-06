#!/bin/bash -eu

cmake -S "$SRC/supercollider" -B "$BUILD" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DSYSTEM_BOOST=ON -DSYSTEM_YAMLCPP=ON -DSC_EL=ON -DSC_VIM=ON -DSC_QT=ON -DSC_IDE=ON
cmake --build "$BUILD" -j "$(nproc)"

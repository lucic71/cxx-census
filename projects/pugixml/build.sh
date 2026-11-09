#!/bin/bash -eu

cd "$SRC/pugixml"
$CXX $CXXFLAGS -fno-exceptions -DPUGIXML_NO_EXCEPTIONS -O2 -Isrc -o "$BUILD/pugixml_test" src/pugixml.cpp tests/*.cpp

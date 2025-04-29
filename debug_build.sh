#!/bin/bash

BUILD_DIR="build_debug"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)

echo "Debug build complete. Executable located in: $BUILD_DIR"

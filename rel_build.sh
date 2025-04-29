#!/bin/bash

BUILD_DIR="build_release"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

echo "Release build complete. Executable located in: $BUILD_DIR"

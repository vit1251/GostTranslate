#!/bin/sh

mkdir -p build
rm -rf build
mkdir -p build
cd build
cmake ..
make

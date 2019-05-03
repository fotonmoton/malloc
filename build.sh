#!/bin/bash

PWD=$(pwd)
OUT_DIR="$PWD/out"
BLD_DIR="$PWD/bld"

meson $BLD_DIR --includedir=$OUT_DIR --libdir=$OUT_DIR --bindir=$OUT_DIR --prefix=$OUT_DIR
ninja -C $BLD_DIR
ninja -C $BLD_DIR install
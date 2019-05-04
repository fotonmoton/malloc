#!/bin/bash

PWD=$(pwd)
OUT_DIR="$PWD/out"
RELEASE_BLD_DIR="$PWD/bld"
DEBUG_BLD_DIR="$PWD/debug_bld"

LIB="libft_malloc.dylib"
LINK="libft_malloc.so"


meson $RELEASE_BLD_DIR --prefix=$OUT_DIR --libdir=$OUT_DIR --includedir=$OUT_DIR --buildtype=release
meson $DEBUG_BLD_DIR --buildtype=debug

ninja -C $DEBUG_BLD_DIR
ninja -C $RELEASE_BLD_DIR
ninja -C $RELEASE_BLD_DIR install

ln -sf "$OUT_DIR/$LIB" "$PWD/$LINK"

#!/bin/bash
pushd Cache_Install
make
popd
mkdir -p bin
rm -f bin/Cache_Install.bin
cp Cache_Install/Cache_Install.bin bin/Cache_Install.bin
rm -f Cache_Install/Cache_Install.bin

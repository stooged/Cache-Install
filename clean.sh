#!/bin/bash
pushd tool
make clean
popd
pushd Cache_Install
make clean
popd
rm -f html_payload/Cache_Install.html
rm -f bin/Cache_Install.bin


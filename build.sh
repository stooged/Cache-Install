#!/bin/bash
set -e
pushd tool
make
popd
pushd Cache_Install
make
popd
mkdir -p bin
rm -f bin/Cache_Install.bin
cp Cache_Install/Cache_Install.bin bin/Cache_Install.bin
mkdir -p html_payload
tool/bin2js bin/Cache_Install.bin > html_payload/payload.js
FILESIZE=$(stat -c%s "bin/Cache_Install.bin")
PNAME=$"Cache Install"
cp exploit.template html_payload/Cache_Install.html
sed -i -f - html_payload/Cache_Install.html << EOF
s/#NAME#/$PNAME/g
s/#BUF#/$FILESIZE/g
s/#PAY#/$(cat html_payload/payload.js)/g
EOF
rm -f Cache_Install/Cache_Install.bin
rm -f html_payload/payload.js

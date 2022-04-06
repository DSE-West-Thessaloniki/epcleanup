#!/bin/bash
set -e

PATH=/usr/lib/mxe/usr/bin:$PATH
export PATH

cp /src/* /build/
cd /build
/lib/mxe/usr/i686-w64-mingw32.static/qt5/bin/qmake && make
cp release/epcleanup.exe /result/

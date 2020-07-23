#!/bin/bash

git submodule update --init --recursive --remote

cmake -DCMAKE_BUILD_TYPE=Release ./
cmake --build . --config Release

mkdir -p ./build/linux64/Release/modules/lua-module
cp ./vendors/luajit/bin/linux64/lua51.so ./build/linux64/Release/modules/lua-module/
cp ./build/linux64/Release/liblua-module.so ./build/linux64/Release/modules/lua-module/


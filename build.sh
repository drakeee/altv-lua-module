#!/bin/bash

git submodule update --init --recursive --remote
cd vendors/luajit/ && make
mkdir -p {include,bin/linux64,lib/linux64}
cp ./src/{lauxlib.h,lua.h,lua.hpp,luaconf.h,luajit.h,lualib.h} ./include/
cp ./src/{libluajit.a,libluajit.so} ./lib/linux64/
cp ./src/{luajit,libluajit.so} ./bin/linux64/
mv ./bin/linux64/libluajit.so ./bin/linux64/lua51.so

cd ../..
cmake -DCMAKE_BUILD_TYPE=Release ./
cmake --build . --config Release

mkdir -p ./build/linux64/Release/modules/lua-module
cp ./vendors/luajit/bin/linux64/lua51.so ./build/linux64/Release/modules/lua-module/
cp ./build/linux64/Release/liblua-module.so ./build/linux64/Release/modules/lua-module/


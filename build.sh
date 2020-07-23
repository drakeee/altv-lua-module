#!/bin/bash

git submodule update --init
cd vendors/luajit/ && make
mkdir -p {include,bin/linux64,lib/linux64}
cp ./src/{lauxlib.h,lua.h,lua.hpp,luaconf.h,luajit.h,lualib.h} ./include/
cp ./src/{libluajit.a,libluajit.so} ./lib/linux64/
cp ./src/{luajit,libluajit.so} ./bin/linux64/
mv ./bin/linux64/libluajit.so ./bin/linux64/lua51.so

cd ../..
cmake ./ && make

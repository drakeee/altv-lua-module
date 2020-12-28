#!/bin/bash

#git submodule update --init --recursive --remote

cmake -DCMAKE_BUILD_TYPE=Release ./
cmake --build . --config Release

mkdir -p artifacts/lua-module/modules
cp ./libs/lua51/linux64/lua51.so ./artifacts/lua-module
cp ./build/linux64/Release/liblua-module.so ./artifacts/lua-module
ln -rs ./artifacts/lua-module/lua51.so ./artifacts/lua-module/libluajit-5.1.so.2

cd artifacts
zip --symlinks -r lua-module-linux.zip lua-module/*
cd ..

#mkdir -p ./build/linux64/Release/modules/lua-module
#cp -r ./scripts ./build/linux64/Release/modules/lua-module/
#cp ./libs/lua51/linux64/lua51.so ./build/linux64/Release/modules/lua-module/
#cp ./libs/mariadb/linux64/libmariadb.so ./build/linux64/Release/modules/lua-module/
#cp ./libs/sqlite3/linux64/sqlite3.so ./build/linux64/Release/modules/lua-module/
#cp ./build/linux64/Release/liblua-module.so ./build/linux64/Release/modules/lua-module/


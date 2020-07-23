@echo off

git submodule update --init --recursive --remote

if not exist build mkdir build
cd build

cmake -G"Visual Studio 16" -A x64 ..\\
cmake --build . --config Release

cd ..

xcopy vendors\luajit\bin\win64\lua51.dll build\win64\Release\modules\lua-module\ /Y
xcopy build\win64\Release\lua-module.dll build\win64\Release\modules\lua-module\ /Y

7z a -tzip lua-module-windows.zip -r build\win64\Release\modules\lua-module


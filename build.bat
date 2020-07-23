@echo off

git submodule update --init --recursive --remote
REM cd vendors/luajit/src/
REM call msvcbuild.bat

REM cd ..
REM if not exist include mkdir include
REM if not exist bin\\win64 mkdir bin\\win64
REM if not exist lib\\win64 mkdir lib\\win64

REM for %%I in (src\lauxlib.h src\lua.h src\lua.hpp src\luaconf.h src\luajit.h src\lualib.h) do xcopy %%I include\\ /Y
REM for %%I in (src\lua51.lib src\luajit.lib) do xcopy %%I lib\\win64\\ /Y
REM for %%I in (src\lua51.dll src\luajit.exe) do xcopy %%I bin\\win64\\ /Y

REM cd ..\\..
if not exist build mkdir build
cd build

cmake -G"Visual Studio 16" -A x64 ..\\
cmake --build . --config Release

cd ..

xcopy vendors\\luajit\\bin\\win64\\lua51.dll build\\win64\\Release\\modules\\lua-module\\ /Y
xcopy build\\win64\\Release\\lua-module.dll build\\win64\\Release\\modules\\lua-module\\ /Y


@echo on

REM git submodule update --init --recursive --remote

if not exist build mkdir build
cd build

cmake -G"Visual Studio 16" -A x64 ..\\
cmake --build . --config Release

cd ..

mkdir artifacts

xcopy libs\lua51\win64\lua51.dll artifacts\lua-module\ /Y
REM xcopy libs\mariadb\win64\libmariadb.dll build\win64\Release\modules\lua-module\ /Y
REM xcopy libs\sqlite3\win64\sqlite3.dll build\win64\Release\modules\lua-module\ /Y
xcopy build\win64\Release\lua-module.dll artifacts\lua-module\ /Y

cd artifacts
if not exist "lua-module\modules" mkdir "lua-module\modules"
7z a -tzip "lua-module-windows.zip" -r lua-module

cd ..

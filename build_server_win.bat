@echo on

REM git submodule update --init --recursive --remote

if not exist build mkdir build
cd build

cmake -G"Visual Studio 16" -DMODULE_TYPE=SERVER -A x64 ..\\
cmake --build . --config Release

cd ..

mkdir artifacts

xcopy libs\lua51\win64\lua51.dll artifacts\lua-server-module\ /Y
REM xcopy libs\mariadb\win64\libmariadb.dll build\win64\Release\modules\lua-module\ /Y
REM xcopy libs\sqlite3\win64\sqlite3.dll build\win64\Release\modules\lua-module\ /Y
xcopy build\win64\Release\lua-module.dll artifacts\lua-server-module\ /Y

cd artifacts
if not exist "lua-server-module\modules" mkdir "lua-server-module\modules"
7z a -tzip "lua-server-module-windows.zip" -r lua-server-module

cd ..

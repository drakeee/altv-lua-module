@echo on

REM git submodule update --init --recursive --remote

if not exist build mkdir build
cd build

cmake -G"Visual Studio 16 2019" -DMODULE_TYPE=CLIENT -A x64 ..\\
cmake --build . --config Release

cd ..

mkdir artifacts

xcopy libs\lua51\win64\lua51.dll artifacts\lua-client-module\ /Y
REM xcopy libs\mariadb\win64\libmariadb.dll build\win64\Release\modules\lua-module\ /Y
REM xcopy libs\sqlite3\win64\sqlite3.dll build\win64\Release\modules\lua-module\ /Y
xcopy build\win64\Release\lua-client-module.dll artifacts\lua-client-module\ /Y
xcopy build\win64\Release\lua-client-module-static.lib artifacts\ /Y

cd artifacts
REM if not exist "lua-client-module\modules" mkdir "lua-client-module\modules"
7z a -tzip "lua-client-module-windows.zip" -r lua-client-module

cd ..

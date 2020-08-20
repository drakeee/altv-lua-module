@echo on

git submodule update --init --recursive --remote

if not exist build mkdir build
cd build

cmake -G"Visual Studio 16" -A x64 ..\\
cmake --build . --config Release

cd ..

xcopy scripts build\win64\Release\modules\lua-module\scripts\ /Y /E
xcopy libs\lua51\win64\lua51.dll build\win64\Release\modules\lua-module\ /Y
xcopy libs\mariadb\win64\libmariadb.dll build\win64\Release\modules\lua-module\ /Y
xcopy libs\sqlite3\win64\sqlite3.dll build\win64\Release\modules\lua-module\ /Y
xcopy build\win64\Release\lua-module.dll build\win64\Release\modules\lua-module\ /Y

mkdir lua-module
xcopy build\win64\Release\modules\lua-module lua-module\ /Y /E

7z a -tzip "lua-module-windows.zip" -r lua-module\*


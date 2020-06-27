# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("altv-lua-module")

set(PROJECT_MODULE_NAME "lua-module")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "./src/*.h" "./src/*.hpp" "./src/*.cpp")

include_directories(
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/vendors/luajit/include"
	"${PROJECT_SOURCE_DIR}/src/vendors/cpp-sdk"
)

add_library(
	${PROJECT_MODULE_NAME} SHARED
	${PROJECT_SOURCE_FILES}
)

if(UNIX)
	target_link_libraries(${PROJECT_MODULE_NAME} ${PROJECT_SOURCE_DIR}/src/vendors/luajit/lib/linux64/libluajit.a)
else()
	target_link_libraries(${PROJECT_MODULE_NAME}
	${PROJECT_SOURCE_DIR}/src/vendors/luajit/lib/win64/lua51.lib
	${PROJECT_SOURCE_DIR}/src/vendors/luajit/lib/win64/luajit.lib
	)
endif()
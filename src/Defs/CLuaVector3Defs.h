#pragma once

#include <Main.h>

class CLuaVector3Defs
{
public:
	static const char* ClassName;
	static void Init(lua_State *L);

private:
	static int create(lua_State* L);
	static int destroy(lua_State* L);
	static int tostring(lua_State* L);
	static int add(lua_State* L);
};
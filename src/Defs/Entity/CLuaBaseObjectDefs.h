#pragma once

#include <Main.h>

class CLuaBaseObjectDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int tostring(lua_State* L);

	static int GetType(lua_State* L);
	static int HasMetaData(lua_State* L);
	static int GetMetaData(lua_State* L);
	static int SetMetaData(lua_State* L);
	static int DeleteMetaData(lua_State* L);
	static int Destroy(lua_State* L);
};
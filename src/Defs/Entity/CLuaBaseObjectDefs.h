#pragma once

#include <Main.h>

class CLuaBaseObjectDefs
{
public:
	static void Init(lua_State* L);

private:
	static const std::list<std::string> entityTypes;

	static int tostring(lua_State* L);

	static int GetType(lua_State* L);
	static int HasMetaData(lua_State* L);
	static int GetMetaData(lua_State* L);
	static int SetMetaData(lua_State* L);
	static int DeleteMetaData(lua_State* L);
};
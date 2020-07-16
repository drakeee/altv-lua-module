#pragma once

#include <Main.h>

class CLuaCheckpointDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int Create(lua_State* L);
	static int GetCheckpointType(lua_State* L);
	static int GetHeight(lua_State* L);
	static int GetRadius(lua_State* L);
	static int GetColor(lua_State* L);
};
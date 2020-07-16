#pragma once

#include <Main.h>

class CLuaBlipDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int Create(lua_State* L);
	static int CreateAttached(lua_State* L);

	static int IsGlobal(lua_State* L);
	static int GetTarget(lua_State* L);

	static int IsAttached(lua_State* L);
	static int AttachedTo(lua_State* L);
	static int GetBlipType(lua_State* L);

	static int SetSprite(lua_State* L);
	static int SetColor(lua_State* L);
	static int SetRoute(lua_State* L);
	static int SetRouteColor(lua_State* L);
};
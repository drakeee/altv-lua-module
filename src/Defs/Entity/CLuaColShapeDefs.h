#pragma once

#include <Main.h>

#ifdef ALT_SERVER_API
class CLuaColShapeDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int CreateCircle(lua_State* L);
	static int CreateCube(lua_State* L);
	static int CreateCylinder(lua_State* L);
	static int CreateRectangle(lua_State* L);
	static int CreateSphere(lua_State* L);

	static int GetColshapeType(lua_State* L);

	static int IsEntityIn(lua_State* L);
	static int IsPointIn(lua_State* L);
};
#endif
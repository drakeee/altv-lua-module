#pragma once

#include "Main.h"

typedef alt::Vector<float, 3, alt::PointLayout> Vector3fp;

class CLuaVector3Defs
{
public:
	static void Init(lua_State *L);
	static int create(lua_State *L);
	static int destroy(lua_State *L);
	static int tostring(lua_State *L);
	static int add(lua_State* L);

private:
	static void InitClass(lua_State* L);
	static void InitVariables(lua_State* L);
};
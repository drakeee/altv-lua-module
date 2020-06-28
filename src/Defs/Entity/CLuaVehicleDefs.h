#pragma once

#include <Main.h>

class CLuaVehicleDefs
{
public:
	static void init(lua_State* L);
	static void initClass(lua_State* L);

	static int CreateVehicle(lua_State* L);
	static int SetVehiclePosition(lua_State* L);
	static int GetVehiclePosition(lua_State* L);
};
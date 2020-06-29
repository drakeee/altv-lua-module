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
	static int SetVehicleBodyHealth(lua_State* L);
	static int SetVehicleEngineHealth(lua_State* L);
	static int GetVehicleBodyHealth(lua_State* L);
	static int GetVehicleEngineHealth(lua_State* L);
	static int SetVehiclePrimaryColor(lua_State* L);
	static int SetVehicleSecondaryColor(lua_State* L);
	static int GetVehiclePrimaryColor(lua_State* L);
	static int GetVehicleSecondaryColor(lua_State* L);
};

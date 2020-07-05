#pragma once

#include <Main.h>

class CLuaVehicleDefs
{
private:
	static void InitClass(lua_State* L);

	static std::list<alt::IVehicle *> vehicles;

public:
	static void Init(lua_State* L);

	static int tostring(lua_State* L);
	static int destroy(lua_State* L);
	static int next(lua_State* L);
	static int pairs(lua_State* L);
	static int ipairs(lua_State* L);

	static int CreateVehicle(lua_State* L);
	static int SetVehiclePosition(lua_State* L);
	static int GetVehiclePosition(lua_State* L);
};
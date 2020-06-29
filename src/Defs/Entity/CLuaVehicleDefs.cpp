#include "CLuaVehicleDefs.h"

void CLuaVehicleDefs::init(lua_State* L)
{
	CLuaVehicleDefs::initClass(L);
}

void CLuaVehicleDefs::initClass(lua_State* L)
{
	lua_newclass(L, "Vehicle");

	// CREATE VEHICLE
	lua_registerfunction(L, "createVehicle", CLuaVehicleDefs::CreateVehicle);
	lua_registeroop(L, "new", "createVehicle");

	// VEHICLE POSITION

	lua_registerfunction(L, "setVehiclePosition", CLuaVehicleDefs::SetVehiclePosition);
	lua_registerfunction(L, "getVehiclePosition", CLuaVehicleDefs::GetVehiclePosition);

	lua_registeroop(L, "setPosition", "setVehiclePosition");
	lua_registeroop(L, "getPosition", "getVehiclePosition");

	lua_registervariable(L, "position", "setVehiclePosition", "getVehiclePosition");

	// BODY AND ENGINE HELTH

	lua_registerfunction(L, "setVehicleBodyHealth", CLuaVehicleDefs::SetVehicleBodyHealth);
	lua_registerfunction(L, "setVehicleEngineHealth", CLuaVehicleDefs::SetVehicleEngineHealth);
	lua_registerfunction(L, "getVehicleBodyHealth", CLuaVehicleDefs::GetVehicleBodyHealth);
	lua_registerfunction(L, "getVehicleEngineHealth", CLuaVehicleDefs::GetVehicleEngineHealth);

	lua_registervariable(L, "bodyhealth", "setVehicleBodyHealth", "getVehicleBodyHealth");
	lua_registervariable(L, "enginehealth", "setVehicleEngineHealth", "getVehicleEngineHealth");

	// VEHICLE COLORS

	lua_registerfunction(L, "setVehiclePrimaryColor", CLuaVehicleDefs::SetVehiclePrimaryColor);
	lua_registerfunction(L, "setVehicleSecondaryColor", CLuaVehicleDefs::SetVehicleSecondaryColor);
	lua_registerfunction(L, "getVehiclePrimaryColor", CLuaVehicleDefs::GetVehiclePrimaryColor);
	lua_registerfunction(L, "getVehicleSecondaryColor", CLuaVehicleDefs::GetVehicleSecondaryColor);


	lua_registervariable(L, "primarycolor", "setVehiclePrimaryColor", "getVehiclePrimaryColor");
	lua_registervariable(L, "secondarycolor", "setVehicleSecondaryColor", "getVehicleSecondaryColor");

	lua_registerclass(L);
}

int CLuaVehicleDefs::CreateVehicle(lua_State* L)
{
	unsigned int modelHash;
	alt::Position position;
	alt::Rotation rotation;

	CArgReader argReader(L);
	argReader.ReadNumber(modelHash);
	argReader.ReadPosition(position);
	argReader.ReadRotation(rotation);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	/*argReader.ReadNumber(position[0]);
	argReader.ReadNumber(position[1]);
	argReader.ReadNumber(position[2]);

	argReader.ReadNumber(rotation[0]);
	argReader.ReadNumber(rotation[1]);
	argReader.ReadNumber(rotation[2]);*/

	//alt::Position pos(position[0], position[1], position[2]);
	//alt::Rotation rot(rotation[0], rotation[1], rotation[2]);

	alt::Ref<alt::IVehicle> vehicle = Core->CreateVehicle(
		modelHash,
		position,
		rotation
	);

	if (vehicle.Get() != nullptr)
		lua_userdata(L, "Vehicle", vehicle.Get());
	else
		lua_pushnil(L);

#ifdef _DEBUG
	Core->LogInfo("Vehicle(" + std::to_string(modelHash) + ", {"+ std::to_string(position.x) +", "+ std::to_string(position.y) +", "+ std::to_string(position.z) +"}, {" + std::to_string(rotation.roll) + ", " + std::to_string(rotation.pitch) + ", " + std::to_string(rotation.yaw) + "})");
#endif

	return 1;
}

int CLuaVehicleDefs::SetVehiclePosition(lua_State* L)
{
	alt::IVehicle *vehicle;
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);
	argReader.ReadPosition(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetPosition(position);

#ifdef _DEBUG
	Core->LogInfo("SetVehiclePosition("+std::to_string(vehicle->GetModel())+", {" + std::to_string(position.x) + ", "+ std::to_string(position.y) +", "+ std::to_string(position.z) +"})");
#endif

	lua_pushboolean(L, 1);

	return 1;
}

int CLuaVehicleDefs::GetVehiclePosition(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	position = vehicle->GetPosition();
	Vector3fp* t = new Vector3fp(position);

	lua_userdata(L, "Vector3", t);

	return 1;
}

int CLuaVehicleDefs::SetVehicleBodyHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number health;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);
	argReader.ReadNumber(health);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetBodyHealth(health);

	return 1;
}

int CLuaVehicleDefs::SetVehicleEngineHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number health;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);
	argReader.ReadNumber(health);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetEngineHealth(health);

	return 1;
}

int CLuaVehicleDefs::GetVehicleBodyHealth(lua_State* L)
{
	alt::IVehicle* vehicle;	
	lua_Number health;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	health = vehicle->GetBodyHealth();

	lua_pushnumber(L, health);

	return 1;
}

int CLuaVehicleDefs::GetVehicleEngineHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number health;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	health = vehicle->GetEngineHealth();

	lua_pushnumber(L, health);

	return 1;
}

int CLuaVehicleDefs::SetVehiclePrimaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number id;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);
	argReader.ReadNumber(id);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetPrimaryColor(id);

	return 1;
}

int CLuaVehicleDefs::SetVehicleSecondaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number id;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);
	argReader.ReadNumber(id);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetSecondaryColor(id);

	return 1;
}

int CLuaVehicleDefs::GetVehiclePrimaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number color;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	color = vehicle->GetPrimaryColor();

	lua_pushnumber(L, color);

	return 1;
}

int CLuaVehicleDefs::GetVehicleSecondaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	lua_Number color;

	CArgReader argReader(L);
	argReader.ReadUserData(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	color = vehicle->GetSecondaryColor();

	lua_pushnumber(L, color);

	return 1;
}

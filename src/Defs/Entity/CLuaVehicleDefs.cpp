#include "CLuaVehicleDefs.h"

void CLuaVehicleDefs::init(lua_State* L)
{
	CLuaVehicleDefs::initClass(L);
}

void CLuaVehicleDefs::initClass(lua_State* L)
{
	lua_newclass(L, "Vehicle");

	lua_registerfunction(L, "createVehicle", CLuaVehicleDefs::CreateVehicle);
	lua_registerfunction(L, "setVehiclePosition", CLuaVehicleDefs::SetVehiclePosition);
	lua_registerfunction(L, "getVehiclePosition", CLuaVehicleDefs::GetVehiclePosition);


	lua_registeroop(L, "new", "createVehicle");
	lua_registeroop(L, "setPosition", "setVehiclePosition");
	lua_registeroop(L, "getPosition", "getVehiclePosition");

	lua_registervariable(L, "position", "setVehiclePosition", "getVehiclePosition");

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
#include "Main.h"

std::list<alt::IVehicle*> CLuaVehicleDefs::vehicles;

void CLuaVehicleDefs::Init(lua_State* L)
{
	CLuaVehicleDefs::InitClass(L);
}

void CLuaVehicleDefs::InitClass(lua_State* L)
{
	lua_globalfunction(L, "createVehicle", CreateVehicle);
	lua_globalfunction(L, "setVehiclePosition", SetVehiclePosition);
	lua_globalfunction(L, "getVehiclePosition", GetVehiclePosition);

	lua_beginclass(L, "Vehicle", "Entity");
	{
		lua_classmeta(L, "__gc", CLuaVehicleDefs::destroy);
		lua_classmeta(L, "__next", next);
		lua_classmeta(L, "__pairs", pairs);
		lua_classmeta(L, "__ipairs", ipairs);

		lua_classfunction(L, "new", "createVehicle");
		//lua_classfunction(L, "setPosition", "setVehiclePosition");
		//lua_classfunction(L, "getPosition", "getVehiclePosition");

		//lua_classvariable(L, "position", "setPosition", "getPosition");
	}
	lua_endclass(L);
}

/*


	auto allVehicle = vehicles;

	lua_newtable(L);
	int index = 1;
	for(auto vehicle : allVehicle)
	{
		Core->LogInfo("for: " + std::to_string(vehicle->GetModel()));
		lua_pushnumber(L, index);
		lua_pushuserdata(L, "Vehicle", vehicle);
		lua_rawset(L, -3);

		index++;
	}

	lua_stacktrace(L, "CLuaVehicleDefs::ipairs");
*/

int CLuaVehicleDefs::destroy(lua_State* L)
{
	Core->LogInfo("CLuaVehicleDefs::destroy");

	return 0;
}

int CLuaVehicleDefs::next(lua_State* L)
{
	Core->LogInfo("CLuaVehicleDefs::next");

	return 0;
}

int CLuaVehicleDefs::pairs(lua_State* L)
{
	

	return 0;
}

int CLuaVehicleDefs::ipairs(lua_State* L)
{
	Core->LogInfo("CLuaVehicleDefs::ipairs");

	//alt::ICore::Instance().GetVehicles();
	/*for (size_t i = 0; i < allVehicle.GetSize(); i++)
	{
		Core->LogInfo("Index: " + std::to_string(allVehicle[i]->GetModel()));
	}*/

	lua_stacktrace(L, "CLuaVehicleDefs::ipairs");

	return 1;
}

int CLuaVehicleDefs::tostring(lua_State* L)
{
	return 0;
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

	alt::ICore::Instance().GetVehicles();

	if (vehicle.Get() != nullptr)
	{
		lua_pushuserdata(L, "Vehicle", vehicle.Get());

		vehicles.push_back(vehicle.Get());

		Core->LogInfo("SizeVehicle: " + std::to_string(vehicles.size()));
	}
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

#ifdef _DEBUG
	printf("GetPosition: %p\n", t);
#endif

	//lua_userdata(L, "Vector3", t, false);

	return 1;
}
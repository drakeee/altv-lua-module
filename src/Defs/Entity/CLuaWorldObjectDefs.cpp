#include <Main.h>

const char* CLuaWorldObjectDefs::ClassName = "WorldObject";
void CLuaWorldObjectDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaWorldObjectDefs::Init");

	lua_globalfunction(L, "setEntityPosition", SetPosition);
	lua_globalfunction(L, "getEntityPosition", GetPosition);

	lua_globalfunction(L, "setEntityDimension", SetDimension);
	lua_globalfunction(L, "getEntityDimension", GetDimension);

	lua_beginclass(L, ClassName, CLuaBaseObjectDefs::ClassName);
	{
		lua_classfunction(L, "setPosition", SetPosition);
		lua_classfunction(L, "getPosition", GetPosition);
		lua_classfunction(L, "setDimension", SetDimension);
		lua_classfunction(L, "getDimension", GetDimension);

		lua_classvariable(L, "pos", "setPosition", "getPosition");
		lua_classvariable(L, "dimension", "setDimension", "getDimension");
	}
	lua_endclass(L);

	DEBUG_INFO("CLuaWorldObjectDefs::Init ...done");
}

int CLuaWorldObjectDefs::SetPosition(lua_State* L)
{
	alt::IWorldObject* worldObject;
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadBaseObject(worldObject);
	argReader.ReadVector(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	//Core->LogInfo("CLuaWorldObjectDefs::SetPosition: x = " + std::to_string(position.x));
	//Core->LogInfo("CLuaWorldObjectDefs::SetPosition: y = " + std::to_string(position.y));
	//Core->LogInfo("CLuaWorldObjectDefs::SetPosition: z = " + std::to_string(position.z));

	worldObject->SetPosition(position);

	return 0;
}

int CLuaWorldObjectDefs::GetPosition(lua_State* L)
{
	alt::IWorldObject* worldObject;

	//Core->LogInfo("CLuaWorldObjectDefs::GetPosition");

	CArgReader argReader(L);
	argReader.ReadBaseObject(worldObject);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	//Core->LogInfo("CLuaWorldObjectDefs::GetPosition: " + std::to_string(worldObject->GetPosition().x));

	lua_pushvector3(L, worldObject->GetPosition());

	return 1;
}

int CLuaWorldObjectDefs::SetDimension(lua_State* L)
{
	alt::IWorldObject* worldObject;
	int dimension;

	CArgReader argReader(L);
	argReader.ReadBaseObject(worldObject);
	argReader.ReadNumber(dimension);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	worldObject->SetDimension(dimension);

	return 0;
}

int CLuaWorldObjectDefs::GetDimension(lua_State* L)
{
	alt::IWorldObject* worldObject;

	CArgReader argReader(L);
	argReader.ReadBaseObject(worldObject);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, worldObject->GetDimension());

	return 1;
}
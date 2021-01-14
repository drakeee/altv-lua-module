#include <Main.h>

const char* CLuaCheckpointDefs::ClassName = "Checkpoint";
void CLuaCheckpointDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaCheckpointDefs::Init");

	lua_globalfunction(L, "createCheckpoint", Create);
	lua_globalfunction(L, "getCheckpointType", GetCheckpointType);
	lua_globalfunction(L, "getCheckpointHeight", GetHeight);
	lua_globalfunction(L, "getCheckpointRadius", GetRadius);
	lua_globalfunction(L, "getCheckpointColor", GetColor);

	lua_beginclass(L, ClassName);
	{
		lua_classfunction(L, "new", Create);
		lua_classfunction(L, "getCheckpointType", GetCheckpointType);
		lua_classfunction(L, "getHeight", GetHeight);
		lua_classfunction(L, "getRadius", GetRadius);
		lua_classfunction(L, "getColor", GetColor);

		lua_classvariable(L, "checkpointType", nullptr, "getCheckpointType");
		lua_classvariable(L, "height", nullptr, "getHeight");
		lua_classvariable(L, "radius", nullptr, "getRadius");
		lua_classvariable(L, "color", nullptr, "getColor");
	}
	lua_endclass(L);

	DEBUG_INFO("CLuaCheckpointDefs::Init ...done");
}

int CLuaCheckpointDefs::Create(lua_State* L)
{
	uint8_t type;
	alt::Position position;
	alt::Position nextPosition;
	float radius;
	float height;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadNumber(type);
	argReader.ReadVector(position);
#ifdef ALT_CLIENT_API
	argReader.ReadVector(nextPosition);
#endif
	argReader.ReadNumber(radius);
	argReader.ReadNumber(height);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

#ifdef ALT_SERVER_API
	auto checkpoint = Core->CreateCheckpoint(type, position, radius, height, color);
#else
	auto checkpoint = Core->CreateCheckpoint(type, position, nextPosition, radius, height, color);
#endif
	if (checkpoint)
	{
		lua_pushbaseobject(L, checkpoint.Get());

		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(checkpoint.Get());
	}
	else
		lua_pushnil(L);

	return 1;
}

int CLuaCheckpointDefs::GetCheckpointType(lua_State* L)
{
	alt::ICheckpoint* checkpoint;

	CArgReader argReader(L);
	argReader.ReadBaseObject(checkpoint);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, checkpoint->GetCheckpointType());

	return 1;
}

int CLuaCheckpointDefs::GetHeight(lua_State* L)
{
	alt::ICheckpoint* checkpoint;

	CArgReader argReader(L);
	argReader.ReadBaseObject(checkpoint);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, checkpoint->GetHeight());

	return 1;
}

int CLuaCheckpointDefs::GetRadius(lua_State* L)
{
	alt::ICheckpoint* checkpoint;

	CArgReader argReader(L);
	argReader.ReadBaseObject(checkpoint);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, checkpoint->GetRadius());

	return 1;
}

int CLuaCheckpointDefs::GetColor(lua_State* L)
{
	alt::ICheckpoint* checkpoint;

	CArgReader argReader(L);
	argReader.ReadBaseObject(checkpoint);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushrgba(L, checkpoint->GetColor());

	return 1;
}
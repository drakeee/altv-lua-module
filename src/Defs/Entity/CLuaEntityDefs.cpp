#include <Main.h>

void CLuaEntityDefs::Init(lua_State* L)
{
	lua_beginclass(L, "Entity", "BaseObject");
	{
		lua_classfunction(L, "getId", GetID);
		lua_classfunction(L, "getNetworkOwner", GetNetworkOwner);
		lua_classfunction(L, "getModel", GetModel);
		lua_classfunction(L, "setPosition", SetPosition);
		lua_classfunction(L, "getPosition", GetPosition);
		lua_classfunction(L, "setRotation", SetRotation);
		lua_classfunction(L, "getRotation", GetRotation);
		lua_classfunction(L, "hasSyncedMetaData", HasSyncedMetaData);
		lua_classfunction(L, "getSyncedMetaData", GetSyncedMetaData);
		lua_classfunction(L, "hasStreamSyncedMetaData", HasStreamSyncedMetaData);
		lua_classfunction(L, "getStreamSyncedMetaData", GetStreamSyncedMetaData);
		//lua_classfunction(L, "setSyncedMetaData", SetSyncedMetaData);
		lua_classfunction(L, "deleteSyncedMetaData", DeleteSyncedMetaData);
		//lua_classfunction(L, "setStreamSyncedMetaData", SetStreamSyncedMetaData);
		lua_classfunction(L, "deleteStreamSyncedMetaData", DeleteStreamSyncedMetaData);

		lua_classvariable(L, "id", nullptr, "getId");
		lua_classvariable(L, "networkOwner", nullptr, "getNetworkOwner");
		lua_classvariable(L, "model", nullptr, "getModel");
		lua_classvariable(L, "position", "setPosition", "getPosition");
	}
	lua_endclass(L);

}

int CLuaEntityDefs::ToString(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->GetType();

	return 1;
}

int CLuaEntityDefs::GetID(lua_State* L)
{
	alt::IEntity *entity;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, entity->GetID());

	return 1;
}

int CLuaEntityDefs::GetNetworkOwner(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushuserdata(L, nullptr, entity->GetNetworkOwner().Get());

	return 1;
}

int CLuaEntityDefs::GetModel(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, entity->GetModel());

	return 1;
}

int CLuaEntityDefs::SetPosition(lua_State* L)
{
	alt::IEntity* entity;
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadPosition(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->SetPosition(position);

	return 0;
}

int CLuaEntityDefs::GetPosition(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushuserdata(L, "Vector3", new alt::Position(entity->GetPosition()), false);

	return 1;
}

int CLuaEntityDefs::SetRotation(lua_State* L)
{
	alt::IEntity* entity;
	alt::Rotation rotation;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadRotation(rotation);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->SetRotation(rotation);

	return 0;
}

int CLuaEntityDefs::GetRotation(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushuserdata(L, "Vector3", new alt::Rotation(entity->GetRotation()), false);

	return 1;
}

int CLuaEntityDefs::HasSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, entity->HasSyncedMetaData(key));

	return 1;
}

int CLuaEntityDefs::GetSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushmvalue(L, entity->GetSyncedMetaData(key));

	return 1;
}

int CLuaEntityDefs::HasStreamSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, entity->HasStreamSyncedMetaData(key));

	return 1;
}

int CLuaEntityDefs::GetStreamSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushmvalue(L, entity->GetStreamSyncedMetaData(key));

	return 1;
}

//int CLuaEntityDefs::SetSyncedMetaData(lua_State* L)
//{
//	alt::IEntity* entity;
//	std::string key;
//	alt::MValue value;
//
//	CArgReader argReader(L);
//	argReader.ReadUserData(entity);
//	argReader.ReadString(key);
//	argReader.ReadMValue(value);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	entity->SetSyncedMetaData(key, val);
//
//	return 1;
//}

int CLuaEntityDefs::DeleteSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;
	
	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadString(key);
	
	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->DeleteSyncedMetaData(key);

	return 0;
}

//int CLuaEntityDefs::SetStreamSyncedMetaData(lua_State* L)
//{
//	return 0;
//}

int CLuaEntityDefs::DeleteStreamSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->DeleteStreamSyncedMetaData(key);

	return 0;
}
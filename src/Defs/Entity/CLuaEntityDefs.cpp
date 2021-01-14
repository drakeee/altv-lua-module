#include <Main.h>

const char* CLuaEntityDefs::ClassName = "Entity";
void CLuaEntityDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaEntityDefs::Init");

	lua_globalfunction(L, "getEntityID", GetID);

	lua_globalfunction(L, "getEntityNetworkOwner", GetNetworkOwner);

	lua_globalfunction(L, "getEntityModel", GetModel);

	lua_globalfunction(L, "setEntityRotation", SetRotation);
	lua_globalfunction(L, "getEntityRotation", GetRotation);

	lua_globalfunction(L, "getEntityVisible", GetVisible);
	lua_globalfunction(L, "hasEntitySyncedMetaData", HasSyncedMetaData);
	lua_globalfunction(L, "getEntitySyncedMetaData", GetSyncedMetaData);
	lua_globalfunction(L, "hasEntityStreamSyncedMetaData", HasStreamSyncedMetaData);
	lua_globalfunction(L, "getEntityStreamSyncedMetaData", GetStreamSyncedMetaData);

#ifdef ALT_SERVER_API
	lua_globalfunction(L, "setEntityNetworkOwner", SetNetworkOwner);

	lua_globalfunction(L, "setEntitySyncedMetaData", SetSyncedMetaData);
	lua_globalfunction(L, "deleteEntitySyncedMetaData", DeleteSyncedMetaData);
	lua_globalfunction(L, "setEntityStreamSyncedMetaData", SetStreamSyncedMetaData);
	lua_globalfunction(L, "deleteEntityStreamSyncedMetaData", DeleteStreamSyncedMetaData);
	lua_globalfunction(L, "setEntityVisible", SetVisible);
#else
	lua_globalfunction(L, "getEntityByScriptID", GetEntityByScriptGuid);
	lua_globalfunction(L, "getEntityScriptID", GetScriptGuid);
#endif

	lua_beginclass(L, ClassName, CLuaWorldObjectDefs::ClassName);
	{
		lua_classmeta(L, "__pairs", pairs);
		lua_classmeta(L, "__ipairs", ipairs);

		lua_classfunction(L, "getId", GetID);
		lua_classfunction(L, "getNetworkOwner", GetNetworkOwner);
		lua_classfunction(L, "getModel", GetModel);
		//lua_classfunction(L, "setPosition", SetPosition);
		//lua_classfunction(L, "getPosition", GetPosition);
		lua_classfunction(L, "setRotation", SetRotation);
		lua_classfunction(L, "getRotation", GetRotation);
		lua_classfunction(L, "getVisible", GetVisible);
		lua_classfunction(L, "hasSyncedMetaData", HasSyncedMetaData);
		lua_classfunction(L, "getSyncedMetaData", GetSyncedMetaData);
		lua_classfunction(L, "hasStreamSyncedMetaData", HasStreamSyncedMetaData);
		lua_classfunction(L, "getStreamSyncedMetaData", GetStreamSyncedMetaData);
		lua_classfunction(L, "getAll", ipairs);

#ifdef ALT_SERVER_API
		lua_classfunction(L, "setNetworkOwner", SetNetworkOwner);

		lua_classfunction(L, "setSyncedMetaData", SetSyncedMetaData);
		lua_classfunction(L, "deleteSyncedMetaData", DeleteSyncedMetaData);
		lua_classfunction(L, "setStreamSyncedMetaData", SetStreamSyncedMetaData);
		lua_classfunction(L, "deleteStreamSyncedMetaData", DeleteStreamSyncedMetaData);
		lua_classfunction(L, "setVisible", SetVisible);
#else
		lua_classfunction(L, "getByScriptID", GetEntityByScriptGuid);
		lua_classfunction(L, "getScriptID", GetScriptGuid);
#endif

		lua_classvariable(L, "id", nullptr, "getId");
		lua_classvariable(L, "model", nullptr, "getModel");
		lua_classvariable(L, "rotation", "setRotation", "getRotation");
		lua_classvariable(L, "all", nullptr, "getAll");

#ifdef ALT_SERVER_API
		lua_classvariable(L, "networkOwner", "setNetworkOwner", "getNetworkOwner");
#else
		lua_classvariable(L, "networkOwner", nullptr, "getNetworkOwner");
		lua_classvariable(L, "scriptID", nullptr, "getScriptID");
#endif
	}
	lua_endclass(L);

	DEBUG_INFO("CLuaEntityDefs::Init ...done");
}

int CLuaEntityDefs::tostring(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->GetType();

	return 1;
}

int CLuaEntityDefs::pairs(lua_State* L)
{
	return 0;
}

int CLuaEntityDefs::ipairs(lua_State* L)
{
	lua_newtable(L);
	auto allEntites = alt::ICore::Instance().GetEntities();
	for (size_t i = 0; i < allEntites.GetSize(); i++)
	{
		lua_pushnumber(L, (int)(i + 1));
		lua_pushbaseobject(L, allEntites[i].Get());
		lua_rawset(L, -3);
	}

	return 1;
}

int CLuaEntityDefs::GetID(lua_State* L)
{
	alt::IEntity *entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);

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
	argReader.ReadBaseObject(entity);

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
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, entity->GetModel());

	return 1;
}

//int CLuaEntityDefs::SetPosition(lua_State* L)
//{
//	Core->LogInfo("CLuaEntityDefs::SetPosition1");
//
//	alt::IEntity* entity;
//	alt::Position position;
//
//	Core->LogInfo("CLuaEntityDefs::SetPosition2");
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(entity);
//	argReader.ReadPosition(position);
//
//	Core->LogInfo("CLuaEntityDefs::SetPosition3");
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	Core->LogInfo("CLuaEntityDefs::SetPosition4");
//
//	//alt::IEntity* shit = dynamic_cast<alt::IEntity*>(entity);
//
//	printf("SetPosition: %p\n", entity);
//	printf("SetPosition type: %d\n", entity->GetType());
//	printf("SetPosition: %f, %f, %f\n", position.x, position.y, position.z);
//
//	entity->SetPosition(position);
//
//	Core->LogInfo("CLuaEntityDefs::SetPosition5");
//
//	return 0;
//}

//int CLuaEntityDefs::GetPosition(lua_State* L)
//{
//	alt::IEntity* entity;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(entity);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	lua_pushuserdata(L, "Vector3", new alt::Position(entity->GetPosition()), false);
//
//	return 1;
//}

int CLuaEntityDefs::SetRotation(lua_State* L)
{
	alt::IEntity* entity;
	alt::Rotation rotation;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadVector(rotation);

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
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	//lua_pushuserdata(L, "Vector3", new alt::Rotation(entity->GetRotation()), false);
	lua_pushvector3(L, entity->GetRotation());

	return 1;
}

int CLuaEntityDefs::GetVisible(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, entity->GetVisible());

	return 1;
}

int CLuaEntityDefs::HasSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
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
	argReader.ReadBaseObject(entity);
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
	argReader.ReadBaseObject(entity);
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
	argReader.ReadBaseObject(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushmvalue(L, entity->GetStreamSyncedMetaData(key));

	return 1;
}

#ifdef ALT_SERVER_API
int CLuaEntityDefs::SetNetworkOwner(lua_State* L)
{
	alt::IEntity* entity;
	alt::IPlayer* entityOwner;
	bool disableMigration;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadBaseObject(entityOwner);
	argReader.ReadBool(disableMigration);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->SetNetworkOwner(entityOwner, disableMigration);

	return 0;
}

int CLuaEntityDefs::SetSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;
	alt::MValue value;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadString(key);
	argReader.ReadMValue(value);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->SetSyncedMetaData(key, value);

	return 0;
}

int CLuaEntityDefs::DeleteSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;
	
	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadString(key);
	
	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->DeleteSyncedMetaData(key);

	return 0;
}

int CLuaEntityDefs::SetStreamSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;
	alt::MValue value;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadString(key);
	argReader.ReadMValue(value);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->SetStreamSyncedMetaData(key, value);

	return 0;
}

int CLuaEntityDefs::DeleteStreamSyncedMetaData(lua_State* L)
{
	alt::IEntity* entity;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->DeleteStreamSyncedMetaData(key);

	return 0;
}

int CLuaEntityDefs::SetVisible(lua_State* L)
{
	alt::IEntity* entity;
	bool state;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);
	argReader.ReadBool(state);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	entity->SetVisible(state);

	return 0;
}
#else
int CLuaEntityDefs::GetScriptGuid(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, entity->GetScriptGuid());

	return 1;
}

int CLuaEntityDefs::GetEntityByScriptGuid(lua_State* L)
{
	int32_t scriptID;

	CArgReader argReader(L);
	argReader.ReadNumber(scriptID);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, Core->GetEntityByScriptGuid(scriptID));

	return 1;
}
#endif
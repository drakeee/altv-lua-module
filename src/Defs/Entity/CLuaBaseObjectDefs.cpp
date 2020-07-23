#include <Main.h>

const char* CLuaBaseObjectDefs::ClassName = "BaseObject";
void CLuaBaseObjectDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "getEntityType", GetType);
	lua_globalfunction(L, "hasEntityMetaData", HasMetaData);
	lua_globalfunction(L, "getEntityMetaData", GetMetaData);
	lua_globalfunction(L, "setEntityMetaData", SetMetaData);
	lua_globalfunction(L, "deleteEntityMetaData", DeleteMetaData);
	lua_globalfunction(L, "destroyEntity", Destroy);

	lua_beginclass(L, ClassName);
	{
		lua_classfunction(L, "getType", GetType);
		lua_classfunction(L, "hasMetaData", HasMetaData);
		lua_classfunction(L, "getMetaData", GetMetaData);
		lua_classfunction(L, "setMetaData", SetMetaData);
		lua_classfunction(L, "deleteMetaData", DeleteMetaData);
		lua_classfunction(L, "destroy", Destroy);

		lua_classvariable(L, "type", nullptr, "getType");
	}
	lua_endclass(L);
}

int CLuaBaseObjectDefs::Destroy(lua_State* L)
{
	alt::IBaseObject* baseObject;

	CArgReader argReader(L);
	argReader.ReadBaseObject(baseObject);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->DestroyBaseObject(baseObject);

	lua_pushboolean(L, true);

	return 1;
}

/**
 * @luafunc BaseObject::getType()
 *
 * @brief Gets a BaseObject's type.
 */
int CLuaBaseObjectDefs::GetType(lua_State* L)
{
	alt::IBaseObject *baseObject;

	CArgReader argReader(L);
	argReader.ReadBaseObject(baseObject);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto type = CLuaScriptRuntime::Instance().GetBaseObjectType(baseObject->GetType());
	lua_pushstring(L, type.c_str());

	return 1;
}

int CLuaBaseObjectDefs::HasMetaData(lua_State* L)
{
	alt::IBaseObject* baseObject;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadBaseObject(baseObject);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, baseObject->HasMetaData(key));

	return 1;
}

int CLuaBaseObjectDefs::GetMetaData(lua_State* L)
{
	alt::IBaseObject* baseObject;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadBaseObject(baseObject);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushmvalue(L, baseObject->GetMetaData(alt::String(key)));

	return 1;
}

int CLuaBaseObjectDefs::SetMetaData(lua_State* L)
{
	alt::IBaseObject* baseObject;
	std::string key;
	alt::MValue value;

	CArgReader argReader(L);
	argReader.ReadBaseObject(baseObject);
	argReader.ReadString(key);
	argReader.ReadMValue(value);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	baseObject->SetMetaData(key, value);

	return 0;
}

int CLuaBaseObjectDefs::DeleteMetaData(lua_State* L)
{
	alt::IBaseObject* baseObject;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadBaseObject(baseObject);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	baseObject->DeleteMetaData(key);

	return 0;
}
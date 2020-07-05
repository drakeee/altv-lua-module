#include <Main.h>

const std::list<std::string> CLuaBaseObjectDefs::entityTypes = std::list<std::string>({
		"Player",
		"Vehicle",
		"Blip",
		"WebView",
		"VoiceChannel",
		"ColShape",
		"CheckPoint"
});

void CLuaBaseObjectDefs::Init(lua_State* L)
{
	lua_beginclass(L, "BaseObject");
	{
		lua_classmeta(L, "__tostring", tostring);

		lua_classfunction(L, "getType", GetType);
		lua_classfunction(L, "hasMetaData", HasMetaData);
		lua_classfunction(L, "getMetaData", GetMetaData);
		//lua_classfunction(L, "setMetaData", SetMetaData);
		lua_classfunction(L, "deleteMetaData", DeleteMetaData);
	}
	lua_endclass(L);
}

int CLuaBaseObjectDefs::tostring(lua_State* L)
{
	Core->LogInfo("shit happens i guess");

	alt::IBaseObject* baseObject;

	CArgReader argReader(L);
	argReader.ReadUserData(baseObject);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	std::list<std::string>::const_iterator it = entityTypes.begin();
	std::advance(it, (static_cast<int>(baseObject->GetType()) - 1));

	alt::StringView type("userdata:" + *it);

	lua_pushstring(L, type.CStr());

	return 1;
}

int CLuaBaseObjectDefs::GetType(lua_State* L)
{
	alt::IBaseObject* baseObject;

	CArgReader argReader(L);
	argReader.ReadUserData(baseObject);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, static_cast<int>(baseObject->GetType()));

	return 1;
}

int CLuaBaseObjectDefs::HasMetaData(lua_State* L)
{
	alt::IBaseObject* baseObject;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(baseObject);
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
	argReader.ReadUserData(baseObject);
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
	return 0;
}

int CLuaBaseObjectDefs::DeleteMetaData(lua_State* L)
{
	alt::IBaseObject* baseObject;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(baseObject);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	baseObject->DeleteMetaData(key);

	return 0;
}
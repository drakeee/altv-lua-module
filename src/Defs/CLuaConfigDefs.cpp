#include <Main.h>

const char* CLuaConfigDefs::ClassName = "Config";
void CLuaConfigDefs::Init(lua_State* L)
{
	lua_beginclass(L, CLuaConfigDefs::ClassName);
	{
		lua_classmeta(L, "__tostring", tostring);

		lua_classfunction(L, "getKey", GetKey);
	}
	lua_endclass(L);
}

int CLuaConfigDefs::tostring(lua_State* L)
{
	lua_pushstring(L, "userdata:Config");

	return 1;
}

int CLuaConfigDefs::GetKey(lua_State* L)
{
	alt::config::Node::Dict* nodeDict;
	std::string key;

	CArgReader argReader(L);
	argReader.ReadUserData(nodeDict);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	if (nodeDict->find(key) == nodeDict->end())
	{
		lua_pushnil(L);
	}
	else
	{
		lua_pushnode(L, (*nodeDict)[key]);
	}

	return 1;
}
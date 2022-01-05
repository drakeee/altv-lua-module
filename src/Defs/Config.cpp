#include <Main.h>

namespace lua::Class
{
	const char* Config::ClassName = "Config";
	void Config::Init(lua_State* L)
	{
		DEBUG_INFO("Config::Init");

		lua_beginclass(L, Config::ClassName);
		{
			lua_classmeta(L, "__tostring", tostring);

			lua_classfunction(L, "getKey", GetKey);
		}
		lua_endclass(L);

		DEBUG_INFO("Config::Init ...done");
	}

	int Config::tostring(lua_State* L)
	{
		lua_pushstring(L, "userdata:Config");

		return 1;
	}

	int Config::GetKey(lua_State* L)
	{
		alt::config::Node::Dict* nodeDict;
		std::string key;

		ArgumentReader argReader(L);
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
}
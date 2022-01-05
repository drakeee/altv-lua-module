#pragma once

#include <Main.h>

namespace lua::Class
{
	class Resource
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int tostring(lua_State* L);
		static int pairs(lua_State* L);
		static int ipairs(lua_State* L);

		static int ResourceIndex(lua_State* L);
		static int Call(lua_State* L);

		static int GetResourceByName(lua_State* L);
		static int IsStarted(lua_State* L);

		static int GetConfig(lua_State* L);

		static int GetType(lua_State* L);
		static int GetName(lua_State* L);
		static int GetPath(lua_State* L);
		static int GetMain(lua_State* L);
		static int GetExports(lua_State* L);
		static int GetDependencies(lua_State* L);
		static int GetDependants(lua_State* L);

		static int GetRequiredPermissions(lua_State* L);
		static int GetOptionalPermissions(lua_State* L);
	};
}
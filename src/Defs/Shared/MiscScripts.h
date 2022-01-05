#pragma once

#include <Main.h>

namespace lua::Class
{
	class MiscScripts
	{
	public:
		static void Init(lua_State* L);

	private:
		static void thread(lua_State* L);
		static void inspect(lua_State* L);
	};
}
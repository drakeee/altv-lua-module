#pragma once

#include <Main.h>

namespace lua::Class
{
	class Config
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int tostring(lua_State* L);

		static int GetKey(lua_State* L);
	};
}
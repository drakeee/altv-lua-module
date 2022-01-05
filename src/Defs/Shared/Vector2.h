#pragma once

#include <Main.h>

namespace lua::Class
{
	class Vector2
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int create(lua_State* L);
		static int destroy(lua_State* L);
		static int tostring(lua_State* L);
		static int add(lua_State* L);

		static int SetX(lua_State* L);
		static int SetY(lua_State* L);
		static int GetX(lua_State* L);
		static int GetY(lua_State* L);
	};
}
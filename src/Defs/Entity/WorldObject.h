#pragma once

#include <Main.h>

namespace lua::Class
{
	class WorldObject
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int SetPosition(lua_State* L);
		static int GetPosition(lua_State* L);

		static int SetDimension(lua_State* L);
		static int GetDimension(lua_State* L);
	};
}
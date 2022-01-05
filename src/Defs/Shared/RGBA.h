#pragma once

#include <Main.h>

namespace lua::Class
{
	class RGBA
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int CreateRGBA(lua_State* L);

		static int SetColor(lua_State* L);
		static int GetColor(lua_State* L);
		static int SetR(lua_State* L);
		static int GetR(lua_State* L);
		static int SetG(lua_State* L);
		static int GetG(lua_State* L);
		static int SetB(lua_State* L);
		static int GetB(lua_State* L);
		static int SetA(lua_State* L);
		static int GetA(lua_State* L);
	};
}
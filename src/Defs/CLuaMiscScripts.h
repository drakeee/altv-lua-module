#pragma once

#include <Main.h>

class CLuaMiscScripts
{
public:
	static void Init(lua_State* L);

private:
	static void thread(lua_State* L);
	static void inspect(lua_State* L);
};
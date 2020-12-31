#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API
class CLuaDiscordManagerDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int GetCurrentUser(lua_State* L);
};
#endif
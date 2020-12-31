#include <Main.h>

#ifdef ALT_CLIENT_API
const char* CLuaDiscordManagerDefs::ClassName = "Discord";
void CLuaDiscordManagerDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "getCurrentUser", GetCurrentUser);

	lua_beginclass(L, CLuaDiscordManagerDefs::ClassName);
	{
		lua_classfunction(L, "getCurrentUser", GetCurrentUser);

		lua_classvariable(L, "currentUser", nullptr, "getCurrentUser");
	}
	lua_endclass(L);
}

int CLuaDiscordManagerDefs::GetCurrentUser(lua_State* L)
{
	auto discord = alt::ICore::Instance().GetDiscordManager();
	if (discord->IsUserDataReady())
	{
		lua_newtable(L);

		lua_pushstring(L, discord->GetUserID().CStr());
		lua_setfield(L, -2, "id");

		lua_pushstring(L, discord->GetUsername().CStr());
		lua_setfield(L, -2, "name");

		lua_pushstring(L, discord->GetDiscriminator().CStr());
		lua_setfield(L, -2, "discriminator");

		lua_pushstring(L, discord->GetAvatar().CStr());
		lua_setfield(L, -2, "avatar");
	}
	else
	{
		lua_pushnil(L);
	}

	return 1;
}
#endif
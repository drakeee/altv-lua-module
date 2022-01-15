#include <Main.h>

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CONSOLE_COMMAND_EVENT,
	consoleCommand,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* e) -> int
	{
		auto event = static_cast<const alt::CConsoleCommandEvent*>(e);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushstring(L, event->GetName().c_str());
		lua_newtable(L);

		int index = 1;
		for (auto& arg : event->GetArgs())
		{
			lua_pushnumber(L, index);
			lua_pushstring(L, arg.c_str());
			lua_rawset(L, -3);

			index++;
		}

		return 2;
	}
);
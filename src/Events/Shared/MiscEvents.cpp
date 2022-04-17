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

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::SERVER_SCRIPT_EVENT,
	SERVER_SCRIPT_EVENT,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CServerScriptEvent* event = static_cast<const alt::CServerScriptEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		for (auto arg : event->GetArgs())
		{
			lua_pushmvalue(L, arg);
		}

		return static_cast<int>(event->GetArgs().GetSize());
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CServerScriptEvent* event = static_cast<const alt::CServerScriptEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();


		if(isClient)
			return resourceEventManager->GetRemoteFunctionReferences(const_cast<std::string&>(event->GetName()));
		else
			return resourceEventManager->GetLocalFunctionReferences(const_cast<std::string&>(event->GetName()));
	}
);

#ifdef ALT_SERVER_API
REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CLIENT_SCRIPT_EVENT,
	CLIENT_SCRIPT_EVENT,
	[](LuaResourceImpl* resource, const alt::CEvent* ev) -> int
	{
		const alt::CClientScriptEvent* event = static_cast<const alt::CClientScriptEvent*>(ev);
		lua_State* L = resource->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());

		for (auto arg : event->GetArgs())
		{
			lua_pushmvalue(L, arg);
		}
		return static_cast<int>(event->GetArgs().GetSize()) + 1;
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CClientScriptEvent* event = static_cast<const alt::CClientScriptEvent*>(ev);
		return resourceImpl->GetResourceEventManager()->GetRemoteFunctionReferences(const_cast<std::string&>(event->GetName()));
	}
);
#else
REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CLIENT_SCRIPT_EVENT,
	CLIENT_SCRIPT_EVENT,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CClientScriptEvent* event = static_cast<const alt::CClientScriptEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		for (auto arg : event->GetArgs())
		{
			lua_pushmvalue(L, arg);
		}

		return static_cast<int>(event->GetArgs().GetSize());
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CClientScriptEvent* event = static_cast<const alt::CClientScriptEvent*>(ev);
		return resourceImpl->GetResourceEventManager()->GetLocalFunctionReferences(const_cast<std::string&>(event->GetName()));
	}
);
#endif
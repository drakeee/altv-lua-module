#include <Main.h>

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::SERVER_SCRIPT_EVENT,
	serverScriptEvent,
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
			return resourceEventManager->GetRemoteFunctionReferences(event->GetName().ToString());
		else
			return resourceEventManager->GetLocalFunctionReferences(event->GetName().ToString());
	}
);

#ifdef ALT_SERVER_API
REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CLIENT_SCRIPT_EVENT,
	clientScriptEvent,
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
		return resourceImpl->GetResourceEventManager()->GetRemoteFunctionReferences(event->GetName().ToString());
	}
);
#else
REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CLIENT_SCRIPT_EVENT,
	clientScriptEvent,
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
		return resourceImpl->GetResourceEventManager()->GetLocalFunctionReferences(event->GetName().ToString());
	}
);
#endif
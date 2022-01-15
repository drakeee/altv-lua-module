#include <Main.h>

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::RESOURCE_START,
	anyResourceStart,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CResourceStartEvent* event = static_cast<const alt::CResourceStartEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushresource(L, event->GetResource());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::RESOURCE_STOP,
	anyResourceStop,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CResourceStopEvent* event = static_cast<const alt::CResourceStopEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushresource(L, event->GetResource());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::RESOURCE_ERROR,
	anyResourceError,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CResourceErrorEvent* event = static_cast<const alt::CResourceErrorEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushresource(L, event->GetResource());

		return 1;
	}
);
#include <Main.h>

#ifdef ALT_CLIENT_API
#include <events/CKeyboardEvent.h>
#include <events/CSpawnedEvent.h>
#include <Events/CWindowFocusChangeEvent.h>

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::KEYBOARD_EVENT,
	keyboard,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CKeyboardEvent* event = static_cast<const alt::CKeyboardEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushnumber(L, event->GetKeyCode());

		return 1;
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev)
	{
		const alt::CKeyboardEvent* event = static_cast<const alt::CKeyboardEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		std::string eventName{ "keyup" };
		if (event->GetKeyState() == alt::CKeyboardEvent::KeyState::DOWN)
			eventName.assign("keydown");

		return resourceEventManager->GetLocalFunctionReferences(eventName);
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CONNECTION_COMPLETE,
	connectionComplete,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int { return 0; }
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::DISCONNECT_EVENT,
	disconnect,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int { return 0; }
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::TASK_CHANGE,
	taskChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CTaskChangeEvent* event = static_cast<const alt::CTaskChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushnumber(L, event->GetOldTask());
		lua_pushnumber(L, event->GetNewTask());

		return 2;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::SPAWNED,
	spawned,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int { return 0; }
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::WINDOW_FOCUS_CHANGE,
	windowFocusChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CWindowFocusChangeEvent* event = static_cast<const alt::CWindowFocusChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushboolean(L, event->GetState());

		return 1;
	}
)

#endif
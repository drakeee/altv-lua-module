#include <Main.h>

#ifdef ALT_CLIENT_API

#include <events/CWebSocketClientEvent.h>
#include <events/CRmlEvent.h>

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::GAME_ENTITY_CREATE,
	gameEntityCreate,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CGameEntityCreateEvent* event = static_cast<const alt::CGameEntityCreateEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::GAME_ENTITY_DESTROY,
	gameEntityDestroy,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CGameEntityDestroyEvent* event = static_cast<const alt::CGameEntityDestroyEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::WEB_VIEW_EVENT,
	WEB_VIEW,
	alt::IBaseObject::Type::WEBVIEW,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CWebViewEvent* event = static_cast<const alt::CWebViewEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		for (auto arg : event->GetArgs())
		{
			lua_pushmvalue(L, arg);
		}

		return static_cast<int>(event->GetArgs().GetSize());
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CWebViewEvent* event = static_cast<const alt::CWebViewEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		return resourceEventManager->GetFunctionReferences(event->GetTarget().Get(), event->GetName().ToString());
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::WEB_SOCKET_CLIENT_EVENT,
	WEB_SOCKET_CLIENT,
	alt::IBaseObject::Type::WEBSOCKET_CLIENT,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CWebSocketClientEvent* event = static_cast<const alt::CWebSocketClientEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		for (auto arg : event->GetArgs())
		{
			lua_pushmvalue(L, arg);
		}

		return static_cast<int>(event->GetArgs().GetSize());
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CWebViewEvent* event = static_cast<const alt::CWebViewEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		return resourceEventManager->GetFunctionReferences(event->GetTarget().Get(), event->GetName().ToString());
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::AUDIO_EVENT,
	AUDIO_EVENT,
	alt::IBaseObject::Type::AUDIO,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CWebSocketClientEvent* event = static_cast<const alt::CWebSocketClientEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		for (auto arg : event->GetArgs())
		{
			lua_pushmvalue(L, arg);
		}

		return static_cast<int>(event->GetArgs().GetSize());
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CWebViewEvent* event = static_cast<const alt::CWebViewEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		return resourceEventManager->GetFunctionReferences(event->GetTarget().Get(), event->GetName().ToString());
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::RMLUI_EVENT,
	RMLUI,
	alt::IBaseObject::Type::RML_ELEMENT,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CRmlEvent* event = static_cast<const alt::CRmlEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		//for (auto arg : event->GetArgs())
		//{
		lua_pushmvalue(L, event->GetArgs());
		//}

		//return static_cast<int>(event->GetArgs().GetSize());

		return 1;
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CRmlEvent* event = static_cast<const alt::CRmlEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		return resourceEventManager->GetFunctionReferences(event->GetElement().Get(), event->GetName());
	}
);

#endif
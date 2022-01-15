#include <Main.h>
#include <events/CLocalMetaDataChangeEvent.h>

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::SYNCED_META_CHANGE,
	syncedMetaChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CSyncedMetaDataChangeEvent* event = static_cast<const alt::CSyncedMetaDataChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushstring(L, event->GetKey());
		lua_pushmvalue(L, event->GetVal());
		lua_pushmvalue(L, event->GetOldVal());

		return 4;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::STREAM_SYNCED_META_CHANGE,
	streamSyncedMetaChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CStreamSyncedMetaDataChangeEvent* event = static_cast<const alt::CStreamSyncedMetaDataChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushstring(L, event->GetKey());
		lua_pushmvalue(L, event->GetVal());
		lua_pushmvalue(L, event->GetOldVal());

		return 4;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::GLOBAL_META_CHANGE,
	globalMetaChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CGlobalMetaDataChangeEvent* event = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushstring(L, event->GetKey());
		lua_pushmvalue(L, event->GetVal());
		lua_pushmvalue(L, event->GetOldVal());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::GLOBAL_SYNCED_META_CHANGE,
	globalSyncedMetaChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CGlobalSyncedMetaDataChangeEvent* event = static_cast<const alt::CGlobalSyncedMetaDataChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushstring(L, event->GetKey());
		lua_pushmvalue(L, event->GetVal());
		lua_pushmvalue(L, event->GetOldVal());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::LOCAL_SYNCED_META_CHANGE,
	localMetaChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CLocalMetaDataChangeEvent* event = static_cast<const alt::CLocalMetaDataChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		if(!isClient)
			lua_pushbaseobject(L, event->GetTarget().Get());

		lua_pushstring(L, event->GetKey());
		lua_pushmvalue(L, event->GetVal());
		lua_pushmvalue(L, event->GetOldVal());

		int returnSize = isClient ? 3 : 4;
		return returnSize;
	}
);
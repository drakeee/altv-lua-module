#include "CLuaScriptRuntime.h"

alt::IResource::Impl* CLuaScriptRuntime::CreateImpl(alt::IResource* resource)
{

	CLuaResourceImpl* resourceImpl = new CLuaResourceImpl(this, resource);

	this->resources.insert({resourceImpl->GetLuaState(), resourceImpl});

#ifndef NDEBUG
	Core->LogInfo("CLuaScriptRuntime::CreateImpl: " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));
#endif

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_CONNECT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerConnectEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());

			return 1;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_DISCONNECT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerDisconnectEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushstring(L, event->GetReason().CStr());

			return 2;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::RESOURCE_START,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceStartEvent*>(ev);

			//lua_pushstring(L, event->GetResource()->GetName().CStr());
			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::RESOURCE_STOP,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceStopEvent*>(ev);

			//lua_pushstring(L, event->GetResource()->GetName().CStr());
			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::RESOURCE_ERROR,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceErrorEvent*>(ev);

			//lua_pushstring(L, event->GetResource()->GetName().CStr());
			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	//not used(?)
	/*this->RegisterCallback(
		alt::CEvent::Type::META_CHANGE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			
		}
	)*/

	this->RegisterCallback(
		alt::CEvent::Type::SYNCED_META_CHANGE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CSyncedMetaDataChangeEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 4;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::STREAM_SYNCED_META_CHANGE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CStreamSyncedMetaDataChangeEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 4;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::GLOBAL_META_CHANGE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);

			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 3;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::GLOBAL_SYNCED_META_CHANGE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CGlobalSyncedMetaDataChangeEvent*>(ev);

			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 3;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_DAMAGE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerDamageEvent*>(ev);
			
			lua_pushbaseobject(L, event->GetTarget().Get());

			if (event->GetAttacker())
				lua_pushbaseobject(L, event->GetAttacker().Get());
			else
				lua_pushnil(L);

			lua_pushnumber(L, event->GetDamage());
			lua_pushnumber(L, event->GetWeapon());

			return 4;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_DEATH,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerDeathEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());

			if (event->GetKiller())
				lua_pushbaseobject(L, event->GetKiller().Get());
			else
				lua_pushnil(L);

			lua_pushnumber(L, event->GetWeapon());

			return 3;
		}
	);

	/*this->RegisterCallback(
		alt::CEvent::Type::FIRE_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			
		}
	);*/

	this->RegisterCallback(
		alt::CEvent::Type::EXPLOSION_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CExplosionEvent*>(ev);

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushnumber(L, static_cast<int>(event->GetExplosionType()));
			lua_pushvector(L, event->GetPosition());
			lua_pushnumber(L, event->GetExplosionFX());

			return 4;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::WEAPON_DAMAGE_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CWeaponDamageEvent*>(ev);

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetWeaponHash());
			lua_pushnumber(L, event->GetDamageValue());
			lua_pushvector(L, Vector3fp(event->GetShotOffset()));
			lua_pushnumber(L, static_cast<int>(event->GetBodyPart()));

			return 6;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::VEHICLE_DESTROY,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CVehicleDestroyEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());

			return 1;
		}
	);

	/*this->RegisterCallback(
		alt::CEvent::Type::CHECKPOINT_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			
		}
	);*/

	this->RegisterCallback(
		alt::CEvent::Type::COLSHAPE_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CColShapeEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushbaseobject(L, event->GetEntity().Get());
			lua_pushboolean(L, event->GetState());

			return 3;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_ENTER_VEHICLE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerEnterVehicleEvent*>(ev);

			lua_pushbaseobject(L, event->GetPlayer().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetSeat());

			return 3;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_LEAVE_VEHICLE,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);

			lua_pushbaseobject(L, event->GetPlayer().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetSeat());

			return 3;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::PLAYER_CHANGE_VEHICLE_SEAT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerChangeVehicleSeatEvent*>(ev);

			lua_pushbaseobject(L, event->GetPlayer().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetNewSeat());
			lua_pushnumber(L, event->GetOldSeat());

			return 4;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::REMOVE_ENTITY_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CRemoveEntityEvent*>(ev);

			lua_pushbaseobject(L, event->GetEntity().Get());

			return 1;
		}
	);

	this->RegisterCallback(
		alt::CEvent::Type::CONSOLE_COMMAND_EVENT,
		[](lua_State* L, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CConsoleCommandEvent*>(ev);

			lua_pushstring(L, event->GetName().CStr());
			lua_newtable(L);

			int index = 1;
			for (auto& arg : event->GetArgs())
			{
				lua_pushnumber(L, index);
				lua_pushstring(L, arg.CStr());
				lua_rawset(L, -3);

				index++;
			}

			return 2;
		}
	);

	/*
	enum class Type : uint16_t
		{
			NONE,

			// Shared
			PLAYER_CONNECT,
			PLAYER_DISCONNECT,

			RESOURCE_START,
			RESOURCE_STOP,
			RESOURCE_ERROR,
			
			SERVER_SCRIPT_EVENT,
			CLIENT_SCRIPT_EVENT,

			META_CHANGE,
			SYNCED_META_CHANGE,
			STREAM_SYNCED_META_CHANGE,
			GLOBAL_META_CHANGE,
			GLOBAL_SYNCED_META_CHANGE,

			PLAYER_DAMAGE,
			PLAYER_DEATH,
			FIRE_EVENT,
			EXPLOSION_EVENT,
			WEAPON_DAMAGE_EVENT,
			VEHICLE_DESTROY,

			CHECKPOINT_EVENT,
			COLSHAPE_EVENT,
			PLAYER_ENTER_VEHICLE,
			PLAYER_LEAVE_VEHICLE,
			PLAYER_CHANGE_VEHICLE_SEAT,

			REMOVE_ENTITY_EVENT,

			DATA_NODE_RECEIVED_EVENT,

			CONSOLE_COMMAND_EVENT,

			// Client
			CONNECTION_COMPLETE,
			DISCONNECT_EVENT,
			WEB_VIEW_EVENT,
			KEYBOARD_EVENT,
			GAME_ENTITY_CREATE,
			GAME_ENTITY_DESTROY,

			ALL,
			SIZE
		};
	*/

	return resourceImpl;
}

void CLuaScriptRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
	CLuaResourceImpl* resourceImpl = dynamic_cast<CLuaResourceImpl*>(impl);

	this->resources.erase(resourceImpl->GetLuaState());

#ifndef NDEBUG
	Core->LogInfo("CLuaScriptRuntime::DestroyImpl: " + std::to_string(reinterpret_cast<intptr_t>(impl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));
#endif

	delete impl;

}

CLuaResourceImpl* CLuaScriptRuntime::GetResourceFromState(lua_State* L)
{
	auto it = this->resources.find(L);
	if (it != this->resources.end())
		return it->second;

	return nullptr;
}

const std::string CLuaScriptRuntime::GetBaseObjectType(alt::IBaseObject* baseObject)
{
	return this->entityTypes.at(static_cast<int>(baseObject->GetType()));
}

const std::string CLuaScriptRuntime::GetBaseObjectType(alt::IBaseObject::Type baseType)
{
	return this->entityTypes.at(static_cast<int>(baseType));
}

const std::string CLuaScriptRuntime::GetEventType(const alt::CEvent* ev)
{
	return this->eventTypes.at(static_cast<int>(ev->GetType()));
}
#include "CLuaScriptRuntime.h"

CLuaScriptRuntime::CLuaScriptRuntime()
{
	CVehModels::Instance(); //instance class once for further usage

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_CONNECT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerConnectEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_DISCONNECT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerDisconnectEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushstring(L, event->GetReason().CStr());

			return 2;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::RESOURCE_START,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceStartEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			//lua_pushstring(L, event->GetResource()->GetName().CStr());
			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::RESOURCE_STOP,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceStopEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			//lua_pushstring(L, event->GetResource()->GetName().CStr());
			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::RESOURCE_ERROR,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceErrorEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			//lua_pushstring(L, event->GetResource()->GetName().CStr());
			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::SERVER_SCRIPT_EVENT,
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> const std::vector<int>*
		{
			auto event = static_cast<const alt::CServerScriptEvent*>(ev);
			return &resource->GetEventReferences(event->GetName().CStr());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CServerScriptEvent*>(ev);
			auto runtime = &CLuaScriptRuntime::Instance();
			lua_State* L = resource->GetLuaState();
			
			for (auto arg : event->GetArgs())
			{
				lua_pushmvalue(L, arg);
			}

			return static_cast<int>(event->GetArgs().GetSize());
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::CLIENT_SCRIPT_EVENT,
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> const std::vector<int>*
		{
			auto event = static_cast<const alt::CClientScriptEvent*>(ev);
			return &resource->GetClientEventReferences(event->GetName().CStr());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CClientScriptEvent*>(ev);
			auto runtime = &CLuaScriptRuntime::Instance();
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			for (auto arg : event->GetArgs())
			{
				lua_pushmvalue(L, arg);
			}

			return static_cast<int>(event->GetArgs().GetSize()) + 1;
		}
	);

	//not used(?)
	/*this->RegisterServerCallback(
		alt::CEvent::Type::META_CHANGE,
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> const std::vector<int>*
		{
			auto event = static_cast<const alt::CServerScriptEvent*>(ev);
			return &resource->GetEventReferences(event->GetName().CStr());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			
		}
	)*/

	this->RegisterServerCallback(
		alt::CEvent::Type::SYNCED_META_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CSyncedMetaDataChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 4;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::STREAM_SYNCED_META_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CStreamSyncedMetaDataChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 4;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::GLOBAL_META_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CGlobalMetaDataChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::GLOBAL_SYNCED_META_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CGlobalSyncedMetaDataChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushstring(L, event->GetKey().CStr());
			lua_pushmvalue(L, event->GetVal());
			lua_pushmvalue(L, event->GetOldVal());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_DAMAGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerDamageEvent*>(ev);
			lua_State* L = resource->GetLuaState();

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

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_DEATH,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerDeathEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());

			if (event->GetKiller())
				lua_pushbaseobject(L, event->GetKiller().Get());
			else
				lua_pushnil(L);

			lua_pushnumber(L, event->GetWeapon());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::FIRE_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CFireEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			auto& fires = event->GetFires();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_newtable(L);
			for (int i = 0; i < fires.GetSize(); ++i)
			{
				auto fire = fires[i];

				lua_pushnumber(L, i + 1);
				lua_newtable(L);
				lua_pushstring(L, "position");
				lua_pushvector(L, fire.position);
				lua_rawset(L, -3);

				lua_pushstring(L, "weapon");
				lua_pushnumber(L, fire.weaponHash);
				lua_rawset(L, -3);
				lua_rawset(L, -3);
			}

			return 2;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::EXPLOSION_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CExplosionEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushnumber(L, static_cast<int>(event->GetExplosionType()));
			lua_pushvector(L, event->GetPosition());
			lua_pushnumber(L, event->GetExplosionFX());

			return 4;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::START_PROJECTILE_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CStartProjectileEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushvector(L, event->GetStartPosition());
			lua_pushvector(L, event->GetDirection());
			lua_pushnumber(L, event->GetAmmoHash());
			lua_pushnumber(L, event->GetWeaponHash());

			return 5;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::WEAPON_DAMAGE_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CWeaponDamageEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetWeaponHash());
			lua_pushnumber(L, event->GetDamageValue());
			lua_pushvector(L, event->GetShotOffset());
			lua_pushnumber(L, static_cast<int>(event->GetBodyPart()));

			return 6;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::VEHICLE_DESTROY,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CVehicleDestroyEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());

			return 1;
		}
	);

	/*this->RegisterServerCallback(
		alt::CEvent::Type::CHECKPOINT_EVENT,
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{

		}
	);*/

	this->RegisterServerCallback(
		alt::CEvent::Type::COLSHAPE_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto test = static_cast<const alt::CClientScriptEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			auto event = static_cast<const alt::CColShapeEvent*>(ev);

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushbaseobject(L, event->GetEntity().Get());
			lua_pushboolean(L, event->GetState());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_ENTER_VEHICLE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerEnterVehicleEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetPlayer().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetSeat());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_LEAVE_VEHICLE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetPlayer().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetSeat());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_CHANGE_VEHICLE_SEAT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerChangeVehicleSeatEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetPlayer().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetNewSeat());
			lua_pushnumber(L, event->GetOldSeat());

			return 4;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_WEAPON_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerWeaponChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetOldWeapon());
			lua_pushnumber(L, event->GetNewWeapon());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::REMOVE_ENTITY_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CRemoveEntityEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetEntity().Get());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::CONSOLE_COMMAND_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CConsoleCommandEvent*>(ev);
			lua_State* L = resource->GetLuaState();

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
}

alt::IResource::Impl* CLuaScriptRuntime::CreateImpl(alt::IResource* resource)
{

	CLuaResourceImpl* resourceImpl = new CLuaResourceImpl{ this, resource };

#ifndef NDEBUG
	Core->LogInfo("CLuaScriptRuntime::CreateImpl: " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));
#endif

	return resourceImpl;
}

void CLuaScriptRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
	CLuaResourceImpl* resourceImpl = dynamic_cast<CLuaResourceImpl*>(impl);

	if (resourceImpl != nullptr)
	{
		this->resources.erase(resourceImpl->GetLuaState());
	}

#ifndef NDEBUG
	Core->LogInfo("CLuaScriptRuntime::DestroyImpl: " + std::to_string(reinterpret_cast<intptr_t>(impl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));
#endif

	delete impl;

}

CLuaResourceImpl* CLuaScriptRuntime::GetResourceImplFromState(lua_State* L)
{
	auto it = this->resources.find(L);
	if (it != this->resources.end())
		return it->second;

	return nullptr;
}

void CLuaScriptRuntime::AddResource(lua_State* L, CLuaResourceImpl* resource)
{
	this->resources.insert({ L, resource });
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

const std::string CLuaScriptRuntime::GetEventType(alt::CEvent::Type ev)
{
	return this->eventTypes.at(static_cast<int>(ev));
}
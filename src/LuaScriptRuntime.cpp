#include <Main.h>
#include <fstream>

//#include <events/CRenderEvent.h>
#include <events/CWebSocketClientEvent.h>
#include <events/CAudioEvent.h>

CLuaScriptRuntime::CLuaScriptRuntime()
{

#ifndef NDEBUG
	Core->LogInfo("CLuaScriptRuntime::CLuaScriptRuntime");
#endif

#ifdef ALT_SERVER_API
	VehicleModels::Instance(); //instance class once for further usage
#endif

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_CONNECT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
		alt::CEvent::Type::PLAYER_BEFORE_CONNECT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerBeforeConnectEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			const alt::ConnectionInfo& connectionInfo = event->GetConnectionInfo();
			lua_newtable(L);
			const int t = lua_gettop(L);

			lua_pushstring(L, connectionInfo.name);
			lua_setfield(L, t, "name");
			
			lua_pushstring(L, std::to_string(connectionInfo.socialId));
			lua_setfield(L, t, "socialID");

			lua_pushstring(L, std::to_string(connectionInfo.hwidHash));
			lua_setfield(L, t, "hwidHash");

			lua_pushstring(L, std::to_string(connectionInfo.hwidExHash));
			lua_setfield(L, t, "hwidExHash");

			lua_pushstring(L, connectionInfo.authToken);
			lua_setfield(L, t, "authToken");

			lua_pushboolean(L, connectionInfo.isDebug);
			lua_setfield(L, t, "isDebug");

			lua_pushstring(L, connectionInfo.branch);
			lua_setfield(L, t, "branch");
			
			lua_pushnumber(L, connectionInfo.build);
			lua_setfield(L, t, "build");

			lua_pushstring(L, connectionInfo.cdnUrl);
			lua_setfield(L, t, "cdnUrl");

			lua_pushnumber(L, connectionInfo.passwordHash);
			lua_setfield(L, t, "passwordHash");
			lua_pushstring(L, event->GetReason());

			return 2;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_DISCONNECT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceStartEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::RESOURCE_STOP,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceStopEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::RESOURCE_ERROR,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CResourceErrorEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushresource(L, event->GetResource());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::SERVER_SCRIPT_EVENT,
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> const std::vector<int>*
		{
			auto event = static_cast<const alt::CServerScriptEvent*>(ev);

#ifdef ALT_SERVER_API
			return &resource->GetLocalEventReferences(event->GetName().CStr());
#else
			return &resource->GetRemoteEventReferences(event->GetName().CStr());
#endif
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

#ifdef ALT_SERVER_API
			return &resource->GetRemoteEventReferences(event->GetName().CStr());
#else
			return &resource->GetLocalEventReferences(event->GetName().CStr());
#endif
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CClientScriptEvent*>(ev);
			auto runtime = &CLuaScriptRuntime::Instance();
			lua_State* L = resource->GetLuaState();

#ifdef ALT_SERVER_API
			lua_pushbaseobject(L, event->GetTarget().Get());
#endif
			for (auto arg : event->GetArgs())
			{
				lua_pushmvalue(L, arg);
			}

#ifdef ALT_SERVER_API
			return static_cast<int>(event->GetArgs().GetSize()) + 1;
#else
			return static_cast<int>(event->GetArgs().GetSize());
#endif
		}
	);

	//not used(?)
	/*this->RegisterServerCallback(
		alt::CEvent::Type::META_CHANGE,
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> const std::vector<int>*
		{
			auto event = static_cast<const alt::CServerScriptEvent*>(ev);
			return &resource->GetLocalEventReferences(event->GetName().CStr());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			
		}
	)*/

	this->RegisterServerCallback(
		alt::CEvent::Type::SYNCED_META_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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

			lua_pushnumber(L, event->GetWeapon());
			lua_pushnumber(L, event->GetHealthDamage());
			lua_pushnumber(L, event->GetArmourDamage());

			return 5;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::PLAYER_DEATH,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
				lua_pushvector3(L, fire.position);
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CExplosionEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushnumber(L, static_cast<int>(event->GetExplosionType()));
			lua_pushvector3(L, event->GetPosition());
			lua_pushnumber(L, event->GetExplosionFX());

			return 4;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::START_PROJECTILE_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CStartProjectileEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushvector3(L, event->GetStartPosition());
			lua_pushvector3(L, event->GetDirection());
			lua_pushnumber(L, event->GetAmmoHash());
			lua_pushnumber(L, event->GetWeaponHash());

			return 5;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::WEAPON_DAMAGE_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CWeaponDamageEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetSource().Get());
			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushnumber(L, event->GetWeaponHash());
			lua_pushnumber(L, event->GetDamageValue());
			lua_pushvector3(L, event->GetShotOffset());
			lua_pushnumber(L, static_cast<int>(event->GetBodyPart()));

			return 6;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::VEHICLE_DESTROY,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CVehicleDestroyEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::VEHICLE_DAMAGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CVehicleDamageEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget());
			lua_pushbaseobject(L, event->GetDamager());
			lua_pushnumber(L, event->GetBodyHealthDamage());
			lua_pushnumber(L, event->GetBodyAdditionalHealthDamage());
			lua_pushnumber(L, event->GetEngineHealthDamage());
			lua_pushnumber(L, event->GetPetrolTankHealthDamage());
			lua_pushnumber(L, event->GetDamagedWith());

			return 7;
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
		alt::CEvent::Type::PLAYER_ENTERING_VEHICLE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CPlayerEnteringVehicleEvent*>(ev);
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
		alt::CEvent::Type::VEHICLE_ATTACH,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CVehicleAttachEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushbaseobject(L, event->GetAttached().Get());

			return 2;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::VEHICLE_DETACH,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CVehicleDetachEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushbaseobject(L, event->GetDetached().Get());

			return 2;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::NETOWNER_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CNetOwnerChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget().Get());
			lua_pushbaseobject(L, event->GetNewOwner().Get());
			lua_pushbaseobject(L, event->GetOldOwner().Get());

			return 3;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::REMOVE_ENTITY_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
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
		alt::CEvent::Type::CREATE_BASE_OBJECT_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
			[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CCreateBaseObjectEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetObject().Get());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::REMOVE_BASE_OBJECT_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CRemoveBaseObjectEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetObject().Get());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::CONSOLE_COMMAND_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CConsoleCommandEvent*>(ev);
			lua_State* L = resource->GetLuaState();

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

#ifdef ALT_CLIENT_API
	this->RegisterServerCallback(
		alt::CEvent::Type::CONNECTION_COMPLETE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			return 0;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::DISCONNECT_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			return 0;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::WEB_VIEW_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			auto event = static_cast<const alt::CWebViewEvent*>(ev);
			return &resource->GetWebEventReferences(event->GetTarget().Get(), event->GetName().ToString());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CWebViewEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			for (auto arg : event->GetArgs())
			{
				lua_pushmvalue(L, arg);
			}

			return static_cast<int>(event->GetArgs().GetSize());
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::KEYBOARD_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			auto event = static_cast<const alt::CKeyboardEvent*>(ev);
			if (event->GetKeyState() == alt::CKeyboardEvent::KeyState::UP)
				return &resource->GetLocalEventReferences("keyup");
			else
				return &resource->GetLocalEventReferences("keydown");
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CKeyboardEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushnumber(L, event->GetKeyCode());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::GAME_ENTITY_CREATE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CGameEntityCreateEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::GAME_ENTITY_DESTROY,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CGameEntityDestroyEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushbaseobject(L, event->GetTarget());

			return 1;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::GAME_ENTITY_DESTROY,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			return 0;
		}
	);

	this->RegisterServerCallback(
		alt::CEvent::Type::WEB_SOCKET_CLIENT_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			auto event = static_cast<const alt::CWebSocketClientEvent*>(ev);
			return &resource->GetWebSocketEventReferences(event->GetTarget().Get(), event->GetName().ToString());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CWebSocketClientEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			for (auto arg : event->GetArgs())
			{
				lua_pushmvalue(L, arg);
			}

			return static_cast<int>(event->GetArgs().GetSize());
		}
	);

	/*this->RegisterServerCallback(
		alt::CEvent::Type::AUDIO_EVENT,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			auto event = static_cast<const alt::CAudioEvent*>(ev);
			return &resource->GetWebSocketEventReferences(event->GetTarget().Get(), event->GetName().ToString());
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CWebSocketClientEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			for (auto arg : event->GetArgs())
			{
				lua_pushmvalue(L, arg);
			}

			return static_cast<int>(event->GetArgs().GetSize());
		}
	);*/

	this->RegisterServerCallback(
		alt::CEvent::Type::TASK_CHANGE,
		[this](CLuaResourceImpl* resource, const alt::CEvent* ev)
		{
			return &resource->GetLocalEventReferences(this->GetEventType(ev->GetType()));
		},
		[](CLuaResourceImpl* resource, const alt::CEvent* ev) -> int
		{
			auto event = static_cast<const alt::CTaskChangeEvent*>(ev);
			lua_State* L = resource->GetLuaState();

			lua_pushnumber(L, event->GetOldTask());
			lua_pushnumber(L, event->GetNewTask());

			return 2;
		}
		);
#endif

#ifdef ALT_SERVER_API
	alt::String serverConfigPath = Core->GetRootDirectory() + p_s + "server.cfg";
	this->serverConfigDict = this->ParseConfig(serverConfigPath.CStr());

	//Core->SubscribeEvent(alt::CEvent::Type::RESOURCE_START, CLuaScriptRuntime::OnResourceStart, this);
	//Core->SubscribeEvent(alt::CEvent::Type::RESOURCE_STOP, CLuaScriptRuntime::OnResourceStop, this);
#endif

	this->moduleStartedTime = this->GetTime();
}

#ifdef ALT_SERVER_API
bool CLuaScriptRuntime::OnResourceStart(const alt::CEvent* e, void* userData)
{
	CLuaScriptRuntime *runtime = (CLuaScriptRuntime*)userData;
	auto event = (alt::CResourceStartEvent*)e;

	if (event->GetResource()->GetType() == "lua")
		return true;

	alt::String resourceConfigPath = event->GetResource()->GetPath() + p_s + "resource.cfg";
	auto resourceNode = runtime->ParseConfig(resourceConfigPath.CStr());

	runtime->resourceNodeDictMap[event->GetResource()] = resourceNode;
	return true;
}

bool CLuaScriptRuntime::OnResourceStop(const alt::CEvent* e, void* userData)
{
	CLuaScriptRuntime* runtime = (CLuaScriptRuntime*)userData;
	auto event = (alt::CResourceStartEvent*)e;

	runtime->resourceNodeDictMap.erase(event->GetResource());

	return true;
}
#endif

alt::IResource::Impl* CLuaScriptRuntime::CreateImpl(alt::IResource* resource)
{

	DEBUG_INFO("Before::CLuaScriptRuntime::CreateImpl");

	CLuaResourceImpl* resourceImpl = new CLuaResourceImpl{ this, resource };

	DEBUG_INFO("After::CLuaScriptRuntime::CreateImpl: " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));

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

alt::config::Node::Dict CLuaScriptRuntime::ParseConfig(std::string path)
{
	std::ifstream file(path);
	std::string str;
	std::string file_contents;

	while (std::getline(file, str))
	{
		file_contents += str;
		file_contents.push_back('\n');
	}

	alt::config::Parser parser(file_contents.c_str(), file_contents.size());
	auto node = parser.Parse();

	if (!node.IsDict())
	{
		Core->LogError("Unable to parse config file: " + path);
		return {};
	}

	return node.ToDict();
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
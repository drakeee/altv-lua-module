#include <Main.h>

#ifdef ALT_SERVER_API

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_BEFORE_CONNECT,
	beforePlayerConnect,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerBeforeConnectEvent* event = static_cast<const alt::CPlayerBeforeConnectEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		const alt::Ref<alt::IConnectionInfo> connectionInfo = event->GetConnectionInfo();
		lua_newtable(L);
		{
			lua_setfield(L, -1, "name", connectionInfo->GetName());
			lua_setfield(L, -1, "socialID", std::to_string(connectionInfo->GetSocialId()));
			lua_setfield(L, -1, "hwidHash", std::to_string(connectionInfo->GetHwIdHash()));
			lua_setfield(L, -1, "hwidExHash", std::to_string(connectionInfo->GetHwIdExHash()));
			lua_setfield(L, -1, "authToken", connectionInfo->GetAuthToken());
			lua_setfield(L, -1, "isDebug", connectionInfo->GetIsDebug());
			lua_setfield(L, -1, "branch", connectionInfo->GetBranch());
			lua_setfield(L, -1, "build", connectionInfo->GetBuild());
			lua_setfield(L, -1, "cdnUrl", connectionInfo->GetCdnUrl());
			lua_setfield(L, -1, "passwordHash", connectionInfo->GetPasswordHash());
		}

		lua_pushstring(L, event->GetReason());

		return 2;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_CONNECT,
	playerConnect,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerConnectEvent* event = static_cast<const alt::CPlayerConnectEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_DISCONNECT,
	playerDisconnect,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerDisconnectEvent* event = static_cast<const alt::CPlayerDisconnectEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushstring(L, event->GetReason());

		return 2;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_DAMAGE,
	playerDamage,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerDamageEvent* event = static_cast<const alt::CPlayerDamageEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

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

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_DEATH,
	playerDeath,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerDeathEvent* event = static_cast<const alt::CPlayerDeathEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());

		if (event->GetKiller())
			lua_pushbaseobject(L, event->GetKiller().Get());
		else
			lua_pushnil(L);

		lua_pushnumber(L, event->GetWeapon());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_ENTER_VEHICLE,
	playerEnteredVehicle,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerEnterVehicleEvent* event = static_cast<const alt::CPlayerEnterVehicleEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetPlayer().Get());
		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushnumber(L, event->GetSeat());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_ENTERING_VEHICLE,
	playerEnteringVehicle,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerEnteringVehicleEvent* event = static_cast<const alt::CPlayerEnteringVehicleEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetPlayer().Get());
		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushnumber(L, event->GetSeat());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_LEAVE_VEHICLE,
	playerLeftVehicle,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerLeaveVehicleEvent* event = static_cast<const alt::CPlayerLeaveVehicleEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetPlayer().Get());
		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushnumber(L, event->GetSeat());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_CHANGE_VEHICLE_SEAT,
	playerChangedVehicleSeat,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerChangeVehicleSeatEvent* event = static_cast<const alt::CPlayerChangeVehicleSeatEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetPlayer().Get());
		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushnumber(L, event->GetNewSeat());
		lua_pushnumber(L, event->GetOldSeat());

		return 4;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::PLAYER_WEAPON_CHANGE,
	playerWeaponChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CPlayerWeaponChangeEvent* event = static_cast<const alt::CPlayerWeaponChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushnumber(L, event->GetOldWeapon());
		lua_pushnumber(L, event->GetNewWeapon());

		return 3;
	}
);

#endif
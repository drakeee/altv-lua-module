#include <Main.h>

#ifdef ALT_SERVER_API

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::VEHICLE_DESTROY,
	vehicleDestroy,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CVehicleDestroyEvent* event = static_cast<const alt::CVehicleDestroyEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::VEHICLE_DAMAGE,
	vehicleDamage,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CVehicleDamageEvent* event = static_cast<const alt::CVehicleDamageEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

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

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::VEHICLE_ATTACH,
	vehicleAttach,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CVehicleAttachEvent* event = static_cast<const alt::CVehicleAttachEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushbaseobject(L, event->GetAttached().Get());

		return 2;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::VEHICLE_DETACH,
	vehicleDetach,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CVehicleDetachEvent* event = static_cast<const alt::CVehicleDetachEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushbaseobject(L, event->GetDetached().Get());

		return 2;
	}
);

#endif
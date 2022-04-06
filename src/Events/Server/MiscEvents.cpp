#include <Main.h>

#ifdef ALT_SERVER_API

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::CREATE_BASE_OBJECT_EVENT,
	createBaseObject,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CCreateBaseObjectEvent* event = static_cast<const alt::CCreateBaseObjectEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetObject());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::REMOVE_BASE_OBJECT_EVENT,
	removeBaseObject,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CRemoveBaseObjectEvent* event = static_cast<const alt::CRemoveBaseObjectEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetObject());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::FIRE_EVENT,
	startFire,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CFireEvent* event = static_cast<const alt::CFireEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		const alt::Array<alt::CFireEvent::FireInfo>& fires = event->GetFires();

		lua_pushbaseobject(L, event->GetSource().Get());
		lua_newtable(L);
		for (int i = 0; i < fires.GetSize(); ++i)
		{
			auto fire = fires[i];

			lua_pushnumber(L, i + 1);
			lua_newtable(L);
			
			lua_setfield(L, -1, "position", fire.position);
			lua_setfield(L, -1, "weapon", fire.weaponHash);

			lua_rawset(L, -3);
		}

		return 2;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::EXPLOSION_EVENT,
	explosion,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CExplosionEvent* event = static_cast<const alt::CExplosionEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetSource().Get());
		lua_pushnumber(L, static_cast<int>(event->GetExplosionType()));
		lua_pushvector3(L, event->GetPosition());
		lua_pushnumber(L, event->GetExplosionFX());

		return 4;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::START_PROJECTILE_EVENT,
	startProjectile,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CStartProjectileEvent* event = static_cast<const alt::CStartProjectileEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetSource().Get());
		lua_pushvector3(L, event->GetStartPosition());
		lua_pushvector3(L, event->GetDirection());
		lua_pushnumber(L, event->GetAmmoHash());
		lua_pushnumber(L, event->GetWeaponHash());

		return 5;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::WEAPON_DAMAGE_EVENT,
	weaponDamage,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CWeaponDamageEvent* event = static_cast<const alt::CWeaponDamageEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetSource().Get());
		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushnumber(L, event->GetWeaponHash());
		lua_pushnumber(L, event->GetDamageValue());
		lua_pushvector3(L, event->GetShotOffset());
		lua_pushnumber(L, static_cast<int>(event->GetBodyPart()));

		return 6;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::COLSHAPE_EVENT,
	COLSHAPE_EVENT,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CColShapeEvent* event = static_cast<const alt::CColShapeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushbaseobject(L, event->GetEntity().Get());
		lua_pushboolean(L, event->GetState());

		return 2;
	},
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
	{
		const alt::CColShapeEvent* event = static_cast<const alt::CColShapeEvent*>(ev);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		std::string eventName = event->GetState() ? "entityEnterColshape" : "entityLeaveColshape";
		return resourceEventManager->GetLocalFunctionReferences(eventName);
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::NETOWNER_CHANGE,
	netOwnerChange,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CNetOwnerChangeEvent* event = static_cast<const alt::CNetOwnerChangeEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetTarget().Get());
		lua_pushbaseobject(L, event->GetNewOwner().Get());
		lua_pushbaseobject(L, event->GetOldOwner().Get());

		return 3;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::REMOVE_ENTITY_EVENT,
	removeEntity,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		const alt::CRemoveEntityEvent* event = static_cast<const alt::CRemoveEntityEvent*>(ev);
		lua_State* L = resourceImpl->GetLuaState();

		lua_pushbaseobject(L, event->GetEntity().Get());

		return 1;
	}
);

REGISTER_LOCAL_EVENT(
	alt::CEvent::Type::SERVER_STARTED,
	serverStarted,
	[](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> int
	{
		return 0;
	}
);

#endif
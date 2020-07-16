#include <Main.h>

const char* CLuaPlayerDefs::ClassName = "Entity";
void CLuaPlayerDefs::Init(lua_State* L)
{
	lua_beginclass(L, ClassName, CLuaEntityDefs::ClassName);
	{
		lua_classfunction(L, "isConnected", IsConnected);
		lua_classfunction(L, "getPing", GetPing);
		lua_classfunction(L, "getIP", GetIP);
		lua_classfunction(L, "spawn", Spawn);
		lua_classfunction(L, "despawn", Despawn);
		lua_classfunction(L, "getName", GetName);
		lua_classfunction(L, "getSocialID", GetSocialID);
		lua_classfunction(L, "getHwidHash", GetHwidHash);
		lua_classfunction(L, "getHwidExHash", GetHwidExHash);
		lua_classfunction(L, "getAuthToken", GetAuthToken);
		lua_classfunction(L, "getHealth", GetHealth);
		lua_classfunction(L, "setHealth", SetHealth);
		lua_classfunction(L, "getMaxHealth", GetMaxHealth);
		lua_classfunction(L, "setMaxHealth", SetMaxHealth);
		lua_classfunction(L, "setDateTime", SetDateTime);
		lua_classfunction(L, "setWeather", SetWeather);
		lua_classfunction(L, "giveWeapon", GiveWeapon);
		lua_classfunction(L, "removeWeapon", RemoveWeapon);
		lua_classfunction(L, "removeAllWeapons", RemoveAllWeapons);
		lua_classfunction(L, "addWeaponComponent", AddWeaponComponent);
		lua_classfunction(L, "removeWeaponComponent", RemoveWeaponComponent);
		lua_classfunction(L, "getCurrentWeaponComponents", GetCurrentWeaponComponents);
		lua_classfunction(L, "setWeaponTintIndex", SetWeaponTintIndex);
		lua_classfunction(L, "getCurrentWeaponTintIndex", GetCurrentWeaponTintIndex);
		lua_classfunction(L, "getCurrentWeapon", GetCurrentWeapon);
		lua_classfunction(L, "setCurrentWeapon", SetCurrentWeapon);
		lua_classfunction(L, "isDead", IsDead);
		lua_classfunction(L, "isJumping", IsJumping);
		lua_classfunction(L, "isInRagdoll", IsInRagdoll);
		lua_classfunction(L, "isAiming", IsAiming);
		lua_classfunction(L, "isShooting", IsShooting);
		lua_classfunction(L, "isReloading", IsReloading);
		lua_classfunction(L, "getArmour", GetArmour);
		lua_classfunction(L, "setArmour", SetArmour);
		lua_classfunction(L, "getMaxArmour", GetMaxArmour);
		lua_classfunction(L, "setMaxArmour", SetMaxArmour);
		lua_classfunction(L, "getMoveSpeed", GetMoveSpeed);
		lua_classfunction(L, "getWeapon", GetWeapon);
		lua_classfunction(L, "getAmmo", GetAmmo);
		lua_classfunction(L, "getAimPos", GetAimPos);
		lua_classfunction(L, "getHeadRotation", GetHeadRotation);
		lua_classfunction(L, "isInVehicle", IsInVehicle);
		lua_classfunction(L, "getVehicle", GetVehicle);
		lua_classfunction(L, "getSeat", GetSeat);
		lua_classfunction(L, "getEntityAimingAt", GetEntityAimingAt);
		lua_classfunction(L, "getEntityAimOffset", GetEntityAimOffset);
		lua_classfunction(L, "isFlashlightActive", IsFlashlightActive);
		lua_classfunction(L, "kick", Kick);

#ifdef ALT_SERVER_API
		lua_classfunction(L, "setModel", SetModel);
		lua_classfunction(L, "getModel", GetModel);
#endif

		lua_classvariable(L, "connected", nullptr, "isConnected");
		lua_classvariable(L, "ping", nullptr, "getPing");
		lua_classvariable(L, "ip", nullptr, "getIP");
		lua_classvariable(L, "name", nullptr, "getName");
		lua_classvariable(L, "socialId", nullptr, "getSocialID");
		lua_classvariable(L, "hwidHash", nullptr, "getHwidHash");
		lua_classvariable(L, "hwidExHash", nullptr, "getHwidExHash");
		lua_classvariable(L, "authToken", nullptr, "getAuthToken");
		lua_classvariable(L, "health", "setHealth", "getHealth");
		lua_classvariable(L, "maxHealth", "setMaxHealth", "getMaxHealth");
		lua_classvariable(L, "weather", "setWeather", nullptr);
		lua_classvariable(L, "currentWeaponComponents", nullptr, "getCurrentWeaponComponents");
		lua_classvariable(L, "currentWeaponTintIndex", nullptr, "getCurrentWeaponTintIndex");
		lua_classvariable(L, "currentWeapon", "setCurrentWeapon", "getCurrentWeapon");
		lua_classvariable(L, "dead", nullptr, "isDead");
		lua_classvariable(L, "jumping", nullptr, "isJumping");
		lua_classvariable(L, "ragdoll", nullptr, "isInRagdoll");
		lua_classvariable(L, "aiming", nullptr, "isAiming");
		lua_classvariable(L, "shooting", nullptr, "isShooting");
		lua_classvariable(L, "reloading", nullptr, "isReloading");
		lua_classvariable(L, "armour", "setArmour", "getArmour");
		lua_classvariable(L, "maxArmour", "setMaxArmour", "getMaxArmour");
		lua_classvariable(L, "moveSpeed", nullptr, "getMoveSpeed");
		lua_classvariable(L, "weapon", nullptr, "getWeapon");
		lua_classvariable(L, "ammo", nullptr, "getAmmo");
		lua_classvariable(L, "aimPos", nullptr, "getAimPos");
		lua_classvariable(L, "headRotation", nullptr, "getHeadRotation");
		lua_classvariable(L, "inVehicle", nullptr, "isInVehicle");
		lua_classvariable(L, "vehicle", nullptr, "getVehicle");
		lua_classvariable(L, "seat", nullptr, "getSeat");
		lua_classvariable(L, "aimingAt", nullptr, "getEntityAimingAt");
		lua_classvariable(L, "aimOffset", nullptr, "getEntityAimOffset");
		lua_classvariable(L, "flashlightActive", nullptr, "isFlashlightActive");

#ifdef ALT_SERVER_API
		lua_classvariable(L, "model", "setModel", "getModel");
#endif
	}
	lua_endclass(L);
}

int CLuaPlayerDefs::IsConnected(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsConnected());

	return 1;
}

int CLuaPlayerDefs::GetPing(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetPing());

	return 1;
}

int CLuaPlayerDefs::GetIP(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, player->GetIP().CStr());

	return 1;
}

int CLuaPlayerDefs::Spawn(lua_State* L)
{
	alt::IPlayer* player;
	alt::Position position;
	uint32_t delayMs;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadVector(position);
	argReader.ReadNumber(delayMs);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->Spawn(position, delayMs);

	return 0;
}
int CLuaPlayerDefs::Despawn(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->Despawn();

	return 0;
}

int CLuaPlayerDefs::GetName(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, player->GetName().CStr());

	return 1;
}

int CLuaPlayerDefs::GetSocialID(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetSocialID());

	return 1;
}

int CLuaPlayerDefs::GetHwidHash(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetHwidHash());

	return 1;
}

int CLuaPlayerDefs::GetHwidExHash(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetHwidExHash());

	return 1;
}

int CLuaPlayerDefs::GetAuthToken(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, player->GetAuthToken().CStr());

	return 1;
}

int CLuaPlayerDefs::GetHealth(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetHealth());

	return 1;
}

int CLuaPlayerDefs::SetHealth(lua_State* L)
{
	alt::IPlayer* player;
	uint16_t health;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(health);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetHealth(health);

	return 0;
}

int CLuaPlayerDefs::GetMaxHealth(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetMaxHealth());

	return 1;
}

int CLuaPlayerDefs::SetMaxHealth(lua_State* L)
{
	alt::IPlayer* player;
	uint16_t health;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(health);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetMaxHealth(health);

	return 0;
}

int CLuaPlayerDefs::SetDateTime(lua_State* L)
{
	alt::IPlayer* player;
	int day, month, year, hour, minute, second;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(day);
	argReader.ReadNumber(month);
	argReader.ReadNumber(year);
	argReader.ReadNumber(hour);
	argReader.ReadNumber(minute);
	argReader.ReadNumber(second);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetDateTime(day, month, year, hour, minute, second);

	return 0;
}

int CLuaPlayerDefs::SetWeather(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weather;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weather);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetWeather(weather);

	return 0;
}

int CLuaPlayerDefs::GiveWeapon(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weapon;
	uint32_t ammo;
	bool selectWeapon;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weapon);
	argReader.ReadNumber(ammo);
	argReader.ReadBool(selectWeapon);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->GiveWeapon(weapon, ammo, selectWeapon);

	return 0;
}

int CLuaPlayerDefs::RemoveWeapon(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weapon;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weapon);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->RemoveWeapon(weapon);

	return 0;
}

int CLuaPlayerDefs::RemoveAllWeapons(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->RemoveAllWeapons();

	return 0;
}

int CLuaPlayerDefs::AddWeaponComponent(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weapon;
	uint32_t component;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weapon);
	argReader.ReadNumber(component);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->AddWeaponComponent(weapon, component);

	return 0;
}

int CLuaPlayerDefs::RemoveWeaponComponent(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weapon;
	uint32_t component;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weapon);
	argReader.ReadNumber(component);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->RemoveWeaponComponent(weapon, component);

	return 0;
}

int CLuaPlayerDefs::GetCurrentWeaponComponents(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_newtable(L);
	int index = 1;
	for (auto weapon : player->GetCurrentWeaponComponents())
	{
		lua_pushnumber(L, index);
		lua_pushnumber(L, weapon);
		lua_rawset(L, -3);

		index++;
	}

	return 1;
}

int CLuaPlayerDefs::SetWeaponTintIndex(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weapon;
	uint8_t tintIndex;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weapon);
	argReader.ReadNumber(tintIndex);
	
	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetWeaponTintIndex(weapon, tintIndex);

	return 0;
}

int CLuaPlayerDefs::GetCurrentWeaponTintIndex(lua_State* L)
{
	alt::IPlayer* player;
	
	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	
	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetCurrentWeaponTintIndex());

	return 1;
}

int CLuaPlayerDefs::GetCurrentWeapon(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetCurrentWeapon());

	return 1;
}

int CLuaPlayerDefs::SetCurrentWeapon(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t weapon;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(weapon);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetCurrentWeapon(weapon);

	return 0;
}

int CLuaPlayerDefs::IsDead(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsDead());

	return 1;
}

int CLuaPlayerDefs::IsJumping(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsJumping());

	return 1;
}

int CLuaPlayerDefs::IsInRagdoll(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsInRagdoll());

	return 1;
}
int CLuaPlayerDefs::IsAiming(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsAiming());

	return 1;
}

int CLuaPlayerDefs::IsShooting(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsShooting());

	return 1;
}

int CLuaPlayerDefs::IsReloading(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsReloading());

	return 1;
}

int CLuaPlayerDefs::GetArmour(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetArmour());

	return 1;
}

int CLuaPlayerDefs::SetArmour(lua_State* L)
{
	alt::IPlayer* player;
	uint16_t armor;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(armor);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetArmour(armor);

	return 0;
}

int CLuaPlayerDefs::GetMaxArmour(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetMaxArmour());

	return 1;
}

int CLuaPlayerDefs::SetMaxArmour(lua_State* L)
{
	alt::IPlayer* player;
	uint16_t armor;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(armor);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetMaxArmour(armor);

	return 0;
}

int CLuaPlayerDefs::GetMoveSpeed(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetMoveSpeed());

	return 1;
}

int CLuaPlayerDefs::GetWeapon(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetWeapon());

	return 1;
}

int CLuaPlayerDefs::GetAmmo(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetAmmo());

	return 1;
}

int CLuaPlayerDefs::GetAimPos(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushvector(L, player->GetAimPos());

	return 1;
}

int CLuaPlayerDefs::GetHeadRotation(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushvector(L, player->GetHeadRotation());

	return 1;
}

int CLuaPlayerDefs::IsInVehicle(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsInVehicle());

	return 1;
}

int CLuaPlayerDefs::GetVehicle(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, player->GetVehicle().Get());

	return 1;
}

int CLuaPlayerDefs::GetSeat(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetSeat());

	return 1;
}

int CLuaPlayerDefs::GetEntityAimingAt(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	if (player->GetEntityAimingAt())
	{
		lua_pushbaseobject(L, player->GetEntityAimingAt().Get());
	}
	else
	{
		lua_pushnil(L);
	}

	return 1;
}

int CLuaPlayerDefs::GetEntityAimOffset(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushvector(L, player->GetEntityAimOffset());

	return 1;
}

int CLuaPlayerDefs::IsFlashlightActive(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsFlashlightActive());

	return 1;
}

int CLuaPlayerDefs::Kick(lua_State* L)
{
	alt::IPlayer* player;
	std::string reason;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadString(reason);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->Kick(reason);

	return 0;
}

#ifdef ALT_SERVER_API
int CLuaPlayerDefs::SetModel(lua_State* L)
{
	alt::IPlayer* player;
	uint32_t model;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(model);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetModel(model);

	return 0;
}

int CLuaPlayerDefs::GetModel(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetModel());

	return 0;
}
#endif
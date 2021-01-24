#include <Main.h>

const char* CLuaPlayerDefs::ClassName = "Player";
void CLuaPlayerDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaPlayerDefs::Init");

	lua_globalfunction(L, "getPlayerName", GetName);
	lua_globalfunction(L, "getPlayerHealth", GetHealth);
	lua_globalfunction(L, "getPlayerMaxHealth", GetMaxHealth);
	lua_globalfunction(L, "getPlayerCurrentWeaponComponents", GetCurrentWeaponComponents);
	lua_globalfunction(L, "getPlayerCurrentWeaponTintIndex", GetCurrentWeaponTintIndex);
	lua_globalfunction(L, "getPlayerCurrentWeapon", GetCurrentWeapon);
	lua_globalfunction(L, "isPlayerDead", IsDead);
	lua_globalfunction(L, "isPlayerJumping", IsJumping);
	lua_globalfunction(L, "isPlayerInRagdoll", IsInRagdoll);
	lua_globalfunction(L, "isPlayerAiming", IsAiming);
	lua_globalfunction(L, "isPlayerShooting", IsShooting);
	lua_globalfunction(L, "isPlayerReloading", IsReloading);
	lua_globalfunction(L, "getPlayerArmour", GetArmour);
	lua_globalfunction(L, "getPlayerMaxArmour", GetMaxArmour);
	lua_globalfunction(L, "getPlayerMoveSpeed", GetMoveSpeed);
	//lua_globalfunction(L, "getPlayerWeapon", GetWeapon);
	//lua_globalfunction(L, "getPlayerAmmo", GetAmmo);
	lua_globalfunction(L, "getPlayerAimPos", GetAimPos);
	lua_globalfunction(L, "getPlayerHeadRotation", GetHeadRotation);
	lua_globalfunction(L, "isPlayerInVehicle", IsInVehicle);
	lua_globalfunction(L, "getPlayerVehicle", GetVehicle);
	lua_globalfunction(L, "getPlayerSeat", GetSeat);
	lua_globalfunction(L, "getPlayerEntityAimingAt", GetEntityAimingAt);
	lua_globalfunction(L, "getPlayerEntityAimOffset", GetEntityAimOffset);
	lua_globalfunction(L, "isPlayerFlashlightActive", IsFlashlightActive);

#ifdef ALT_SERVER_API
	lua_globalfunction(L, "isPlayerConnected", IsConnected);
	lua_globalfunction(L, "getPlayerPing", GetPing);
	lua_globalfunction(L, "getPlayerIP", GetIP);
	lua_globalfunction(L, "getPlayerSocialID", GetSocialID);
	lua_globalfunction(L, "getPlayerHwidHash", GetHwidHash);
	lua_globalfunction(L, "getPlayerHwidExHash", GetHwidExHash);
	lua_globalfunction(L, "getPlayerAuthToken", GetAuthToken);
	lua_globalfunction(L, "getPlayerClothes", GetClothes);

	lua_globalfunction(L, "spawnPlayer", Spawn);
	lua_globalfunction(L, "despawnPlayer", Despawn);
	lua_globalfunction(L, "setPlayerModel", SetModel);
	lua_globalfunction(L, "setPlayerArmour", SetArmour);
	lua_globalfunction(L, "setPlayerMaxArmour", SetMaxArmour);
	lua_globalfunction(L, "setPlayerCurrentWeapon", SetCurrentWeapon);
	lua_globalfunction(L, "setPlayerWeaponTintIndex", SetWeaponTintIndex);
	lua_globalfunction(L, "addPlayerWeaponComponent", AddWeaponComponent);
	lua_globalfunction(L, "removePlayerWeaponComponent", RemoveWeaponComponent);
	lua_globalfunction(L, "clearPlayerBloodDamage", ClearBloodDamage);
	lua_globalfunction(L, "setPlayerHealth", SetHealth);
	lua_globalfunction(L, "setPlayerMaxHealth", SetMaxHealth);
	lua_globalfunction(L, "givePlayerWeapon", GiveWeapon);
	lua_globalfunction(L, "removePlayerWeapon", RemoveWeapon);
	lua_globalfunction(L, "removePlayerAllWeapons", RemoveAllWeapons);
	lua_globalfunction(L, "setPlayerDateTime", SetDateTime);
	lua_globalfunction(L, "setPlayerWeather", SetWeather);
	lua_globalfunction(L, "setPlayerClothes", SetClothes);
	lua_globalfunction(L, "kickPlayer", Kick);
	lua_globalfunction(L, "isEntityInStreamRange", IsEntityInStreamingRange);
#else
	lua_globalfunction(L, "isPlayerTalking", IsTalking);
	lua_globalfunction(L, "getPlayerMicLevel", GetMicLevel);
#endif

	lua_beginclass(L, ClassName, CLuaEntityDefs::ClassName);
	{
		lua_classmeta(L, "__tostring", tostring);
		lua_classmeta(L, "__ipairs", ipairs);

		lua_classfunction(L, "getName", GetName);
		lua_classfunction(L, "getHealth", GetHealth);
		lua_classfunction(L, "getMaxHealth", GetMaxHealth);
		lua_classfunction(L, "getCurrentWeaponComponents", GetCurrentWeaponComponents);
		lua_classfunction(L, "getCurrentWeaponTintIndex", GetCurrentWeaponTintIndex);
		lua_classfunction(L, "getCurrentWeapon", GetCurrentWeapon);
		lua_classfunction(L, "isDead", IsDead);
		lua_classfunction(L, "isJumping", IsJumping);
		lua_classfunction(L, "isInRagdoll", IsInRagdoll);
		lua_classfunction(L, "isAiming", IsAiming);
		lua_classfunction(L, "isShooting", IsShooting);
		lua_classfunction(L, "isReloading", IsReloading);
		lua_classfunction(L, "getArmour", GetArmour);
		lua_classfunction(L, "getMaxArmour", GetMaxArmour);
		lua_classfunction(L, "getMoveSpeed", GetMoveSpeed);
		//lua_classfunction(L, "getWeapon", GetWeapon);
		//lua_classfunction(L, "getAmmo", GetAmmo);
		lua_classfunction(L, "getAimPos", GetAimPos);
		lua_classfunction(L, "getHeadRotation", GetHeadRotation);
		lua_classfunction(L, "isInVehicle", IsInVehicle);
		lua_classfunction(L, "getVehicle", GetVehicle);
		lua_classfunction(L, "getSeat", GetSeat);
		lua_classfunction(L, "getEntityAimingAt", GetEntityAimingAt);
		lua_classfunction(L, "getEntityAimOffset", GetEntityAimOffset);
		lua_classfunction(L, "isFlashlightActive", IsFlashlightActive);
		lua_classfunction(L, "getAll", ipairs);

#ifdef ALT_SERVER_API
		lua_classfunction(L, "isConnected", IsConnected);
		lua_classfunction(L, "getPing", GetPing);
		lua_classfunction(L, "getIP", GetIP);
		lua_classfunction(L, "getSocialID", GetSocialID);
		lua_classfunction(L, "getHwidHash", GetHwidHash);
		lua_classfunction(L, "getHwidExHash", GetHwidExHash);
		lua_classfunction(L, "getAuthToken", GetAuthToken);
		lua_classfunction(L, "getClothes", GetClothes);

		lua_classfunction(L, "spawn", Spawn);
		lua_classfunction(L, "despawn", Despawn);
		lua_classfunction(L, "setModel", SetModel);
		lua_classfunction(L, "setArmour", SetArmour);
		lua_classfunction(L, "setMaxArmour", SetMaxArmour);
		lua_classfunction(L, "setCurrentWeapon", SetCurrentWeapon);
		lua_classfunction(L, "setWeaponTintIndex", SetWeaponTintIndex);
		lua_classfunction(L, "addWeaponComponent", AddWeaponComponent);
		lua_classfunction(L, "removeWeaponComponent", RemoveWeaponComponent);
		lua_classfunction(L, "clearBloodDamage", ClearBloodDamage);
		lua_classfunction(L, "setHealth", SetHealth);
		lua_classfunction(L, "setMaxHealth", SetMaxHealth);
		lua_classfunction(L, "giveWeapon", GiveWeapon);
		lua_classfunction(L, "removeWeapon", RemoveWeapon);
		lua_classfunction(L, "removeAllWeapons", RemoveAllWeapons);
		lua_classfunction(L, "setDateTime", SetDateTime);
		lua_classfunction(L, "setWeather", SetWeather);
		lua_classfunction(L, "setClothes", SetClothes);
		lua_classfunction(L, "kick", Kick);
		lua_classfunction(L, "isEntityInStreamingRange", IsEntityInStreamingRange);
#else
		lua_classfunction(L, "getLocalPlayer", GetLocalPlayer);

		lua_classfunction(L, "isTalking", IsTalking);
		lua_classfunction(L, "getMicLevel", GetMicLevel);
#endif

		lua_classvariable(L, "name", nullptr, "getName");
		lua_classvariable(L, "currentWeaponComponents", nullptr, "getCurrentWeaponComponents");
		lua_classvariable(L, "currentWeaponTintIndex", nullptr, "getCurrentWeaponTintIndex");
		lua_classvariable(L, "dead", nullptr, "isDead");
		lua_classvariable(L, "jumping", nullptr, "isJumping");
		lua_classvariable(L, "ragdoll", nullptr, "isInRagdoll");
		lua_classvariable(L, "aiming", nullptr, "isAiming");
		lua_classvariable(L, "shooting", nullptr, "isShooting");
		lua_classvariable(L, "reloading", nullptr, "isReloading");
		lua_classvariable(L, "moveSpeed", nullptr, "getMoveSpeed");
		lua_classvariable(L, "weapon", nullptr, "getCurrentWeapon");
		//lua_classvariable(L, "ammo", nullptr, "getAmmo");
		lua_classvariable(L, "aimPos", nullptr, "getAimPos");
		lua_classvariable(L, "headRotation", nullptr, "getHeadRotation");
		lua_classvariable(L, "inVehicle", nullptr, "isInVehicle");
		lua_classvariable(L, "vehicle", nullptr, "getVehicle");
		lua_classvariable(L, "seat", nullptr, "getSeat");
		lua_classvariable(L, "aimingAt", nullptr, "getEntityAimingAt");
		lua_classvariable(L, "aimOffset", nullptr, "getEntityAimOffset");
		lua_classvariable(L, "flashlightActive", nullptr, "isFlashlightActive");
		lua_classvariable(L, "all", nullptr, "getAll");

#ifdef ALT_SERVER_API
		lua_classvariable(L, "weather", "setWeather", nullptr);
		lua_classvariable(L, "connected", nullptr, "isConnected");
		lua_classvariable(L, "ping", nullptr, "getPing");
		lua_classvariable(L, "ip", nullptr, "getIP");
		lua_classvariable(L, "socialId", nullptr, "getSocialID");
		lua_classvariable(L, "hwidHash", nullptr, "getHwidHash");
		lua_classvariable(L, "hwidExHash", nullptr, "getHwidExHash");
		lua_classvariable(L, "authToken", nullptr, "getAuthToken");

		lua_classvariable(L, "model", "setModel", "getModel");
		lua_classvariable(L, "armour", "setArmour", "getArmour");
		lua_classvariable(L, "maxArmour", "setMaxArmour", "getMaxArmour");
		lua_classvariable(L, "currentWeapon", "setCurrentWeapon", "getCurrentWeapon");
		lua_classvariable(L, "health", "setHealth", "getHealth");
		lua_classvariable(L, "maxHealth", "setMaxHealth", "getMaxHealth");
#else
		lua_classvariable(L, "model", nullptr, "getModel");
		lua_classvariable(L, "armour", nullptr, "getArmour");
		lua_classvariable(L, "maxArmour", nullptr, "getMaxArmour");
		lua_classvariable(L, "currentWeapon", nullptr, "getCurrentWeapon");
		lua_classvariable(L, "health", nullptr, "getHealth");
		lua_classvariable(L, "maxHealth", nullptr, "getMaxHealth");
		lua_classvariable(L, "micLevel", nullptr, "getMicLevel");
		lua_classvariable(L, "local", nullptr, "getLocalPlayer");
#endif
	}
	lua_endclass(L);

#ifdef ALT_CLIENT_API
	lua_pushbaseobject(L, Core->GetLocalPlayer());
	lua_setglobal(L, "localPlayer");
#endif

	DEBUG_INFO("CLuaPlayerDefs::Init ...done");
}

int CLuaPlayerDefs::tostring(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	CLuaScriptRuntime* runtime = &CLuaScriptRuntime::Instance();
	auto vehModels = &VehicleModels::Instance();

	alt::StringView type(alt::String("userdata:") + runtime->GetBaseObjectType(player) + alt::String(":") + player->GetName());

	lua_pushstring(L, type.CStr());

	return 1;
}

int CLuaPlayerDefs::ipairs(lua_State* L)
{
	lua_newtable(L);
	auto allPlayer = alt::ICore::Instance().GetPlayers();
	for (size_t i = 0; i < allPlayer.GetSize(); i++)
	{
		lua_pushnumber(L, (int)(i + 1));
		lua_pushbaseobject(L, allPlayer[i].Get());
		lua_rawset(L, -3);
	}

	return 1;
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

//int CLuaPlayerDefs::GetWeapon(lua_State* L)
//{
//	alt::IPlayer* player;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(player);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	lua_pushnumber(L, player->GetWeapon());
//
//	return 1;
//}

//int CLuaPlayerDefs::GetAmmo(lua_State* L)
//{
//	alt::IPlayer* player;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(player);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	lua_pushnumber(L, player->GetAmmo());
//
//	return 1;
//}

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

	lua_pushvector3(L, player->GetAimPos());

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

	lua_pushvector3(L, player->GetHeadRotation());

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

	lua_pushvector3(L, player->GetEntityAimOffset());

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

#ifdef ALT_SERVER_API
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

	lua_pushstring(L, std::to_string(player->GetSocialID()).c_str());

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

	lua_pushstring(L, std::to_string(player->GetHwidHash()).c_str());

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

	lua_pushstring(L, std::to_string(player->GetHwidExHash()).c_str());

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

int CLuaPlayerDefs::GetClothes(lua_State* L)
{
	alt::IPlayer* player;
	uint8_t component;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(component);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto clothes = player->GetClothes(component);

	lua_newtable(L);
	lua_pushnumber(L, clothes.drawableId);
	lua_setfield(L, -2, "drawable");
	lua_pushnumber(L, clothes.textureId);
	lua_setfield(L, -2, "texture");
	lua_pushnumber(L, clothes.paletteId);
	lua_setfield(L, -2, "palette");

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
	player->SetPosition(position);

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


int CLuaPlayerDefs::SetModel(lua_State* L)
{
	alt::IPlayer* player;
	std::string modelStr;
	uint32_t modelHash = 0;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if(argReader.IsCurrentType(LUA_TNUMBER))
		argReader.ReadNumber(modelHash);
	else if(argReader.IsCurrentType(LUA_TSTRING))
	{
		argReader.ReadString(modelStr);
		modelHash = Core->Hash(modelStr);
	}

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetModel(modelHash);

	return 0;
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

int CLuaPlayerDefs::ClearBloodDamage(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->ClearBloodDamage();

	return 0;
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

int CLuaPlayerDefs::SetClothes(lua_State* L)
{
	alt::IPlayer* player;
	uint8_t component;
	uint16_t drawable;
	uint8_t texture;
	uint8_t palette;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(component);
	argReader.ReadNumber(drawable);
	argReader.ReadNumber(texture);
	argReader.ReadNumber(palette);

	if(argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	player->SetClothes(component, drawable, texture, palette);

	return 0;
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

int CLuaPlayerDefs::IsEntityInStreamingRange(lua_State* L)
{
	alt::IPlayer* player;
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsEntityInStreamingRange(entity));

	return 1;
}

//int CLuaPlayerDefs::GetModel(lua_State* L)
//{
//	alt::IPlayer* player;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(player);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	lua_pushnumber(L, player->GetModel());
//
//	return 0;
//}
#else
int CLuaPlayerDefs::GetLocalPlayer(lua_State* L)
{
	lua_pushbaseobject(L, Core->GetLocalPlayer());
	return 1;
}

int CLuaPlayerDefs::IsTalking(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, player->IsTalking());

	return 1;
}

int CLuaPlayerDefs::GetMicLevel(lua_State* L)
{
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, player->GetMicLevel());

	return 1;
}
#endif
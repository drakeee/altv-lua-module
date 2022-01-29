#include <Main.h>

namespace lua::Class
{
#ifdef ALT_CLIENT_API
	const char* LocalPlayer::ClassName = "LocalPlayer";
	void LocalPlayer::Init(lua_State* L)
	{
		DEBUG_INFO("LocalPlayer::Init");

		lua_globalfunction(L, "getCurrentAmmo", GetCurrentAmmo);

		DEBUG_INFO("LocalPlayer::Init1");

		lua_beginclass(L, LocalPlayer::ClassName, Player::ClassName);
		{
			lua_classfunction(L, "getLocalPlayer", GetLocalPlayer);

			lua_classvariable(L, "currentAmmo", nullptr, GetCurrentAmmo);
		}
		lua_endclass(L);

		DEBUG_INFO("LocalPlayer::Init2");

		lua_openclass(L, Player::ClassName);
		{
			lua_classvariable(L, "local", nullptr, GetLocalPlayer);
		}
		lua_closeclass(L);

		DEBUG_INFO("LocalPlayer::Init3");

		lua_pushbaseobject(L, Core->GetLocalPlayer());
		DEBUG_INFO("LocalPlayer::Init3.1");
		lua_setglobal(L, "localPlayer");

		DEBUG_INFO("LocalPlayer::Init4");
	}

	int LocalPlayer::GetLocalPlayer(lua_State* L)
	{
		lua_pushbaseobject(L, Core->GetLocalPlayer());
		return 1;
	}

	int LocalPlayer::GetCurrentAmmo(lua_State* L)
	{
		alt::ILocalPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetCurrentAmmo());

		return 1;
	}

#endif

	const char* Player::ClassName = "Player";
	void Player::Init(lua_State* L)
	{
		DEBUG_INFO("Player::Init");

		lua_beginclass(L, ClassName, Entity::ClassName);
		{
			lua_classmeta(L, "__tostring", tostring);
			lua_classmeta(L, "__ipairs", ipairs);

			DEBUG_INFO("Player::Init5");

			lua_classfunction(L, "getName", GetName);
			lua_classfunction(L, "getHealth", GetHealth);
			lua_classfunction(L, "getMaxHealth", GetMaxHealth);
			lua_classfunction(L, "getCurrentWeaponComponents", GetCurrentWeaponComponents);
			lua_classfunction(L, "getCurrentWeaponTintIndex", GetCurrentWeaponTintIndex);
			lua_classfunction(L, "getCurrentWeapon", GetCurrentWeapon);

			DEBUG_INFO("Player::Init6");

			lua_classfunction(L, "isDead", IsDead);
			lua_classfunction(L, "isJumping", IsJumping);
			lua_classfunction(L, "isInRagdoll", IsInRagdoll);
			lua_classfunction(L, "isAiming", IsAiming);
			lua_classfunction(L, "isShooting", IsShooting);
			lua_classfunction(L, "isReloading", IsReloading);

			lua_classfunction(L, "getArmour", GetArmour);
			lua_classfunction(L, "getMaxArmour", GetMaxArmour);

			lua_classfunction(L, "getMoveSpeed", GetMoveSpeed);

			DEBUG_INFO("Player::Init7");
			
			lua_classfunction(L, "getAimPos", GetAimPos);
			lua_classfunction(L, "getHeadRotation", GetHeadRotation);
			lua_classfunction(L, "isInVehicle", IsInVehicle);
			lua_classfunction(L, "getVehicle", GetVehicle);
			lua_classfunction(L, "getSeat", GetSeat);
			lua_classfunction(L, "getEntityAimingAt", GetEntityAimingAt);
			lua_classfunction(L, "getEntityAimOffset", GetEntityAimOffset);
			lua_classfunction(L, "isFlashlightActive", IsFlashlightActive);
			lua_classfunction(L, "isSuperJumpEnabled", IsSuperJumpEnabled);
			lua_classfunction(L, "isCrouching", IsCrouching);
			lua_classfunction(L, "isStealthy", IsStealthy);
			lua_classfunction(L, "getAll", ipairs);

			DEBUG_INFO("Player::Init8");

#ifdef ALT_SERVER_API
			lua_classfunction(L, "isConnected", IsConnected);
			lua_classfunction(L, "getPing", GetPing);
			lua_classfunction(L, "getIP", GetIP);
			lua_classfunction(L, "getSocialID", GetSocialID);
			lua_classfunction(L, "getHwidHash", GetHwidHash);
			lua_classfunction(L, "getHwidExHash", GetHwidExHash);
			lua_classfunction(L, "getAuthToken", GetAuthToken);

			lua_classfunction(L, "spawn", Spawn);
			lua_classfunction(L, "despawn", Despawn);
			lua_classfunction(L, "setModel", SetModel);
			lua_classfunction(L, "getModel", GetModel);
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
			lua_classfunction(L, "kick", Kick);
			lua_classfunction(L, "getClothes", GetClothes);
			lua_classfunction(L, "setClothes", SetClothes);
			lua_classfunction(L, "getDlcClothes", GetDlcClothes);
			lua_classfunction(L, "setDlcClothes", SetDlcClothes);
			lua_classfunction(L, "getProp", GetProp);
			lua_classfunction(L, "setProp", SetProp);
			lua_classfunction(L, "getDlcProp", GetDlcProps);
			lua_classfunction(L, "setDlcProp", SetDlcProps);
			lua_classfunction(L, "clearProp", ClearProps);
			lua_classfunction(L, "isEntityInStreamingRange", IsEntityInStreamingRange);
			lua_classfunction(L, "setInvincible", SetInvincible);
			lua_classfunction(L, "getInvincible", GetInvincible);
			lua_classfunction(L, "setIntoVehicle", SetIntoVehicle);
			lua_classfunction(L, "playAmbientSpeech", PlayAmbientSpeech);
			lua_classfunction(L, "setHeadOverlay", SetHeadOverlay);
			lua_classfunction(L, "removeHeadOverlay", RemoveHeadOverlay);
			lua_classfunction(L, "setHeadOverlayColor", SetHeadOverlayColor);
			lua_classfunction(L, "getHeadOverlay", GetHeadOverlay);
			lua_classfunction(L, "setFaceFeature", SetFaceFeature);
			lua_classfunction(L, "getFaceFeatureScale", GetFaceFeatureScale);
			lua_classfunction(L, "removeFaceFeature", RemoveFaceFeature);
			lua_classfunction(L, "setHeadBlendPaletteColor", SetHeadBlendPaletteColor);
			lua_classfunction(L, "getHeadBlendPaletteColor", GetHeadBlendPaletteColor);
			lua_classfunction(L, "setHeadBlendData", SetHeadBlendData);
			lua_classfunction(L, "getHeadBlendData", GetHeadBlendData);
			lua_classfunction(L, "setEyeColor", SetEyeColor);
			lua_classfunction(L, "getEyeColor", GetEyeColor);
			lua_classfunction(L, "setHairColor", SetHairColor);
			lua_classfunction(L, "getHairColor", GetHairColor);
			lua_classfunction(L, "setHairHighlightColor", SetHairHighlightColor);
			lua_classfunction(L, "getHairHighlightColor", GetHairHighlightColor);
			lua_classfunction(L, "getWeapons", GetWeapons);

			lua_classfunction(L, "hasLocalMeta", HasLocalMetaData);
			lua_classfunction(L, "setLocalMeta", SetLocalMetaData);
			lua_classfunction(L, "getLocalMeta", GetLocalMetaData);
			lua_classfunction(L, "deleteLocalMeta", DeleteLocalMetaData);
#else

			lua_classfunction(L, "isTalking", IsTalking);
			lua_classfunction(L, "getMicLevel", GetMicLevel);

			lua_classfunction(L, "setSpatialVolume", SetSpatialVolume);
			lua_classfunction(L, "getSpatialVolume", GetSpatialVolume);
			lua_classfunction(L, "setNonSpatialVolume", SetNonSpatialVolume);
			lua_classfunction(L, "getNonSpatialVolume", GetNonSpatialVolume);

			DEBUG_INFO("Player::Init9");

#endif

			lua_classvariable(L, "name", nullptr, GetName);
			lua_classvariable(L, "currentWeaponComponents", nullptr, GetCurrentWeaponComponents);
			lua_classvariable(L, "currentWeaponTintIndex", nullptr, GetCurrentWeaponTintIndex);
			lua_classvariable(L, "dead", nullptr, IsDead);
			lua_classvariable(L, "jumping", nullptr, IsJumping);
			lua_classvariable(L, "ragdoll", nullptr, IsInRagdoll);
			lua_classvariable(L, "aiming", nullptr, IsAiming);
			lua_classvariable(L, "shooting", nullptr, IsShooting);
			lua_classvariable(L, "reloading", nullptr, IsReloading);
			lua_classvariable(L, "moveSpeed", nullptr, GetMoveSpeed);
			lua_classvariable(L, "weapon", nullptr, GetCurrentWeapon);

			DEBUG_INFO("Player::Init10");

			//lua_classvariable(L, "ammo", nullptr, "getAmmo");
			lua_classvariable(L, "aimPos", nullptr, GetAimPos);
			lua_classvariable(L, "headRotation", nullptr, GetHeadRotation);
			lua_classvariable(L, "inVehicle", nullptr, IsInVehicle);
			lua_classvariable(L, "vehicle", nullptr, GetVehicle);
			lua_classvariable(L, "seat", nullptr, GetSeat);
			lua_classvariable(L, "aimingAt", nullptr, GetEntityAimingAt);
			lua_classvariable(L, "aimOffset", nullptr, GetEntityAimOffset);
			lua_classvariable(L, "flashlightActive", nullptr, IsFlashlightActive);
			lua_classvariable(L, "all", nullptr, ipairs);

			DEBUG_INFO("Player::Init11");

#ifdef ALT_SERVER_API
			lua_classvariable(L, "weather", SetWeather, nullptr);
			lua_classvariable(L, "connected", nullptr, IsConnected);
			lua_classvariable(L, "ping", nullptr, GetPing);
			lua_classvariable(L, "ip", nullptr, GetIP);
			lua_classvariable(L, "socialId", nullptr, GetSocialID);
			lua_classvariable(L, "hwidHash", nullptr, GetHwidHash);
			lua_classvariable(L, "hwidExHash", nullptr, GetHwidExHash);
			lua_classvariable(L, "authToken", nullptr, GetAuthToken);

			lua_classvariable(L, "model", SetModel, GetModel);
			lua_classvariable(L, "armour", SetArmour, GetArmour);
			lua_classvariable(L, "maxArmour", SetMaxArmour, GetMaxArmour);
			lua_classvariable(L, "currentWeapon", SetCurrentWeapon, GetCurrentWeapon);
			lua_classvariable(L, "health", SetHealth, GetHealth);
			lua_classvariable(L, "maxHealth", SetMaxHealth, GetMaxHealth);
#else
			lua_classvariable(L, "model", nullptr, GetModel);
			lua_classvariable(L, "armour", nullptr, GetArmour);
			lua_classvariable(L, "maxArmour", nullptr, GetMaxArmour);
			lua_classvariable(L, "currentWeapon", nullptr, GetCurrentWeapon);
			lua_classvariable(L, "health", nullptr, GetHealth);
			lua_classvariable(L, "maxHealth", nullptr, GetMaxHealth);
			lua_classvariable(L, "micLevel", nullptr, GetMicLevel);
			lua_classvariable(L, "spatialVolume", SetSpatialVolume, GetSpatialVolume);
			lua_classvariable(L, "nonSpatialVolume", SetNonSpatialVolume, GetNonSpatialVolume);
			//lua_classvariable(L, "local", nullptr, "getLocalPlayer");

			DEBUG_INFO("Player::Init12");
#endif
		}
		lua_endclass(L);

		DEBUG_INFO("Player::Init ...done");
	}

	int Player::tostring(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaScriptRuntime* runtime = &LuaScriptRuntime::Instance();
		auto vehModels = &VehicleModels::Instance();

		alt::StringView type(alt::String("userdata:") + runtime->GetBaseObjectType(player) + alt::String(":") + player->GetName());

		lua_pushstring(L, type.CStr());

		return 1;
	}

	int Player::ipairs(lua_State* L)
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

	int Player::GetName(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, player->GetName());

		return 1;
	}

	int Player::GetHealth(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetHealth());

		return 1;
	}

	int Player::GetMaxHealth(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetMaxHealth());

		return 1;
	}

	int Player::GetCurrentWeaponComponents(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
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

	int Player::GetCurrentWeaponTintIndex(lua_State* L)
	{
		alt::IPlayer* player;
	
		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
	
		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetCurrentWeaponTintIndex());

		return 1;
	}

	int Player::GetCurrentWeapon(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetCurrentWeapon());

		return 1;
	}

	int Player::IsDead(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsDead());

		return 1;
	}

	int Player::IsJumping(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsJumping());

		return 1;
	}

	int Player::IsInRagdoll(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsInRagdoll());

		return 1;
	}
	int Player::IsAiming(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsAiming());

		return 1;
	}

	int Player::IsShooting(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsShooting());

		return 1;
	}

	int Player::IsReloading(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsReloading());

		return 1;
	}

	int Player::GetArmour(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetArmour());

		return 1;
	}

	int Player::GetMaxArmour(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetMaxArmour());

		return 1;
	}

	int Player::GetMoveSpeed(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetMoveSpeed());

		return 1;
	}

	//int Player::GetWeapon(lua_State* L)
	//{
	//	alt::IPlayer* player;
	//
	//	ArgumentReader argReader(L);
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

	//int Player::GetAmmo(lua_State* L)
	//{
	//	alt::IPlayer* player;
	//
	//	ArgumentReader argReader(L);
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

	int Player::GetAimPos(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector3(L, player->GetAimPos());

		return 1;
	}

	int Player::GetHeadRotation(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector3(L, player->GetHeadRotation());

		return 1;
	}

	int Player::IsInVehicle(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsInVehicle());

		return 1;
	}

	int Player::GetVehicle(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, player->GetVehicle().Get());

		return 1;
	}

	int Player::GetSeat(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetSeat());

		return 1;
	}

	int Player::GetEntityAimingAt(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
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

	int Player::GetEntityAimOffset(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector3(L, player->GetEntityAimOffset());

		return 1;
	}

	int Player::IsFlashlightActive(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsFlashlightActive());

		return 1;
	}

	int Player::IsSuperJumpEnabled(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsSuperJumpEnabled());

		return 1;
	}

	int Player::IsCrouching(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsCrouching());

		return 1;
	}

	int Player::IsStealthy(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsStealthy());

		return 1;
	}

#ifdef ALT_SERVER_API
	int Player::IsConnected(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsConnected());

		return 1;
	}

	int Player::GetPing(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetPing());

		return 1;
	}

	int Player::GetIP(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, player->GetIP());

		return 1;
	}

	int Player::GetSocialID(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, std::to_string(player->GetSocialID()).c_str());

		return 1;
	}

	int Player::GetHwidHash(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, std::to_string(player->GetHwidHash()).c_str());

		return 1;
	}

	int Player::GetHwidExHash(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, std::to_string(player->GetHwidExHash()).c_str());

		return 1;
	}

	int Player::GetAuthToken(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, player->GetAuthToken());

		return 1;
	}

	int Player::GetClothes(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t component;
		bool dlc = false;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);
		argReader.ReadBoolDefault(dlc, false);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		if(!dlc)
		{
			auto clothes = player->GetClothes(component);

			lua_newtable(L);
			lua_pushnumber(L, clothes.drawableId);
			lua_setfield(L, -2, "drawable");
			lua_pushnumber(L, clothes.textureId);
			lua_setfield(L, -2, "texture");
			lua_pushnumber(L, clothes.paletteId);
			lua_setfield(L, -2, "palette");
		}
		else
		{
			auto clothes = player->GetDlcClothes(component);

			lua_newtable(L);
			lua_pushnumber(L, clothes.drawableId);
			lua_setfield(L, -2, "drawable");
			lua_pushnumber(L, clothes.textureId);
			lua_setfield(L, -2, "texture");
			lua_pushnumber(L, clothes.paletteId);
			lua_setfield(L, -2, "palette");
			lua_pushnumber(L, clothes.dlc);
			lua_setfield(L, -2, "dlc");
		}
	

		return 1;
	}

	int Player::GetProp(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t component;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::Prop prop = player->GetProps(component);

		lua_newtable(L);
		{
			lua_setfield(L, -1, "drawable", prop.drawableId);
			lua_setfield(L, -1, "texture", prop.textureId);
		}

		return 1;
	}

	int Player::Spawn(lua_State* L)
	{
		alt::IPlayer* player;
		alt::Position position;
		uint32_t delayMs;

		ArgumentReader argReader(L);
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

	int Player::Despawn(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->Despawn();

		return 0;
	}


	int Player::SetModel(lua_State* L)
	{
		alt::IPlayer* player;
		std::string modelStr;
		uint32_t modelHash = 0;

		ArgumentReader argReader(L);
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

	int Player::GetModel(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetModel());

		return 1;
	}

	int Player::SetArmour(lua_State* L)
	{
		alt::IPlayer* player;
		uint16_t armor;

		ArgumentReader argReader(L);
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

	int Player::SetMaxArmour(lua_State* L)
	{
		alt::IPlayer* player;
		uint16_t armor;

		ArgumentReader argReader(L);
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

	int Player::SetCurrentWeapon(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weapon;

		ArgumentReader argReader(L);
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

	int Player::SetWeaponTintIndex(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weapon;
		uint8_t tintIndex;

		ArgumentReader argReader(L);
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

	int Player::AddWeaponComponent(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weapon;
		uint32_t component;

		ArgumentReader argReader(L);
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

	int Player::RemoveWeaponComponent(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weapon;
		uint32_t component;

		ArgumentReader argReader(L);
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

	int Player::ClearBloodDamage(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->ClearBloodDamage();

		return 0;
	}

	int Player::SetHealth(lua_State* L)
	{
		alt::IPlayer* player;
		uint16_t health;

		ArgumentReader argReader(L);
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

	int Player::SetMaxHealth(lua_State* L)
	{
		alt::IPlayer* player;
		uint16_t health;

		ArgumentReader argReader(L);
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

	int Player::GiveWeapon(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weapon;
		uint32_t ammo;
		bool selectWeapon;

		ArgumentReader argReader(L);
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

	int Player::RemoveWeapon(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weapon;

		ArgumentReader argReader(L);
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

	int Player::RemoveAllWeapons(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->RemoveAllWeapons();

		return 0;
	}

	int Player::SetDateTime(lua_State* L)
	{
		alt::IPlayer* player;
		int day, month, year, hour, minute, second;

		ArgumentReader argReader(L);
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

	int Player::SetWeather(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t weather;

		ArgumentReader argReader(L);
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

	int Player::SetClothes(lua_State* L)
	{
		// todo: make default values here better
		alt::IPlayer* player;
		uint8_t component;
		uint16_t drawable;
		uint8_t texture;
		uint8_t palette = 2;
		uint32_t dlc = 0;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);
		argReader.ReadNumber(drawable);
		argReader.ReadNumber(texture);
		argReader.ReadNumberDefault(palette, (uint8_t)2);
		argReader.ReadNumberDefault(dlc, (uint32_t)0);

		if(argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		if(dlc == 0)
		{
			player->SetClothes(component, drawable, texture, palette);
		}
		else
		{
			player->SetDlcClothes(component, drawable, texture, palette, dlc);
		}
	
		return 0;
	}

	int Player::SetProp(lua_State* L)
	{
		// todo: make default values here better
		alt::IPlayer* player;
		uint8_t component;
		uint16_t drawable;
		uint8_t texture;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);
		argReader.ReadNumber(drawable);
		argReader.ReadNumber(texture);

		if(argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetProps(component, drawable, texture);

		return 0;
	}

	int Player::Kick(lua_State* L)
	{
		// todo: make default values here better
		alt::IPlayer* player;
		std::string reason;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadStringDefault(reason, "Kicked");

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->Kick(reason);

		return 0;
	}

	int Player::IsEntityInStreamingRange(lua_State* L)
	{
		alt::IPlayer* player;
		alt::IEntity* entity = nullptr;
		uint16_t entityId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.IsNextType(LUA_TUSERDATA))
			argReader.ReadBaseObject(entity);
		else
			argReader.ReadNumber(entityId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		if (entity != nullptr)
			lua_pushboolean(L, player->IsEntityInStreamingRange(entity));
		else
			lua_pushboolean(L, player->IsEntityInStreamingRange(entityId));

		return 1;
	}

	int Player::GetDlcClothes(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t component;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::DlcCloth cloth = player->GetDlcClothes(component);
		
		lua_newtable(L);
		{
			lua_setfield(L, -1, "drawable", cloth.drawableId);
			lua_setfield(L, -1, "texture", cloth.textureId);
			lua_setfield(L, -1, "palette", cloth.paletteId);
			lua_setfield(L, -1, "dlc", cloth.dlc);
		}

		return 1;
	}

	int Player::SetDlcClothes(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t component;
		uint16_t drawable;
		uint8_t texture;
		uint8_t palette;
		uint8_t dlc;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(dlc);
		argReader.ReadNumber(component);
		argReader.ReadNumber(drawable);
		argReader.ReadNumber(texture);
		argReader.ReadNumberDefault(palette, (uint8_t)2);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetDlcClothes(component, drawable, texture, palette, dlc);

		return 0;
	}

	int Player::GetDlcProps(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t component;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::DlcProp prop = player->GetDlcProps(component);

		lua_newtable(L);
		{
			lua_setfield(L, -1, "drawable", prop.drawableId);
			lua_setfield(L, -1, "texture", prop.textureId);
			lua_setfield(L, -1, "dlc", prop.dlc);
		}

		return 1;
	}

	int Player::SetDlcProps(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t dlc;
		uint8_t component;
		uint16_t drawable;
		uint8_t texture;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(dlc);
		argReader.ReadNumber(component);
		argReader.ReadNumber(drawable);
		argReader.ReadNumber(texture);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetDlcProps(component, drawable, texture, dlc);

		return 0;
	}

	int Player::ClearProps(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t component;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(component);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->ClearProps(component);

		return 0;
	}

	int Player::SetInvincible(lua_State* L)
	{
		alt::IPlayer* player;
		bool toggle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadBool(toggle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetInvincible(toggle);

		return 0;
	}

	int Player::GetInvincible(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->GetInvincible());

		return 1;
	}

	int Player::SetIntoVehicle(lua_State* L)
	{
		alt::IPlayer* player;
		alt::IVehicle* vehicle;
		uint8_t seat;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(seat);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetIntoVehicle(vehicle, seat);

		return 0;
	}

	int Player::PlayAmbientSpeech(lua_State* L)
	{
		alt::IPlayer* player;
		std::string speechName;
		std::string speechParam;
		uint32_t speechDictHash;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadString(speechName);
		argReader.ReadString(speechParam);
		argReader.ReadNumber(speechDictHash);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->PlayAmbientSpeech(speechName, speechParam, speechDictHash);

		return 0;
	}

	int Player::SetHeadOverlay(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t overlayID;
		uint8_t index;
		float opacity;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(overlayID);
		argReader.ReadNumber(index);
		argReader.ReadNumber(opacity);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetHeadOverlay(overlayID, index, opacity);

		return 0;
	}

	int Player::RemoveHeadOverlay(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t overlayID;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(overlayID);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->RemoveHeadOverlay(overlayID);

		return 0;
	}

	int Player::SetHeadOverlayColor(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t overlayID;
		uint8_t colorType;
		uint8_t colorIndex;
		uint8_t secondColorIndex;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(overlayID);
		argReader.ReadNumber(colorType);
		argReader.ReadNumber(colorIndex);
		argReader.ReadNumber(secondColorIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetHeadOverlayColor(overlayID, colorType, colorIndex, secondColorIndex);

		return 0;
	}

	int Player::GetHeadOverlay(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t overlayID;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(overlayID);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::HeadOverlay headOverlay = player->GetHeadOverlay(overlayID);
		lua_newtable(L);
		{
			lua_setfield(L, -1, "index", headOverlay.index);
			lua_setfield(L, -1, "opacity", headOverlay.opacity);
			lua_setfield(L, -1, "colorType", headOverlay.colorType);
			lua_setfield(L, -1, "colorIndex", headOverlay.colorIndex);
			lua_setfield(L, -1, "secondColorIndex", headOverlay.secondColorIndex);
		}

		return 1;
	}

	int Player::SetFaceFeature(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t index;
		float scale;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(index);
		argReader.ReadNumber(scale);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->SetFaceFeature(index, scale));

		return 1;
	}

	int Player::GetFaceFeatureScale(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t index;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(index);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetFaceFeatureScale(index));

		return 1;
	}

	int Player::RemoveFaceFeature(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t index;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(index);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->RemoveFaceFeature(index));

		return 1;
	}

	int Player::SetHeadBlendPaletteColor(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t id;
		uint8_t red;
		uint8_t green;
		uint8_t blue;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(id);
		argReader.ReadNumber(red);
		argReader.ReadNumber(green);
		argReader.ReadNumber(blue);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->SetHeadBlendPaletteColor(id, red, green, blue));

		return 1;
	}

	int Player::GetHeadBlendPaletteColor(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t id;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(id);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushrgba(L, player->GetHeadBlendPaletteColor(id));

		return 1;
	}

	int Player::SetHeadBlendData(lua_State* L)
	{
		alt::IPlayer* player;
		uint32_t shapeFirstID, shapeSecondID, shapeThirdID;
		uint32_t skinFirstID, skinSecondID, skinThirdID;
		float shapeMix, skinMix, thirdMix;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(shapeFirstID);
		argReader.ReadNumber(shapeSecondID);
		argReader.ReadNumber(shapeThirdID);
		argReader.ReadNumber(skinFirstID);
		argReader.ReadNumber(skinSecondID);
		argReader.ReadNumber(skinThirdID);
		argReader.ReadNumber(shapeMix);
		argReader.ReadNumber(skinMix);
		argReader.ReadNumber(thirdMix);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetHeadBlendData(shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix);

		return 0;
	}

	int Player::GetHeadBlendData(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::HeadBlendData headBlendData = player->GetHeadBlendData();

		lua_newtable(L);
		{
			lua_setfield(L, -1, "shapeFirstID", headBlendData.shapeFirstID);
			lua_setfield(L, -1, "shapeSecondID", headBlendData.shapeSecondID);
			lua_setfield(L, -1, "shapeThirdID", headBlendData.shapeThirdID);
			lua_setfield(L, -1, "skinFirstID", headBlendData.skinFirstID);
			lua_setfield(L, -1, "skinSecondID", headBlendData.skinSecondID);
			lua_setfield(L, -1, "skinThirdID", headBlendData.skinThirdID);
			lua_setfield(L, -1, "shapeMix", headBlendData.shapeMix);
			lua_setfield(L, -1, "skinMix", headBlendData.skinMix);
			lua_setfield(L, -1, "thirdMix", headBlendData.thirdMix);
		}

		return 1;
	}

	int Player::SetEyeColor(lua_State* L)
	{
		alt::IPlayer* player;
		int16_t eyeColor;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(eyeColor);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->SetEyeColor(eyeColor));

		return 1;
	}

	int Player::GetEyeColor(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetEyeColor());

		return 1;
	}

	int Player::SetHairColor(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t hairColor;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(hairColor);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetHairColor(hairColor);

		return 0;
	}

	int Player::GetHairColor(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetHairColor());

		return 1;
	}

	int Player::SetHairHighlightColor(lua_State* L)
	{
		alt::IPlayer* player;
		uint8_t hairHighlightColor;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(hairHighlightColor);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetHairHighlightColor(hairHighlightColor);

		return 0;
	}

	int Player::GetHairHighlightColor(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetHairHighlightColor());

		return 1;
	}

	int Player::GetWeapons(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::Array<alt::Weapon> weapons = player->GetWeapons();
		uint64_t size = weapons.GetSize();

		lua_newtable(L);
		{
			for (uint64_t i = 0; i < size; i++)
			{
				lua_pushnumber(L, i + 1);
				lua_newtable(L);
				{
					alt::Weapon& weapon = weapons[i];
					lua_setfield(L, -1, "hash", weapon.hash);
					lua_setfield(L, -1, "tintIndex", weapon.tintIndex);

					std::unordered_set<uint32_t>& components = weapon.components;

					size_t idx = 1;
					lua_newtable(L);
					{
						for (uint32_t it : components)
						{
							lua_pushnumber(L, idx);
							lua_pushnumber(L, it);
							lua_rawset(L, -3);
							idx++;
						}
					}
					lua_setfield(L, -2, "components");
				}

				lua_rawset(L, -3);
			}
		}

		return 1;
	}

	int Player::HasLocalMetaData(lua_State* L)
	{
		alt::IPlayer* player;
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->HasLocalMetaData(key));

		return 1;
	}

	int Player::SetLocalMetaData(lua_State* L)
	{
		alt::IPlayer* player;
		std::string key;
		alt::MValue val;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadString(key);
		argReader.ReadMValue(val);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetLocalMetaData(key, val);

		return 0;
	}

	int Player::GetLocalMetaData(lua_State* L)
	{
		alt::IPlayer* player;
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushmvalue(L, player->GetLocalMetaData(key));

		return 1;
	}

	int Player::DeleteLocalMetaData(lua_State* L)
	{
		alt::IPlayer* player;
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->DeleteLocalMetaData(key);

		return 0;
	}

#else

	int Player::IsTalking(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, player->IsTalking());

		return 1;
	}

	int Player::GetMicLevel(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetMicLevel());

		return 1;
	}

	int Player::GetSpatialVolume(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetSpatialVolume());

		return 1;
	}

	int Player::SetSpatialVolume(lua_State* L)
	{
		alt::IPlayer* player;
		float volume;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(volume);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetSpatialVolume(volume);

		return 1;
	}

	int Player::GetNonSpatialVolume(lua_State* L)
	{
		alt::IPlayer* player;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, player->GetNonSpatialVolume());

		return 1;
	}

	int Player::SetNonSpatialVolume(lua_State* L)
	{
		alt::IPlayer* player;
		float volume;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(volume);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		player->SetNonSpatialVolume(volume);

		return 1;
	}

#endif
}
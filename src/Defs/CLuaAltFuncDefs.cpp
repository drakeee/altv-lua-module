#include <Main.h>
#include <sstream>

const char* CLuaAltFuncDefs::ClassName = "alt";
void CLuaAltFuncDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaAltFuncDefs::Init");
	//lua_newtable(L);

	lua_globalfunction(L, "log", LogInfo);
	lua_globalfunction(L, "logInfo", LogInfo);
	lua_globalfunction(L, "logDebug", LogDebug);
	lua_globalfunction(L, "logWarning", LogWarning);
	lua_globalfunction(L, "logError", LogError);
	lua_globalfunction(L, "logColored", LogColored);

	lua_beginclass(L, "Log");
	{
		lua_classfunction(L, "info", "logInfo");
		lua_classfunction(L, "debug", "logDebug");
		lua_classfunction(L, "warning", "logWarning");
		lua_classfunction(L, "error", "logError");
		lua_classfunction(L, "colored", "logColored");
	}
	lua_endclass(L);

#ifdef ALT_SERVER_API
	lua_globalfunction(L, "on", OnServer);
#else
	lua_globalfunction(L, "on", OnClient);
#endif
	lua_globalfunction(L, "onServer", OnServer);
	lua_globalfunction(L, "offServer", OffServer);
	lua_globalfunction(L, "onClient", OnClient);
	lua_globalfunction(L, "offClient", OffClient);

	lua_globalfunction(L, "emit", EmitServer);
	lua_globalfunction(L, "emitServer", EmitServer);

	lua_globalfunction(L, "export", Export);
	lua_globalfunction(L, "hash", Hash);
	lua_globalfunction(L, "isDebug", IsDebug);
	lua_globalfunction(L, "fileExists", FileExists);
	lua_globalfunction(L, "fileRead", FileRead);
	lua_globalfunction(L, "getEntityByID", GetEntityByID);
	lua_globalfunction(L, "getVersion", GetVersion);
	lua_globalfunction(L, "getBranch", GetBranch);

	lua_globalfunction(L, "setMetaData", SetMetaData);
	lua_globalfunction(L, "getMetaData", GetMetaData);
	lua_globalfunction(L, "deleteMetaData", DeleteMetaData);
	lua_globalfunction(L, "hasMetaData", HasMetaData);
	lua_globalfunction(L, "getSyncedMetaData", GetSyncedMetaData);
	lua_globalfunction(L, "hasSyncedMetaData", HasSyncedMetaData);

	lua_globalfunction(L, "getRequiredPermissions", GetRequiredPermissions);
	lua_globalfunction(L, "getOptionalPermissions", GetOptionalPermissions);

#ifdef ALT_SERVER_API
	lua_globalfunction(L, "getRootDirectory", GetRootDirectory);

	lua_globalfunction(L, "startResource", StartResource);
	lua_globalfunction(L, "stopResource", StopResource);
	lua_globalfunction(L, "restartResource", RestartResource);

	lua_globalfunction(L, "emitClient", EmitClient);

	lua_globalfunction(L, "setSyncedMetaData", SetSyncedMetaData);
	lua_globalfunction(L, "deleteSyncedMetaData", DeleteSyncedMetaData);

	lua_globalfunction(L, "getPlayersByName", GetPlayersByName);

	lua_globalfunction(L, "getNetTime", GetNetTime);


	lua_pushnumber(L, alt::DEFAULT_DIMENSION);
	lua_setglobal(L, "defaultDimension");

	lua_pushnumber(L, alt::GLOBAL_DIMENSION);
	lua_setglobal(L, "globalDimension");
#else
	lua_globalfunction(L, "setCharStat", SetCharStat);
	lua_globalfunction(L, "getCharStat", GetCharStat);
	lua_globalfunction(L, "resetCharStat", ResetCharStat);

	lua_globalfunction(L, "isSandbox", IsSandbox);

	lua_globalfunction(L, "isKeyDown", IsKeyDown);
	lua_globalfunction(L, "isKeyToggled", IsKeyToggled);
	
	lua_globalfunction(L, "gameControlsEnabled", AreControlsEnabled);
	lua_globalfunction(L, "setCursorPos", SetCursorPosition);
	lua_globalfunction(L, "getCursorPos", GetCursorPosition);

	lua_globalfunction(L, "setConfigFlag", SetConfigFlag);
	lua_globalfunction(L, "getConfigFlag", GetConfigFlag);
	lua_globalfunction(L, "doesConfigFlagExist", DoesConfigFlagExist);

	lua_globalfunction(L, "getLicenseHash", GetLicenseHash);
	lua_globalfunction(L, "getLocale", GetLocale);
	lua_globalfunction(L, "isInStreamerMode", IsInStreamerMode);
	lua_globalfunction(L, "isMenuOpen", IsMenuOpen);
	lua_globalfunction(L, "isConsoleOpen", IsConsoleOpen);
	lua_globalfunction(L, "isTextureExistInArchetype", GetTextureFromDrawable);

	lua_globalfunction(L, "requestIpl", RequestIPL);
	lua_globalfunction(L, "removeIpl", RemoveIPL);

	lua_globalfunction(L, "beginScaleformMovieMethodMinimap", BeginScaleformMovieMethodMinimap);

	lua_globalfunction(L, "getMsPerGameMinute", GetMsPerGameMinute);
	lua_globalfunction(L, "setMsPerGameMinute", SetMsPerGameMinute);
	lua_globalfunction(L, "setWeatherCycle", SetWeatherCycle);
	lua_globalfunction(L, "setWeatherSyncActive", SetWeatherSyncActive);

	lua_globalfunction(L, "setCamFrozen", SetCamFrozen);

	lua_globalfunction(L, "getPermissionState", GetPermissionState);

	lua_globalfunction(L, "takeScreenshot", TakeScreenshot);
	lua_globalfunction(L, "takeScreenshotGameOnly", TakeScreenshotGameOnly);

	lua_globalfunction(L, "setAngularVelocity", SetAngularVelocity);

	lua_globalfunction(L, "isGameFocused", IsGameFocused);
#endif

	lua_beginclass(L, ClassName);
	{
		lua_classmeta(L, "__index", AltIndex, true);
	}
	lua_endclass(L);

	//Override default print function to behave as LogInfo
	lua_getglobal(L, "_G");
	lua_pushstring(L, "_print");
	lua_getglobal(L, "print");
	lua_rawset(L, -3);

	lua_pushstring(L, "print");
	lua_pushcfunction(L, CLuaAltFuncDefs::LogInfo);
	lua_rawset(L, -3);


	//Hacky way to implement custom __pairs and __ipairs meta events
	//Note: both __pairs and __ipairs metaevents should return only a table
	//For example:
	/*
	int CLuaVehicleDefs::ipairs(lua_State* L)
	{
		lua_newtable(L);
		for (size_t i = 0; i < 3; i++)
		{
			//Keep in mind that ipairs only accept tables with index values
			//and need to keep the sequence i.e: (1, 2, 3, 5) will loop through only the first 3 index, because index 4 is missing

			lua_pushnumber(L, i + 1);
			lua_pushstring(L, "somevalue");
			lua_rawset(L, -3);
		}

		return 1;
	}
	*/

	lua_pushstring(L, "ipairsaux");
	lua_pushcfunction(L, CLuaAltFuncDefs::ipairsaux);
	lua_rawset(L, -3);

	lua_pushstring(L, "inext");
	lua_pushcfunction(L, CLuaAltFuncDefs::inext);
	lua_rawset(L, -3);

	lua_pushstring(L, "_pairs");
	lua_getglobal(L, "pairs");
	lua_rawset(L, -3);

	lua_pushstring(L, "_ipairs");
	lua_getglobal(L, "ipairs");
	lua_rawset(L, -3);

	lua_pushstring(L, "pairs");
	lua_getglobal(L, "inext");
	lua_pushcclosure(L, CLuaAltFuncDefs::pairs, 1);
	lua_rawset(L, -3);

	lua_pushstring(L, "ipairs");
	lua_getglobal(L, "ipairsaux");
	lua_pushcclosure(L, CLuaAltFuncDefs::ipairs, 1);
	lua_rawset(L, -3);

#ifdef ALT_SERVER_API
	auto runtime = &CLuaScriptRuntime::Instance();
	lua_pushconfig(L, &runtime->GetServerConfig());
	lua_setglobal(L, "serverConfig");
#endif

	/*lua_pushstring(L, "dofile");
	lua_pushcfunction(L, dofile);
	lua_rawset(L, -3);*/

	lua_pop(L, 1);

	DEBUG_INFO("CLuaAltFuncDefs::Init ...done");
}

int CLuaAltFuncDefs::SetMetaData(lua_State* L)
{
	std::string key;
	alt::MValue value;

	CArgReader argReader(L);
	argReader.ReadString(key);
	argReader.ReadMValue(value);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetMetaData(key, value);

	return 0;
}

int CLuaAltFuncDefs::GetMetaData(lua_State* L)
{
	std::string key;

	CArgReader argReader(L);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushmvalue(L, Core->GetMetaData(key));

	return 1;
}

int CLuaAltFuncDefs::DeleteMetaData(lua_State* L)
{
	std::string key;

	CArgReader argReader(L);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->DeleteMetaData(key);

	return 0;
}

int CLuaAltFuncDefs::HasMetaData(lua_State* L)
{
	std::string key;

	CArgReader argReader(L);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->HasMetaData(key));

	return 1;
}

#ifdef ALT_SERVER_API
int CLuaAltFuncDefs::GetRootDirectory(lua_State* L)
{
	lua_pushstring(L, Core->GetRootDirectory().CStr());
	return 1;
}

int CLuaAltFuncDefs::StartResource(lua_State* L)
{
	std::string resourceName;

	CArgReader argReader(L);
	argReader.ReadString(resourceName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushresource(L, Core->StartResource(resourceName));

	return 1;
}

int CLuaAltFuncDefs::StopResource(lua_State* L)
{
	std::string resourceName;

	CArgReader argReader(L);
	argReader.ReadString(resourceName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->StopResource(resourceName);

	return 0;
}

int CLuaAltFuncDefs::RestartResource(lua_State* L)
{
	std::string resourceName;

	CArgReader argReader(L);
	argReader.ReadString(resourceName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushresource(L, Core->RestartResource(resourceName));

	return 1;
}

int CLuaAltFuncDefs::EmitClient(lua_State* L)
{
	alt::IPlayer* player;
	std::string eventName;
	alt::MValueArgs args;

	CArgReader argReader(L);
	if (argReader.IsCurrentType(LUA_TNIL))
	{
		player = nullptr;
		argReader.SkipValue();
	}
	else
		argReader.ReadBaseObject(player);

	argReader.ReadString(eventName);
	argReader.ReadArguments(args);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->TriggerClientEvent(player, eventName, args);

	return 0;
}

int CLuaAltFuncDefs::SetSyncedMetaData(lua_State* L)
{
	std::string key;
	alt::MValue value;

	CArgReader argReader(L);
	argReader.ReadString(key);
	argReader.ReadMValue(value);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetSyncedMetaData(key, value);

	return 0;
}

int CLuaAltFuncDefs::DeleteSyncedMetaData(lua_State* L)
{
	std::string key;

	CArgReader argReader(L);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->DeleteSyncedMetaData(key);

	return 0;
}

int CLuaAltFuncDefs::GetPlayersByName(lua_State* L)
{
	std::string playersName;

	CArgReader argReader(L);
	argReader.ReadString(playersName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_newtable(L);
	auto playersFound = Core->GetPlayersByName(playersName);
	for (size_t i = 0; i < playersFound.GetSize(); i++)
	{
		lua_pushnumber(L, (int)(i + 1));
		lua_pushbaseobject(L, playersFound[i].Get());
		lua_rawset(L, -3);
	}

	return 1;
}

int CLuaAltFuncDefs::GetNetTime(lua_State* L)
{
	lua_pushnumber(L, Core->GetNetTime());
	return 1;
}
#else
int CLuaAltFuncDefs::SetCharStat(lua_State* L)
{
	std::string statName;

	CArgReader argReader(L);
	argReader.ReadString(statName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto targetStat = Core->GetStatData(statName);
	L_ASSERT(targetStat != nullptr, "stat with this name not found");

	L_ASSERT(strcmp(targetStat->GetStatType(), "NONE") != 0 && strcmp(targetStat->GetStatType(), "PROFILE_SETTING") != 0, "target stat can't be edited");

	if (!strcmp(targetStat->GetStatType(), "INT") || !strcmp(targetStat->GetStatType(), "TEXTLABEL"))
	{
		int32_t value;
		argReader.ReadNumber(value);
		targetStat->SetInt32Value(value);
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "INT64"))
	{
		int32_t value;
		argReader.ReadNumber(value);
		targetStat->SetInt64Value(value);
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "FLOAT"))
	{
		float value;
		argReader.ReadNumber(value);
		targetStat->SetFloatValue(value);
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "BOOL"))
	{
		bool value;
		argReader.ReadBool(value);
		targetStat->SetBoolValue(value);
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "STRING"))
	{
		std::string value;
		argReader.ReadString(value);
		targetStat->SetStringValue(value.c_str());
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "UINT8"))
	{
		uint8_t value;
		argReader.ReadNumber(value);
		targetStat->SetUInt8Value(value);
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "UINT16"))
	{
		uint16_t value;
		argReader.ReadNumber(value);
		targetStat->SetUInt16Value(value);
		lua_pushboolean(L, true);
	}
	else if (!strcmp(targetStat->GetStatType(), "UINT32"))
	{
		uint32_t value;
		argReader.ReadNumber(value);
		targetStat->SetUInt32Value(value);
		lua_pushboolean(L, true);
	}
	else if (
		!strcmp(targetStat->GetStatType(), "UINT64") ||
		!strcmp(targetStat->GetStatType(), "POS") ||
		!strcmp(targetStat->GetStatType(), "DATE") ||
		!strcmp(targetStat->GetStatType(), "PACKED") ||
		!strcmp(targetStat->GetStatType(), "USERID"))
	{
		uint32_t value;
		argReader.ReadNumber(value);
		targetStat->SetUInt64Value(value);
		lua_pushboolean(L, true);
	}
	else {
		lua_pushboolean(L, false);
	}

	return 1;
}

int CLuaAltFuncDefs::GetCharStat(lua_State* L)
{
	std::string statName;

	CArgReader argReader(L);
	argReader.ReadString(statName);

	auto targetStat = Core->GetStatData(statName);
	L_ASSERT(targetStat != nullptr, "stat with this name not found");

	L_ASSERT(strcmp(targetStat->GetStatType(), "NONE") != 0 && strcmp(targetStat->GetStatType(), "PROFILE_SETTING") != 0, "target stat can't be readed");

	if (!strcmp(targetStat->GetStatType(), "INT"))
	{
		lua_pushnumber(L, targetStat->GetInt32Value());
	}
	else if (!strcmp(targetStat->GetStatType(), "INT64"))
	{
		lua_pushnumber(L, targetStat->GetInt64Value());
	}
	else if (!strcmp(targetStat->GetStatType(), "TEXTLABEL"))
	{
		lua_pushnumber(L, targetStat->GetInt32Value());
	}
	else if (!strcmp(targetStat->GetStatType(), "FLOAT"))
	{
		lua_pushnumber(L, targetStat->GetFloatValue());
	}
	else if (!strcmp(targetStat->GetStatType(), "BOOL"))
	{
		lua_pushboolean(L, targetStat->GetBoolValue());
	}
	else if (!strcmp(targetStat->GetStatType(), "STRING"))
	{
		lua_pushstring(L, targetStat->GetStringValue());
	}
	else if (!strcmp(targetStat->GetStatType(), "UINT8"))
	{
		lua_pushnumber(L, targetStat->GetUInt8Value());
	}
	else if (!strcmp(targetStat->GetStatType(), "UINT16"))
	{
		lua_pushnumber(L, targetStat->GetUInt16Value());
	}
	else if (!strcmp(targetStat->GetStatType(), "UINT32"))
	{
		lua_pushnumber(L, targetStat->GetUInt32Value());
	}
	else if (
		!strcmp(targetStat->GetStatType(), "UINT64") ||
		!strcmp(targetStat->GetStatType(), "POS") ||
		!strcmp(targetStat->GetStatType(), "DATE") ||
		!strcmp(targetStat->GetStatType(), "PACKED") ||
		!strcmp(targetStat->GetStatType(), "USERID"))
	{
		lua_pushnumber(L, targetStat->GetUInt64Value());
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int CLuaAltFuncDefs::ResetCharStat(lua_State* L)
{
	std::string statName;

	CArgReader argReader(L);
	argReader.ReadString(statName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto targetStat = Core->GetStatData(statName);
	L_ASSERT(targetStat != nullptr, "stat with this name not found");

	L_ASSERT(strcmp(targetStat->GetStatType(), "NONE") != 0 && strcmp(targetStat->GetStatType(), "PROFILE_SETTING") != 0, "target stat can't be reseted");
	targetStat->Reset();

	lua_pushboolean(L, true);

	return 1;
}

int CLuaAltFuncDefs::IsSandbox(lua_State* L)
{
	lua_pushboolean(L, Core->IsSandbox());
	return 1;
}

int CLuaAltFuncDefs::IsKeyDown(lua_State* L)
{
	uint32_t keyCode;

	CArgReader argReader(L);
	argReader.ReadNumber(keyCode);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->GetKeyState(keyCode).IsDown());
	return 1;
}

int CLuaAltFuncDefs::IsKeyToggled(lua_State* L)
{
	uint32_t keyCode;

	CArgReader argReader(L);
	argReader.ReadNumber(keyCode);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->GetKeyState(keyCode).IsToggled());
	return 1;
}

int CLuaAltFuncDefs::AreControlsEnabled(lua_State* L)
{
	lua_pushboolean(L, Core->AreControlsEnabled());
	return 1;
}

int CLuaAltFuncDefs::SetCursorPosition(lua_State* L)
{
	alt::Vector2i position;

	CArgReader argReader(L);
	argReader.ReadVector(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetCursorPosition(position);

	return 0;
}

int CLuaAltFuncDefs::GetCursorPosition(lua_State* L)
{
	lua_pushvector2(L, Core->GetCursorPosition());
	return 1;
}

int CLuaAltFuncDefs::SetConfigFlag(lua_State* L)
{
	std::string flag;
	bool state;

	CArgReader argReader(L);
	argReader.ReadString(flag);
	argReader.ReadBool(state);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetConfigFlag(flag, state);

	return 0;
}

int CLuaAltFuncDefs::GetConfigFlag(lua_State* L)
{
	std::string flag;

	CArgReader argReader(L);
	argReader.ReadString(flag);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->GetConfigFlag(flag));

	return 1;
}

int CLuaAltFuncDefs::DoesConfigFlagExist(lua_State* L)
{
	std::string flag;

	CArgReader argReader(L);
	argReader.ReadString(flag);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->DoesConfigFlagExist(flag));

	return 1;
}

int CLuaAltFuncDefs::GetLicenseHash(lua_State* L)
{
	lua_pushstring(L, Core->GetLicenseHash());
	return 1;
}

int CLuaAltFuncDefs::GetLocale(lua_State* L)
{
	lua_pushstring(L, Core->GetLocale());
	return 1;
}

int CLuaAltFuncDefs::IsInStreamerMode(lua_State* L)
{
	lua_pushboolean(L, Core->IsInStreamerMode());
	return 1;
}

int CLuaAltFuncDefs::IsMenuOpen(lua_State* L)
{
	lua_pushboolean(L, Core->IsMenuOpen());
	return 1;
}

int CLuaAltFuncDefs::IsConsoleOpen(lua_State* L)
{
	lua_pushboolean(L, Core->IsConsoleOpen());
	return 1;
}

int CLuaAltFuncDefs::GetTextureFromDrawable(lua_State* L)
{
	uint32_t modelHash;
	std::string targetTextureName;

	CArgReader argReader(L);
	argReader.ReadNumber(modelHash);
	argReader.ReadString(targetTextureName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, nullptr != Core->GetTextureFromDrawable(modelHash, targetTextureName));

	return 1;
}

int CLuaAltFuncDefs::RequestIPL(lua_State* L)
{
	std::string ipl;

	CArgReader argReader(L);
	argReader.ReadString(ipl);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->RequestIPL(ipl);

	return 0;
}

int CLuaAltFuncDefs::RemoveIPL(lua_State* L)
{
	std::string ipl;

	CArgReader argReader(L);
	argReader.ReadString(ipl);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->RemoveIPL(ipl);

	return 0;
}

int CLuaAltFuncDefs::BeginScaleformMovieMethodMinimap(lua_State* L)
{
	std::string methodName;

	CArgReader argReader(L);
	argReader.ReadString(methodName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->BeginScaleformMovieMethodMinimap(methodName));

	return 1;
}

int CLuaAltFuncDefs::GetMsPerGameMinute(lua_State* L)
{
	lua_pushnumber(L, Core->GetMsPerGameMinute());
	return 1;
}

int CLuaAltFuncDefs::SetMsPerGameMinute(lua_State* L)
{
	int32_t val;

	CArgReader argReader(L);
	argReader.ReadNumber(val);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetMsPerGameMinute(val);

	return 0;
}

int CLuaAltFuncDefs::SetWeatherCycle(lua_State* L)
{
	alt::MValueArgs args;

	CArgReader argReader(L);
	argReader.ReadArguments(args);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	L_ASSERT(args[0]->GetType() == alt::IMValue::Type::LIST, "weathers must be an array");
	L_ASSERT(args[1]->GetType() == alt::IMValue::Type::LIST, "timeMultipliers must be an array");

	auto weathers = args[0].As<alt::IMValueList>();
	auto multipliers = args[1].As<alt::IMValueList>();

	L_ASSERT(weathers->GetSize() <= 256, "weathers count must be <= 256");
	L_ASSERT(multipliers->GetSize() <= 256, "multipliers count must be <= 256");
	L_ASSERT(weathers->GetSize() == multipliers->GetSize(), "weathers count and multipliers count must be the same");

	alt::Array<uint8_t> weathersVec;
	alt::Array<uint8_t> multipliersVec;

	for (int i = 0; i < weathers->GetSize(); ++i)
	{
		auto weatherVal = weathers->Get(i);
		if (weathers->GetType() != alt::IMValue::Type::INT)
			continue;

		auto multiplierVal = multipliers->Get(i);
		if (multiplierVal->GetType() != alt::IMValue::Type::INT)
			continue;

		uint32_t weatherNum = weatherVal.As<alt::IMValueInt>()->Value();
		L_ASSERT(weatherNum >= 0 && weatherNum <= 14, "weather ids must be >= 0 && <= 14");
		weathersVec.Push(weatherNum);

		uint32_t multiplierNum = multiplierVal.As<alt::IMValueInt>()->Value();
		L_ASSERT(multiplierNum > 0 && multiplierNum <= 720, "multipliers must be > 0 && <= 720");
		multipliersVec.Push(multiplierNum);
	}

	Core->SetWeatherCycle(weathersVec, multipliersVec);

	return 0;
}

int CLuaAltFuncDefs::SetWeatherSyncActive(lua_State* L)
{
	bool active;

	CArgReader argReader(L);
	argReader.ReadBool(active);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetWeatherSyncActive(active);

	return 0;
}

int CLuaAltFuncDefs::SetCamFrozen(lua_State* L)
{
	bool frozen;

	CArgReader argReader(L);
	argReader.ReadBool(frozen);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetCamFrozen(frozen);

	return 0;
}

int CLuaAltFuncDefs::GetPermissionState(lua_State* L)
{
	uint8_t permission;

	CArgReader argReader(L);
	argReader.ReadNumber(permission);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, static_cast<uint8_t>(Core->GetPermissionState((alt::Permission)permission)));

	return 1;
}

struct ScreenshotHelper
{
	lua_State* L;
	int functionIndex;
};

int CLuaAltFuncDefs::TakeScreenshot(lua_State* L)
{
	int functionIndex;

	CArgReader argReader(L);
	argReader.ReadFunction(functionIndex);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto state = Core->GetPermissionState(alt::Permission::ScreenCapture);
	L_ASSERT(state != alt::PermissionState::Denied, "No permissions");
	L_ASSERT(state != alt::PermissionState::Unspecified, "Permissions not specified");

	auto args = new ScreenshotHelper;
	args->L = L;
	args->functionIndex = functionIndex;

	Core->TakeScreenshot([](alt::StringView base64, const void* userData)
	{
		auto args = (ScreenshotHelper*)userData;
		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(args->L);
		L_ASSERT(resourceImpl != nullptr, "lua state not found when executing TakeScreenshot");

		auto voidPtr = resourceImpl->GetFunctionRefByID(args->functionIndex);

		lua_rawgeti(args->L, LUA_REGISTRYINDEX, args->functionIndex);
		lua_pushstring(args->L, base64.CStr());

		lua_call(args->L, 1, 0);

		resourceImpl->RemoveFunctionRef(voidPtr);
		delete args;
	}, args);

	return 0;
}

int CLuaAltFuncDefs::TakeScreenshotGameOnly(lua_State* L)
{
	int functionIndex;

	CArgReader argReader(L);
	argReader.ReadFunction(functionIndex);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto state = Core->GetPermissionState(alt::Permission::ScreenCapture);
	L_ASSERT(state != alt::PermissionState::Denied, "No permissions");
	L_ASSERT(state != alt::PermissionState::Unspecified, "Permissions not specified");

	auto args = new ScreenshotHelper;
	args->L = L;
	args->functionIndex = functionIndex;

	Core->TakeScreenshotGameOnly([](alt::StringView base64, const void* userData)
	{
		auto args = (ScreenshotHelper*)userData;
		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(args->L);
		L_ASSERT(resourceImpl != nullptr, "lua state not found when executing TakeScreenshot");

		auto voidPtr = resourceImpl->GetFunctionRefByID(args->functionIndex);

		lua_rawgeti(args->L, LUA_REGISTRYINDEX, args->functionIndex);
		lua_pushstring(args->L, base64.CStr());

		lua_call(args->L, 1, 0);

		resourceImpl->RemoveFunctionRef(voidPtr);
		delete args;
	}, args);

	return 0;
}

int CLuaAltFuncDefs::SetAngularVelocity(lua_State* L)
{
	uint32_t index;
	alt::Vector4f velocity;

	CArgReader argReader(L);
	argReader.ReadNumber(index);
	argReader.ReadVector(velocity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	Core->SetAngularVelocity(index, velocity);
	
	return 0;
}

int CLuaAltFuncDefs::IsGameFocused(lua_State* L)
{
	lua_pushboolean(L, Core->IsGameFocused());
	return 1;
}
#endif

int CLuaAltFuncDefs::GetSyncedMetaData(lua_State* L)
{
	std::string key;

	CArgReader argReader(L);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushmvalue(L, Core->GetSyncedMetaData(key));

	return 1;
}

int CLuaAltFuncDefs::HasSyncedMetaData(lua_State* L)
{
	std::string key;

	CArgReader argReader(L);
	argReader.ReadString(key);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->HasSyncedMetaData(key));

	return 1;
}

int CLuaAltFuncDefs::GetRequiredPermissions(lua_State* L)
{
	auto requiredPermissions = Core->GetRequiredPermissions();
	lua_newtable(L);

	unsigned short index = 1;
	for (auto &perm : requiredPermissions)
	{
		lua_pushnumber(L, index);
		lua_pushnumber(L, static_cast<int>(perm));
		lua_rawset(L, -3);

		index++;
	}

	return 1;
}

int CLuaAltFuncDefs::GetOptionalPermissions(lua_State* L)
{
	auto optionalPermissions = Core->GetOptionalPermissions();
	lua_newtable(L);

	unsigned short index = 1;
	for (auto& perm : optionalPermissions)
	{
		lua_pushnumber(L, index);
		lua_pushnumber(L, static_cast<int>(perm));
		lua_rawset(L, -3);

		index++;
	}

	return 1;
}

int CLuaAltFuncDefs::Export(lua_State* L)
{
	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);

	std::string exportName;
	int functionRef;

	CArgReader argReader(L);
	argReader.ReadString(exportName);
	argReader.ReadFunction(functionRef);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	if (resource->IsExportExists(exportName))
	{
		Core->LogError("Warning: Export \"" + exportName + "\" already exists. It will be overwritten by the new function.");
	}

	resource->AddExport(exportName, new CLuaResourceImpl::LuaFunction(resource, functionRef));

	return 0;
}

int CLuaAltFuncDefs::IsDebug(lua_State* L)
{
	lua_pushboolean(L, Core->IsDebug());
	return 1;
}

int CLuaAltFuncDefs::FileExists(lua_State* L)
{
	std::string filePath;

	CArgReader argReader(L);
	argReader.ReadString(filePath);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, Core->FileExists(filePath));

	return 1;
}

int CLuaAltFuncDefs::FileRead(lua_State* L)
{
	std::string filePath;

	CArgReader argReader(L);
	argReader.ReadString(filePath);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, Core->FileRead(filePath).CStr());

	return 1;
}

int CLuaAltFuncDefs::GetEntityByID(lua_State* L)
{
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, entity);

	return 1;
}

int CLuaAltFuncDefs::GetVersion(lua_State* L)
{
	lua_pushstring(L, Core->GetVersion().CStr());
	return 1;
}

int CLuaAltFuncDefs::GetBranch(lua_State* L)
{
	lua_pushstring(L, Core->GetBranch().CStr());
	return 1;
}

int CLuaAltFuncDefs::Hash(lua_State* L)
{
	std::string hashKey;

	CArgReader argReader(L);
	argReader.ReadString(hashKey);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, Core->Hash(hashKey));

	return 1;
}

int CLuaAltFuncDefs::OnServer(lua_State* L)
{
	std::string eventName;
	int functionRef;

	unsigned int ha = 1;
	lua_pushnumber(L, ha);

	CArgReader argReader(L);
	argReader.ReadString(eventName);
	argReader.ReadFunction(functionRef);
	//argReader.ReadFunctionComplete();

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);

	lua_pushboolean(L, resource->RegisterEvent(eventName, functionRef));

	return 1;
}

int CLuaAltFuncDefs::OffServer(lua_State* L)
{
	std::string eventName;
	int functionRef;

	CArgReader argReader(L);
	argReader.ReadString(eventName);
	argReader.ReadFunction(functionRef);
	//argReader.ReadFunctionComplete();

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);

	lua_pushboolean(L, resource->RemoveEvent(eventName, functionRef));

	return 1;
}

int CLuaAltFuncDefs::OnClient(lua_State* L)
{
	std::string eventName;
	int functionRef;

	unsigned int ha = 1;
	lua_pushnumber(L, ha);

	CArgReader argReader(L);
	argReader.ReadString(eventName);
	argReader.ReadFunction(functionRef);
	//argReader.ReadFunctionComplete();

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);

	lua_pushboolean(L, resource->RegisterClientEvent(eventName, functionRef));

	return 1;
}

int CLuaAltFuncDefs::OffClient(lua_State* L)
{
	std::string eventName;
	int functionRef;

	CArgReader argReader(L);
	argReader.ReadString(eventName);
	argReader.ReadFunction(functionRef);
	//argReader.ReadFunctionComplete();

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);

	lua_pushboolean(L, resource->RemoveClientEvent(eventName, functionRef));

	return 1;
}

int CLuaAltFuncDefs::EmitServer(lua_State* L)
{
	std::string eventName;
	alt::MValueArgs args;

	CArgReader argReader(L);
	argReader.ReadString(eventName);
	argReader.ReadArguments(args);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

#ifdef ALT_SERVER_API
	Core->TriggerLocalEvent(eventName, args);
#else
	Core->TriggerServerEvent(eventName, args);
#endif

	return 0;
}

int CLuaAltFuncDefs::AltIndex(lua_State* L)
{
	////Route all index accessing to the default handler
	//lua_stacktrace(L, "AltIndex");

	//int results = CLuaFunctionDefs::Index(L);
	//if (!lua_isnil(L, -1))
	//{
	//	//return results
	//	return results;
	//}

	//pop nil
	//lua_pop(L, 1);

	//string expected on top of the stack
	L_ASSERT(lua_isstring(L, -1), "String expected");

	//check if global namespace has the function, or if its a class
	lua_getglobal(L, luaL_checkstring(L, -1));
	if (lua_isfunction(L, -1) || lua_istable(L, -1))
	{
		return 1;
	}

	//nothing found
	return 0;
}

/*int CLuaAltFuncDefs::AltIndex(lua_State* L)
{
	//Route all index accessing to the default handler
	int results = CLuaFunctionDefs::Index(L);
	if (!lua_isnil(L, -1))
	{
		//return results
		return results;
	}

	//pop nil
	lua_pop(L, 1);

	lua_stacktrace(L, "after pop");

	//string expected on top of the stack
	L_ASSERT(lua_isstring(L, -1), "String expected");

	//check if global namespace has the function, or if its a class
	lua_getglobal(L, luaL_checkstring(L, -1));
	if (lua_isfunction(L, -1) || lua_istable(L, -1))
	{
		return 1;
	}

	//nothing found
	return 0;
}*/

int CLuaAltFuncDefs::dofile(lua_State* L)
{
	std::string filePath;

	CArgReader argReader(L);
	argReader.ReadString(filePath);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);
	auto file = (resource->GetWorkingPath() + filePath + ".lua");
	auto &loadedFiles = resource->GetLoadedFiles();

	if (loadedFiles.find(filePath) != loadedFiles.end())
	{
		Core->LogInfo("Found: " + filePath);
		return 0;
	}

	Core->LogInfo("Load: " + filePath);

	if (luaL_dofile(L, file.c_str()))
	{
		//Sadly far from perfect
		Core->LogError(" Unable to load \"" + filePath + "\"");

		//Get the error from the top of the stack
		if (lua_isstring(L, -1))
			Core->LogError(" Error: " + alt::String(luaL_checkstring(L, -1)));

		//Close virtual machine and point to null pointer
		//lua_close(L);
		//this->resourceState = nullptr;

		return 0;
	}
	else
	{
		loadedFiles.insert(std::pair<std::string, bool>(std::string(filePath.c_str()), true));
		Core->LogInfo("Add loadedFiles: " + file);
		Core->LogInfo("LoadedFiles: " + std::to_string(loadedFiles.size()));
	}

	return 0;
}

int CLuaAltFuncDefs::inext(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 2);

	if (lua_next(L, 1))
		return 2;
	else
	{
		lua_pushnil(L);
		return 1;
	}
}

int CLuaAltFuncDefs::pairs(lua_State* L)
{
	luaL_getmetafield(L, 1, "__pairs");

	if (lua_isfunction(L, -1))
	{
		lua_call(L, 0, 1);
		lua_replace(L, 1);
	}

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_pushvalue(L, 1);
	lua_pushnil(L);

	return 3;
}

int CLuaAltFuncDefs::ipairsaux(lua_State* L)
{
	//Core->LogInfo("CLuaAltFuncDefs::ipairsaux");

	int i = luaL_checkint(L, 2);
	luaL_checktype(L, 1, LUA_TTABLE);
	i++;  /* next value */
	lua_pushinteger(L, i);
	lua_rawgeti(L, 1, i);
	//lua_stacktrace(L, "CLuaAltFuncDefs::ipairsaux");

	return (lua_isnil(L, -1)) ? 0 : 2;
}

int CLuaAltFuncDefs::ipairs(lua_State* L)
{
	//Core->LogInfo("CLuaAltFuncDefs::ipairs");
	luaL_getmetafield(L, 1, "__ipairs");
	
	if (lua_isfunction(L, -1))
	{
		lua_call(L, 0, 1);
		lua_replace(L, 1);
	}

	lua_pushvalue(L, lua_upvalueindex(1));
	lua_pushvalue(L, 1);
	lua_pushnumber(L, 0);

	//lua_stacktrace(L, "CLuaAltFuncDefs::ipairs1");

	return 3;
}

int CLuaAltFuncDefs::tostringtest(lua_State* L)
{
	//Core->LogInfo("CLuaAltFuncDefs::tostringtest");

	return 2;
}

int CLuaAltFuncDefs::Log(lua_State* L, LogType logType)
{
	CArgReader argReader(L);
	std::ostringstream message;

	for (int i = 0; i < argReader.GetArgNum(); i++)
	{
		message << alt::String(argReader.ToString());

		if (i != (argReader.GetArgNum() - 1))
			message << '\t';
	}

	switch (logType)
	{
	case LogType::LOG_COLORED:
		Core->LogColored(message.str());
		break;

	case LogType::LOG_DEBUG:
		Core->LogDebug(message.str());
		break;

	case LogType::LOG_ERROR:
		Core->LogError(message.str());
		break;

	case LogType::LOG_INFO:
		Core->LogInfo(message.str());
		break;

	case LogType::LOG_WARNING:
		Core->LogWarning(message.str());
		break;
	}

	return 0;
}

int CLuaAltFuncDefs::LogInfo(lua_State* L)
{
	return CLuaAltFuncDefs::Log(L, LogType::LOG_INFO);
}

int CLuaAltFuncDefs::LogDebug(lua_State* L)
{
	return CLuaAltFuncDefs::Log(L, LogType::LOG_DEBUG);
}

int CLuaAltFuncDefs::LogWarning(lua_State* L)
{
	return CLuaAltFuncDefs::Log(L, LogType::LOG_WARNING);
}

int CLuaAltFuncDefs::LogError(lua_State* L)
{
	return CLuaAltFuncDefs::Log(L, LogType::LOG_ERROR);
}

int CLuaAltFuncDefs::LogColored(lua_State* L)
{
	return CLuaAltFuncDefs::Log(L, LogType::LOG_COLORED);
}
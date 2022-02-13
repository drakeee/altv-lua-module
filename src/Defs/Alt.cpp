#include <Main.h>
#include <sstream>

namespace lua::Class
{
	const char* Alt::ClassName = "alt";
	void Alt::Init(lua_State* L)
	{
		DEBUG_INFO("Alt::Init");
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
		lua_globalfunction(L, "require", require);

		lua_globalfunction(L, "on", OnClient);
	#endif
		lua_globalfunction(L, "onServer", OnServer);
		lua_globalfunction(L, "offServer", OffServer);
		lua_globalfunction(L, "onClient", OnClient);
		lua_globalfunction(L, "offClient", OffClient);

	#ifdef ALT_SERVER_API
		lua_globalfunction(L, "emit", EmitServer);
		lua_globalfunction(L, "emitAllClients", EmitClientAll);
	#else
		lua_globalfunction(L, "emit", EmitClient);
	#endif
		lua_globalfunction(L, "emitServer", EmitServer);
		lua_globalfunction(L, "emitClient", EmitClient);

		lua_globalfunction(L, "nextTick", NextTick);
		lua_globalfunction(L, "everyTick", EveryTick);
		lua_globalfunction(L, "setTimeout", SetTimeout);
		lua_globalfunction(L, "setInterval", SetInterval);
		lua_globalfunction(L, "clearTimer", ClearTimer);
		lua_globalfunction(L, "clearNextTick", ClearTimer);
		lua_globalfunction(L, "clearEveryTick", ClearTimer);
		lua_globalfunction(L, "clearTimeout", ClearTimer);
		lua_globalfunction(L, "clearInterval", ClearTimer);

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

		lua_globalfunction(L, "getModuleTime", GetModuleTime);

	#ifdef ALT_SERVER_API
		lua_globalfunction(L, "getRootDirectory", GetRootDirectory);

		lua_globalfunction(L, "startResource", StartResource);
		lua_globalfunction(L, "stopResource", StopResource);
		lua_globalfunction(L, "restartResource", RestartResource);

		lua_globalfunction(L, "setSyncedMetaData", SetSyncedMetaData);
		lua_globalfunction(L, "deleteSyncedMetaData", DeleteSyncedMetaData);

		lua_globalfunction(L, "getPlayersByName", GetPlayersByName);

		lua_globalfunction(L, "getNetTime", GetNetTime);

		lua_globalfunction(L, "setPassword", SetPassword);
		lua_globalfunction(L, "hashServerPassword", HashServerPassword);

		lua_globalfunction(L, "stopServer", StopServer);

		lua_globalfunction(L, "getVehicleModelInfoByHash", GetVehicleModelByHash);

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
		lua_globalfunction(L, "toggleGameControls", ToggleGameControls);
		lua_globalfunction(L, "showCursor", ShowCursor);
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

		lua_globalfunction(L, "loadModel", LoadModel);
		lua_globalfunction(L, "loadModelAsync", LoadModelAsync);

		lua_globalfunction(L, "loadYtyp", LoadYtyp);
		lua_globalfunction(L, "unloadYtyp", UnloadYtyp);

		lua_globalfunction(L, "getHeadshotBase64", GetHeadshotBase64);

		lua_globalfunction(L, "setPedDlcClothes", SetDlcClothes);
		lua_globalfunction(L, "setPedDlcProps", SetDlcProps);
		lua_globalfunction(L, "clearPedProps", ClearProps);

		lua_globalfunction(L, "setWatermarkPosition", SetWatermarkPosition);
		lua_globalfunction(L, "getFps", GetFps);
		lua_globalfunction(L, "getPing", GetPing);
		lua_globalfunction(L, "getTotalPacketsSent", GetTotalPacketsSent);
		lua_globalfunction(L, "getTotalPacketsLost", GetTotalPacketsLost);
		lua_globalfunction(L, "getServerIp", GetServerIp);
		lua_globalfunction(L, "getServerPort", GetServerPort);
		lua_globalfunction(L, "getClientPath", GetClientPath);

		lua_globalfunction(L, "hasLocalMeta", HasLocalMetaData);
		lua_globalfunction(L, "getLocalMeta", GetLocalMetaData);

		lua_globalfunction(L, "copyToClipboard", CopyToClipboard);

		lua_globalfunction(L, "toggleRmlControls", ToggleRmlControl);
		lua_globalfunction(L, "loadRmlFont", LoadRmlFontFace);

		lua_globalfunction(L, "worldToScreen", WorldToScreen);
		lua_globalfunction(L, "screenToWorld", ScreenToWorld);
		lua_globalfunction(L, "getCamPos", GetCamPos);
		lua_globalfunction(L, "setMinimapComponentPosition", SetMinimapComponentPosition);
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
		lua_pushcfunction(L, Alt::LogInfo);
		lua_rawset(L, -3);


		//Hacky way to implement custom __pairs and __ipairs meta events
		//Note: both __pairs and __ipairs metaevents should return only a table
		//For example:
		/*
		int Vehicle::ipairs(lua_State* L)
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
		lua_pushcfunction(L, Alt::ipairsaux);
		lua_rawset(L, -3);

		lua_pushstring(L, "inext");
		lua_pushcfunction(L, Alt::inext);
		lua_rawset(L, -3);

		lua_pushstring(L, "_pairs");
		lua_getglobal(L, "pairs");
		lua_rawset(L, -3);

		lua_pushstring(L, "_ipairs");
		lua_getglobal(L, "ipairs");
		lua_rawset(L, -3);

		lua_pushstring(L, "pairs");
		lua_getglobal(L, "inext");
		lua_pushcclosure(L, Alt::pairs, 1);
		lua_rawset(L, -3);

		lua_pushstring(L, "ipairs");
		lua_getglobal(L, "ipairsaux");
		lua_pushcclosure(L, Alt::ipairs, 1);
		lua_rawset(L, -3);

	#ifdef ALT_SERVER_API
		auto runtime = &LuaScriptRuntime::Instance();
		lua_pushconfig(L, &runtime->GetServerConfig());
		lua_setglobal(L, "serverConfig");
	#endif

		/*lua_pushstring(L, "dofile");
		lua_pushcfunction(L, dofile);
		lua_rawset(L, -3);*/

		lua_pop(L, 1);

		DEBUG_INFO("Alt::Init ...done");
	}

	int Alt::SetMetaData(lua_State* L)
	{
		std::string key;
		alt::MValue value;

		ArgumentReader argReader(L);
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

	int Alt::GetMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushmvalue(L, Core->GetMetaData(key));

		return 1;
	}

	int Alt::DeleteMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->DeleteMetaData(key);

		return 0;
	}

	int Alt::HasMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->HasMetaData(key));

		return 1;
	}

	int Alt::GetModuleTime(lua_State* L)
	{
		lua_pushnumber(L, LuaScriptRuntime::Instance().GetModuleTime());
		return 1;
	}

	#ifdef ALT_SERVER_API
	int Alt::GetRootDirectory(lua_State* L)
	{
		lua_pushstring(L, Core->GetRootDirectory().CStr());
		return 1;
	}

	int Alt::StartResource(lua_State* L)
	{
		std::string resourceName;

		ArgumentReader argReader(L);
		argReader.ReadString(resourceName);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushresource(L, Core->StartResource(resourceName));

		return 1;
	}

	int Alt::StopResource(lua_State* L)
	{
		std::string resourceName;

		ArgumentReader argReader(L);
		argReader.ReadString(resourceName);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->StopResource(resourceName);

		return 0;
	}

	int Alt::RestartResource(lua_State* L)
	{
		std::string resourceName;

		ArgumentReader argReader(L);
		argReader.ReadString(resourceName);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->RestartResource(resourceName);

		return 0;
	}

	int Alt::SetSyncedMetaData(lua_State* L)
	{
		std::string key;
		alt::MValue value;

		ArgumentReader argReader(L);
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

	int Alt::DeleteSyncedMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->DeleteSyncedMetaData(key);

		return 0;
	}

	int Alt::GetPlayersByName(lua_State* L)
	{
		std::string playersName;

		ArgumentReader argReader(L);
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

	int Alt::GetNetTime(lua_State* L)
	{
		lua_pushnumber(L, Core->GetNetTime());
		return 1;
	}

	int Alt::SetPassword(lua_State* L)
	{
		std::string password;

		ArgumentReader argReader(L);
		argReader.ReadString(password);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetPassword(password);

		return 0;
	}

	int Alt::HashServerPassword(lua_State* L)
	{
		std::string password;

		ArgumentReader argReader(L);
		argReader.ReadString(password);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, Core->HashServerPassword(password));
		return 1;
	}

	int Alt::StopServer(lua_State* L)
	{
		Core->StopServer();
		return 0;
	}

	int Alt::GetVehicleModelByHash(lua_State* L)
	{
		DEBUG_INFO("GetVehicleModelByHash1");
		uint32_t hash;

		ArgumentReader argReader(L);
		argReader.ReadNumber(hash);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		DEBUG_INFO("GetVehicleModelByHash2");

		const alt::VehicleModelInfo& modelInfo = Core->GetVehicleModelByHash(hash);
		if (modelInfo.modelType == alt::VehicleModelInfo::Type::INVALID)
		{
			lua_pushboolean(L, false);
			return 1;
		}

		DEBUG_INFO("GetVehicleModelByHash3");

		lua_newtable(L);
		{
			lua_setfield(L, -1, "title", modelInfo.title);
			lua_setfield(L, -1, "type", (int)modelInfo.modelType);
			lua_setfield(L, -1, "wheelsCount", modelInfo.wheelsCount);
			lua_setfield(L, -1, "hasArmoredWindows", modelInfo.hasArmoredWindows);
			lua_setfield(L, -1, "primaryColor", modelInfo.primaryColor);
			lua_setfield(L, -1, "secondaryColor", modelInfo.secondaryColor);
			lua_setfield(L, -1, "pearlColor", modelInfo.pearlColor);
			lua_setfield(L, -1, "wheelsColor", modelInfo.wheelsColor);
			lua_setfield(L, -1, "interiorColor", modelInfo.interiorColor);
			lua_setfield(L, -1, "dashboardColor", modelInfo.dashboardColor);
			lua_setfield(L, -1, "extras", modelInfo.extras);
			lua_setfield(L, -1, "defaultExtras", modelInfo.defaultExtras);

			DEBUG_INFO("GetVehicleModelByHash4");

			lua_pushstring(L, "availableModkits");
			lua_newtable(L);
			for (size_t i = 0; i < std::size(modelInfo.modkits); i++)
			{
				lua_pushnumber(L, i + 1);
				lua_pushnumber(L, modelInfo.modkits[i]);
				lua_rawset(L, -3);
			}
			lua_rawset(L, -3);

			DEBUG_INFO("GetVehicleModelByHash5");
		}

		return 1;
	}

	#else
	int Alt::require(lua_State* L)
	{
		std::string path;

		ArgumentReader argReader(L);
		argReader.ReadString(path);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in require");
			return 0;
		}

		std::replace(path.begin(), path.end(), '.', '/');
		path.append(".lua");

		lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED_PACKAGE");
		lua_getfield(L, 2, path.c_str());

		lua_stacktrace(L, "require");

		if (lua_isnil(L, -1))
		{
			if (!resourceImpl->IsScriptExists(path))
			{
				Core->LogError(" Unable to load file \"" + path + "\": not exists");
				return 0;
			}

			alt::String script{ resourceImpl->GetScript(path) };
			if (luaL_dostring(L, script.CStr()))
			{
				//Sadly far from perfect
				Core->LogError(" Unable to script \"" + path + "\"");

				//Get the error from the top of the stack
				if (lua_isstring(L, -1))
					Core->LogError(" Error: " + alt::String(luaL_checkstring(L, -1)));

				return false;
			}

			if (lua_isnil(L, -1))
			{
				lua_pushboolean(L, true);
				lua_setfield(L, 2, path.c_str());
			}
			else
				lua_setfield(L, 2, path.c_str());
		}

		lua_getfield(L, 2, path.c_str());

		return 1;
	}

	int Alt::SetCharStat(lua_State* L)
	{
		std::string statName;

		ArgumentReader argReader(L);
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

	int Alt::GetCharStat(lua_State* L)
	{
		std::string statName;

		ArgumentReader argReader(L);
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

	int Alt::ResetCharStat(lua_State* L)
	{
		std::string statName;

		ArgumentReader argReader(L);
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

	int Alt::IsSandbox(lua_State* L)
	{
		lua_pushboolean(L, Core->IsSandbox());
		return 1;
	}

	int Alt::IsKeyDown(lua_State* L)
	{
		uint32_t keyCode;

		ArgumentReader argReader(L);
		argReader.ReadNumber(keyCode);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->GetKeyState(keyCode).IsDown());
		return 1;
	}

	int Alt::IsKeyToggled(lua_State* L)
	{
		uint32_t keyCode;

		ArgumentReader argReader(L);
		argReader.ReadNumber(keyCode);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->GetKeyState(keyCode).IsToggled());
		return 1;
	}

	int Alt::AreControlsEnabled(lua_State* L)
	{
		lua_pushboolean(L, Core->AreControlsEnabled());
		return 1;
	}

	int Alt::SetCursorPosition(lua_State* L)
	{
		alt::Vector2i position;

		ArgumentReader argReader(L);
		argReader.ReadVector(position);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetCursorPosition(position);

		return 0;
	}

	int Alt::GetCursorPosition(lua_State* L)
	{
		lua_pushvector2(L, Core->GetCursorPosition());
		return 1;
	}

	int Alt::SetConfigFlag(lua_State* L)
	{
		std::string flag;
		bool state;

		ArgumentReader argReader(L);
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

	int Alt::GetConfigFlag(lua_State* L)
	{
		std::string flag;

		ArgumentReader argReader(L);
		argReader.ReadString(flag);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->GetConfigFlag(flag));

		return 1;
	}

	int Alt::DoesConfigFlagExist(lua_State* L)
	{
		std::string flag;

		ArgumentReader argReader(L);
		argReader.ReadString(flag);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->DoesConfigFlagExist(flag));

		return 1;
	}

	int Alt::GetLicenseHash(lua_State* L)
	{
		lua_pushstring(L, Core->GetLicenseHash());
		return 1;
	}

	int Alt::GetLocale(lua_State* L)
	{
		lua_pushstring(L, Core->GetLocale());
		return 1;
	}

	int Alt::IsInStreamerMode(lua_State* L)
	{
		lua_pushboolean(L, Core->IsInStreamerMode());
		return 1;
	}

	int Alt::IsMenuOpen(lua_State* L)
	{
		lua_pushboolean(L, Core->IsMenuOpen());
		return 1;
	}

	int Alt::IsConsoleOpen(lua_State* L)
	{
		lua_pushboolean(L, Core->IsConsoleOpen());
		return 1;
	}

	int Alt::ToggleGameControls(lua_State* L)
	{
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in ToggleGameControls");
			return 0;
		}

		resourceImpl->GetResource()->ToggleGameControls(state);

		return 0;
	}

	int Alt::ShowCursor(lua_State* L)
	{
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in ShowCursor");
			return 0;
		}

		if (!resourceImpl->GetResource()->ToggleCursor(state))
		{
			Core->LogWarning("Cursor state can't go < 0");
		}

		return 0;
	}

	int Alt::GetTextureFromDrawable(lua_State* L)
	{
		uint32_t modelHash;
		std::string targetTextureName;

		ArgumentReader argReader(L);
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

	int Alt::RequestIPL(lua_State* L)
	{
		std::string ipl;

		ArgumentReader argReader(L);
		argReader.ReadString(ipl);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->RequestIPL(ipl);

		return 0;
	}

	int Alt::RemoveIPL(lua_State* L)
	{
		std::string ipl;

		ArgumentReader argReader(L);
		argReader.ReadString(ipl);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->RemoveIPL(ipl);

		return 0;
	}

	int Alt::BeginScaleformMovieMethodMinimap(lua_State* L)
	{
		std::string methodName;

		ArgumentReader argReader(L);
		argReader.ReadString(methodName);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->BeginScaleformMovieMethodMinimap(methodName));

		return 1;
	}

	int Alt::GetMsPerGameMinute(lua_State* L)
	{
		lua_pushnumber(L, Core->GetMsPerGameMinute());
		return 1;
	}

	int Alt::SetMsPerGameMinute(lua_State* L)
	{
		int32_t val;

		ArgumentReader argReader(L);
		argReader.ReadNumber(val);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetMsPerGameMinute(val);

		return 0;
	}

	int Alt::SetWeatherCycle(lua_State* L)
	{
		alt::MValueArgs args;

		ArgumentReader argReader(L);
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

	int Alt::SetWeatherSyncActive(lua_State* L)
	{
		bool active;

		ArgumentReader argReader(L);
		argReader.ReadBool(active);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetWeatherSyncActive(active);

		return 0;
	}

	int Alt::SetCamFrozen(lua_State* L)
	{
		bool frozen;

		ArgumentReader argReader(L);
		argReader.ReadBool(frozen);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetCamFrozen(frozen);

		return 0;
	}

	int Alt::GetPermissionState(lua_State* L)
	{
		uint8_t permission;

		ArgumentReader argReader(L);
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

	int Alt::TakeScreenshot(lua_State* L)
	{
		int functionIndex;

		ArgumentReader argReader(L);
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
			auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(args->L);
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

	int Alt::TakeScreenshotGameOnly(lua_State* L)
	{
		int functionIndex;

		ArgumentReader argReader(L);
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
			auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(args->L);
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

	int Alt::SetAngularVelocity(lua_State* L)
	{
		uint32_t index;
		alt::Vector4f velocity;

		ArgumentReader argReader(L);
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

	int Alt::IsGameFocused(lua_State* L)
	{
		lua_pushboolean(L, Core->IsGameFocused());
		return 1;
	}

	int Alt::LoadModel(lua_State* L)
	{
		uint32_t hash;

		ArgumentReader argReader(L);
		argReader.ReadNumber(hash);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->LoadModel(hash);
		Core->LogWarning("loadModel is deprecated and it will be removed in the future. Please use the native requestModel.");
		return 0;
	}

	int Alt::LoadModelAsync(lua_State* L)
	{
		uint32_t hash;

		ArgumentReader argReader(L);
		argReader.ReadNumber(hash);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->LoadModelAsync(hash);
		Core->LogWarning("loadModelAsync is deprecated and it will be removed in the future. Please use the native requestModel.");
		return 0;
	}

	int Alt::LoadYtyp(lua_State* L)
	{
		std::string path;

		ArgumentReader argReader(L);
		argReader.ReadString(path);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->LoadYtyp(path));

		return 1;
	}

	int Alt::UnloadYtyp(lua_State* L)
	{
		std::string path;

		ArgumentReader argReader(L);
		argReader.ReadString(path);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->UnloadYtyp(path));

		return 1;
	}

	int Alt::GetHeadshotBase64(lua_State* L)
	{
		int id;

		ArgumentReader argReader(L);
		argReader.ReadNumber(id);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, Core->HeadshotToBase64(id));

		return 1;
	}

	int Alt::SetDlcClothes(lua_State* L)
	{
		int32_t scriptID;
		uint8_t component;
		uint16_t drawable;
		uint8_t texture;
		uint32_t dlc;
		uint8_t palette;

		ArgumentReader argReader(L);
		argReader.ReadNumber(scriptID);
		argReader.ReadNumber(dlc);
		argReader.ReadNumber(component);
		argReader.ReadNumber(drawable);
		argReader.ReadNumber(texture);
		argReader.ReadNumberDefault<uint8_t>(palette, 2);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetDlcClothes(scriptID, component, drawable, texture, palette, dlc);

		return 0;
	}

	int Alt::SetDlcProps(lua_State* L)
	{
		int32_t scriptID;
		uint8_t component;
		uint16_t drawable;
		uint8_t texture;
		uint32_t dlc;

		ArgumentReader argReader(L);
		argReader.ReadNumber(scriptID);
		argReader.ReadNumber(dlc);
		argReader.ReadNumber(component);
		argReader.ReadNumber(drawable);
		argReader.ReadNumber(texture);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetDlcProps(scriptID, component, drawable, texture, dlc);

		return 0;
	}

	int Alt::ClearProps(lua_State* L)
	{
		int32_t scriptID;
		uint8_t component;

		ArgumentReader argReader(L);
		argReader.ReadNumber(scriptID);
		argReader.ReadNumber(component);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->ClearProps(scriptID, component);

		return 0;
	}

	int Alt::SetWatermarkPosition(lua_State* L)
	{
		uint8_t pos;

		ArgumentReader argReader(L);
		argReader.ReadNumber(pos);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}
	
		Core->SetWatermarkPosition(pos);

		return 0;
	}

	int Alt::GetFps(lua_State* L)
	{
		lua_pushnumber(L, Core->GetFps());
		return 1;
	}

	int Alt::GetPing(lua_State* L)
	{
		lua_pushnumber(L, Core->GetPing());
		return 1;
	}

	int Alt::GetTotalPacketsSent(lua_State* L)
	{
		lua_pushnumber(L, Core->GetTotalPacketsSent());
		return 1;
	}

	int Alt::GetTotalPacketsLost(lua_State* L)
	{
		lua_pushnumber(L, Core->GetTotalPacketsLost());
		return 1;
	}

	int Alt::GetServerIp(lua_State* L)
	{
		lua_pushstring(L, Core->GetServerIp());
		return 1;
	}

	int Alt::GetServerPort(lua_State* L)
	{
		lua_pushnumber(L, Core->GetServerPort());
		return 1;
	}

	int Alt::GetClientPath(lua_State* L)
	{
		lua_pushstring(L, Core->GetClientPath());
		return 1;
	}

	int Alt::HasLocalMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->HasLocalMetaData(key));

		return 1;
	}

	int Alt::GetLocalMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushmvalue(L, Core->GetLocalMetaData(key));

		return 1;
	}

	int Alt::CopyToClipboard(lua_State* L)
	{
		std::string value;

		ArgumentReader argReader(L);
		argReader.ReadString(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, (int)Core->CopyToClipboard(value));

		return 1;
	}

	int Alt::ToggleRmlDebugger(lua_State* L)
	{
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->ToggleRmlDebugger(state);

		return 0;
	}

	int Alt::LoadRmlFontFace(lua_State* L)
	{
		std::string path;
		std::string name;
		bool italic;
		bool bold;

		ArgumentReader argReader(L);
		argReader.ReadString(path);
		argReader.ReadString(name);
		argReader.ReadBoolDefault(italic, false);
		argReader.ReadBoolDefault(bold, false);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		lua_pushnumber(L, Core->LoadRmlFontFace(resourceImpl->GetResource(), path, resourceImpl->GetWorkingPath(), name, italic, bold));

		return 0;
	}

	int Alt::ToggleRmlControl(lua_State* L)
	{
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->ToggleRmlControl(state);

		return 0;
	}

	int Alt::WorldToScreen(lua_State* L)
	{
		alt::Vector3f pos;

		ArgumentReader argReader(L);
		argReader.ReadVector(pos);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector2(L, Core->WorldToScreen(pos));

		return 1;
	}

	int Alt::ScreenToWorld(lua_State* L)
	{
		alt::Vector2f pos;

		ArgumentReader argReader(L);
		argReader.ReadVector(pos);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector3(L, Core->ScreenToWorld(pos));

		return 1;
	}

	int Alt::GetCamPos(lua_State* L)
	{
		lua_pushvector3(L, Core->GetCamPos());

		return 1;
	}

	int Alt::SetMinimapComponentPosition(lua_State* L)
	{
		std::string name;
		char alignX;
		char alignY;
		alt::Vector2f pos;
		alt::Vector2f size;
		
		ArgumentReader argReader(L);
		argReader.ReadString(name);
		argReader.ReadNumber(alignX);
		argReader.ReadNumber(alignY);
		argReader.ReadVector(pos);
		argReader.ReadVector(size);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetMinimapComponentPosition(name, alignX, alignY, pos, size)

		return 0;	
	}
	#endif

	int Alt::GetSyncedMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushmvalue(L, Core->GetSyncedMetaData(key));

		return 1;
	}

	int Alt::HasSyncedMetaData(lua_State* L)
	{
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->HasSyncedMetaData(key));

		return 1;
	}

	int Alt::GetRequiredPermissions(lua_State* L)
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

	int Alt::GetOptionalPermissions(lua_State* L)
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

	int Alt::Export(lua_State* L)
	{
		auto runtime = &LuaScriptRuntime::Instance();
		auto resource = runtime->GetResourceImplFromState(L);

		std::string exportName;
		int functionRef;

		ArgumentReader argReader(L);
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

		resource->AddExport(exportName, new LuaResourceImpl::LuaFunction(resource, functionRef));

		return 0;
	}

	int Alt::IsDebug(lua_State* L)
	{
		lua_pushboolean(L, Core->IsDebug());
		return 1;
	}

	int Alt::FileExists(lua_State* L)
	{
		std::string filePath;

		ArgumentReader argReader(L);
		argReader.ReadString(filePath);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, Core->FileExists(filePath));

		return 1;
	}

	int Alt::FileRead(lua_State* L)
	{
		std::string filePath;

		ArgumentReader argReader(L);
		argReader.ReadString(filePath);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, Core->FileRead(filePath).CStr());

		return 1;
	}

	int Alt::GetEntityByID(lua_State* L)
	{
		alt::IEntity* entity;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(entity);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, entity);

		return 1;
	}

	int Alt::GetVersion(lua_State* L)
	{
		lua_pushstring(L, Core->GetVersion());
		return 1;
	}

	int Alt::GetBranch(lua_State* L)
	{
		lua_pushstring(L, Core->GetBranch());
		return 1;
	}

	int Alt::Hash(lua_State* L)
	{
		std::string hashKey;

		ArgumentReader argReader(L);
		argReader.ReadString(hashKey);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, Core->Hash(hashKey));

		return 1;
	}

	int Alt::OnServer(lua_State* L)
	{
		std::string eventName;
		int functionRef;

		ArgumentReader argReader(L);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionRef);

		//argReader.ReadFunctionComplete();

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto runtime = &LuaScriptRuntime::Instance();
		auto resource = runtime->GetResourceImplFromState(L);
		auto resourceEventManager = resource->GetResourceEventManager();

	#ifdef ALT_SERVER_API
		lua_pushboolean(L, resourceEventManager->SubscribeLocalEvent(eventName, functionRef));
	#else
		lua_pushboolean(L, resourceEventManager->SubscribeRemoteEvent(eventName, functionRef));
	#endif

		return 1;
	}

	int Alt::OffServer(lua_State* L)
	{
		std::string eventName;
		int functionRef;

		ArgumentReader argReader(L);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionRef);
		//argReader.ReadFunctionComplete();

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto runtime = &LuaScriptRuntime::Instance();
		auto resource = runtime->GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resource->GetResourceEventManager();

	#ifdef ALT_SERVER_API
		lua_pushboolean(L, resourceEventManager->UnsubscribeLocalEvent(eventName, functionRef));
	#else
		lua_pushboolean(L, resourceEventManager->UnsubscribeRemoteEvent(eventName, functionRef));
	#endif

		return 1;
	}

	int Alt::OnClient(lua_State* L)
	{
		std::string eventName;
		int functionRef;

		unsigned int ha = 1;
		lua_pushnumber(L, ha);

		ArgumentReader argReader(L);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionRef);
		//argReader.ReadFunctionComplete();

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto runtime = &LuaScriptRuntime::Instance();
		auto resource = runtime->GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resource->GetResourceEventManager();

	#ifdef ALT_SERVER_API
		lua_pushboolean(L, resourceEventManager->SubscribeRemoteEvent(eventName, functionRef));
	#else
		lua_pushboolean(L, resourceEventManager->SubscribeLocalEvent(eventName, functionRef));
	#endif

		return 1;
	}

	int Alt::OffClient(lua_State* L)
	{
		std::string eventName;
		int functionRef;

		ArgumentReader argReader(L);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionRef);
		//argReader.ReadFunctionComplete();

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto runtime = &LuaScriptRuntime::Instance();
		auto resource = runtime->GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resource->GetResourceEventManager();

	#ifdef ALT_SERVER_API
		lua_pushboolean(L, resourceEventManager->UnsubscribeRemoteEvent(eventName, functionRef));
	#else
		lua_pushboolean(L, resourceEventManager->UnsubscribeLocalEvent(eventName, functionRef));
	#endif

		return 1;
	}

	int Alt::EmitServer(lua_State* L)
	{
		std::string eventName;
		alt::MValueArgs args;

		ArgumentReader argReader(L);
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

	int Alt::EmitClient(lua_State* L)
	{
	#ifdef ALT_SERVER_API
		alt::IPlayer* player;
	#endif
		std::string eventName;
		alt::MValueArgs args;

		ArgumentReader argReader(L);
	#ifdef ALT_SERVER_API
		if (argReader.IsCurrentType(LUA_TNIL))
		{
			player = nullptr;
			argReader.SkipValue();
		}
		else
			argReader.ReadBaseObject(player);
	#endif

		argReader.ReadString(eventName);
		argReader.ReadArguments(args);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

	#ifdef ALT_SERVER_API
		Core->TriggerClientEvent(player, eventName, args);
	#else
		Core->TriggerLocalEvent(eventName, args);
	#endif

		return 0;
	}

#ifdef ALT_SERVER_API
	int Alt::EmitClientAll(lua_State* L)
	{
		std::string eventName;
		alt::MValueArgs args;

		ArgumentReader argReader(L);
		argReader.ReadString(eventName);
		argReader.ReadArguments(args);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->TriggerClientEventForAll(eventName, args);

		return 0;
	}
#endif

	int Alt::AltIndex(lua_State* L)
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

	/*int Alt::AltIndex(lua_State* L)
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

	int Alt::dofile(lua_State* L)
	{
		std::string filePath;

		ArgumentReader argReader(L);
		argReader.ReadString(filePath);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto runtime = &LuaScriptRuntime::Instance();
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

	int Alt::inext(lua_State* L)
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

	int Alt::pairs(lua_State* L)
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

	int Alt::ipairsaux(lua_State* L)
	{
		//Core->LogInfo("Alt::ipairsaux");

		int i = luaL_checkint(L, 2);
		luaL_checktype(L, 1, LUA_TTABLE);
		i++;  /* next value */
		lua_pushinteger(L, i);
		lua_rawgeti(L, 1, i);
		//lua_stacktrace(L, "Alt::ipairsaux");

		return (lua_isnil(L, -1)) ? 0 : 2;
	}

	int Alt::ipairs(lua_State* L)
	{
		//Core->LogInfo("Alt::ipairs");
		luaL_getmetafield(L, 1, "__ipairs");
	
		if (lua_isfunction(L, -1))
		{
			lua_call(L, 0, 1);
			lua_replace(L, 1);
		}

		lua_pushvalue(L, lua_upvalueindex(1));
		lua_pushvalue(L, 1);
		lua_pushnumber(L, 0);

		//lua_stacktrace(L, "Alt::ipairs1");

		return 3;
	}

	int Alt::NextTick(lua_State* L)
	{
		int functionReference;

		ArgumentReader argReader(L);
		argReader.ReadFunction(functionReference);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl *resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in NextTick");
			return 0;
		}

		lua_pushnumber(L, resourceImpl->CreateTimer(functionReference, 0, false));

		return 1;
	}

	int Alt::EveryTick(lua_State* L)
	{
		int functionReference;

		ArgumentReader argReader(L);
		argReader.ReadFunction(functionReference);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in EveryTick");
			return 0;
		}

		lua_pushnumber(L, resourceImpl->CreateTimer(functionReference, 0, true));

		return 1;
	}

	int Alt::SetTimeout(lua_State* L)
	{
		int functionReference;
		uint32_t time;

		ArgumentReader argReader(L);
		argReader.ReadFunction(functionReference);
		argReader.ReadNumber(time);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in SetTimeout");
			return 0;
		}

		lua_pushnumber(L, resourceImpl->CreateTimer(functionReference, time, false));

		return 1;
	}

	int Alt::SetInterval(lua_State* L)
	{
		int functionReference;
		uint32_t time;

		ArgumentReader argReader(L);
		argReader.ReadFunction(functionReference);
		argReader.ReadNumber(time);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in SetInterval");
			return 0;
		}

		lua_pushnumber(L, resourceImpl->CreateTimer(functionReference, time, true));

		return 1;
	}

	int Alt::ClearTimer(lua_State* L)
	{
		uint32_t timerIndex;

		ArgumentReader argReader(L);
		argReader.ReadNumber(timerIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Unable to retrieve LuaResourceImpl in NextTick");
			return 0;
		}

		lua_pushboolean(L, resourceImpl->DestroyTimer(timerIndex));

		return 1;
	}

	int Alt::Log(lua_State* L, LogType logType)
	{
		ArgumentReader argReader(L);
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

	int Alt::LogInfo(lua_State* L)
	{
		return Alt::Log(L, LogType::LOG_COLORED);
	}

	int Alt::LogDebug(lua_State* L)
	{
		return Alt::Log(L, LogType::LOG_DEBUG);
	}

	int Alt::LogWarning(lua_State* L)
	{
		return Alt::Log(L, LogType::LOG_WARNING);
	}

	int Alt::LogError(lua_State* L)
	{
		return Alt::Log(L, LogType::LOG_ERROR);
	}

	int Alt::LogColored(lua_State* L)
	{
		return Alt::Log(L, LogType::LOG_COLORED);
	}
}

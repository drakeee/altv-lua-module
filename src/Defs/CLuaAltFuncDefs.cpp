#include <Main.h>

const char* CLuaAltFuncDefs::ClassName = "alt";
void CLuaAltFuncDefs::Init(lua_State* L)
{
	//lua_newtable(L);

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

	lua_globalfunction(L, "onServer", OnServer);
	lua_globalfunction(L, "offServer", OffServer);

	lua_globalfunction(L, "emitServer", EmitServer);

	lua_globalfunction(L, "export", Export);

	lua_beginclass(L, ClassName);
	{
		lua_classmeta(L, "__index", AltIndex, true);
	}
	lua_endclass(L);

	/*lua_pushstring(L, "logInfo");
	lua_pushcfunction(L, CLuaAltFuncDefs::LogInfo);
	lua_settable(L, -3);

	lua_pushstring(L, "logDebug");
	lua_pushcfunction(L, &CLuaAltFuncDefs::LogDebug);
	lua_settable(L, -3);

	lua_pushstring(L, "logWarning");
	lua_pushcfunction(L, &CLuaAltFuncDefs::LogWarning);
	lua_settable(L, -3);

	lua_pushstring(L, "logError");
	lua_pushcfunction(L, &CLuaAltFuncDefs::LogError);
	lua_settable(L, -3);

	lua_pushstring(L, "logColored");
	lua_pushcfunction(L, &CLuaAltFuncDefs::LogColored);
	lua_settable(L, -3);

	lua_setglobal(L, "alt");*/

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

	lua_pop(L, 1);
}

int CLuaAltFuncDefs::Export(lua_State* L)
{
	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceFromState(L);

	std::string exportName;
	int functionRef;

	CArgReader argReader(L);
	argReader.ReadString(exportName);
	argReader.ReadFunction(functionRef);

	if (resource->IsExportExists(exportName))
	{
		Core->LogError("Warning: Export \"" + exportName + "\" already exists. It will be overwritten by the new function.");
	}

	resource->AddExport(exportName, new CLuaResourceImpl::LuaFunction(resource, functionRef));

	return 0;
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
	auto resource = runtime->GetResourceFromState(L);

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
	auto resource = runtime->GetResourceFromState(L);

	lua_pushboolean(L, resource->RemoveEvent(eventName, functionRef));

	return 1;
}

int CLuaAltFuncDefs::EmitServer(lua_State* L)
{
	std::string eventName;
	alt::MValueArgs args;

	CArgReader argReader(L);
	argReader.ReadString(eventName);
	argReader.ReadArguments(args);
	//argReader.ReadFunctionComplete();

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceFromState(L);

	Core->TriggerLocalEvent(eventName, args);

	return 0;
}

int CLuaAltFuncDefs::AltIndex(lua_State* L)
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
	std::string message;

	CArgReader argReader(L);
	argReader.ReadString(message);

	//lua_getglobal(L, "_print");

	//lua_stacktrace(L, "Log");

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	switch (logType)
	{
	case LogType::LOG_COLORED:
		Core->LogColored(message);
		break;

	case LogType::LOG_DEBUG:
		Core->LogDebug(message);
		break;

	case LogType::LOG_ERROR:
		Core->LogError(message);
		break;

	case LogType::LOG_INFO:
		Core->LogInfo(message);
		break;

	case LogType::LOG_WARNING:
		Core->LogWarning(message);
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
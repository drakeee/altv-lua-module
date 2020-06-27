#include "Main.h"

void CLuaAltFuncDefs::init(lua_State* L)
{
	lua_newtable(L);

	lua_pushstring(L, "logInfo");
	lua_pushcfunction(L, &CLuaAltFuncDefs::logInfo);
	lua_settable(L, -3);

	lua_pushstring(L, "logDebug");
	lua_pushcfunction(L, &CLuaAltFuncDefs::logDebug);
	lua_settable(L, -3);

	lua_pushstring(L, "logWarning");
	lua_pushcfunction(L, &CLuaAltFuncDefs::logWarning);
	lua_settable(L, -3);

	lua_pushstring(L, "logError");
	lua_pushcfunction(L, &CLuaAltFuncDefs::logError);
	lua_settable(L, -3);

	lua_pushstring(L, "logColored");
	lua_pushcfunction(L, &CLuaAltFuncDefs::logColored);
	lua_settable(L, -3);

	lua_setglobal(L, "alt");

	lua_stacktrace(L, "CLuaAltFuncDefs::init");
}

int CLuaAltFuncDefs::log(lua_State* L, LogType logType)
{
	std::string message;

	CArgReader argReader(L);
	argReader.ReadString(message);

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

int CLuaAltFuncDefs::logInfo(lua_State* L)
{
	return CLuaAltFuncDefs::log(L, LogType::LOG_INFO);
}

int CLuaAltFuncDefs::logDebug(lua_State* L)
{
	return CLuaAltFuncDefs::log(L, LogType::LOG_DEBUG);
}

int CLuaAltFuncDefs::logWarning(lua_State* L)
{
	return CLuaAltFuncDefs::log(L, LogType::LOG_WARNING);
}

int CLuaAltFuncDefs::logError(lua_State* L)
{
	return CLuaAltFuncDefs::log(L, LogType::LOG_ERROR);
}

int CLuaAltFuncDefs::logColored(lua_State* L)
{
	return CLuaAltFuncDefs::log(L, LogType::LOG_COLORED);
}
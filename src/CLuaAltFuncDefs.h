#pragma once

#include "Main.h"

class CLuaAltFuncDefs
{
public:
	enum class LogType
	{
		LOG_INFO = 0,
		LOG_DEBUG,
		LOG_WARNING,
		LOG_ERROR,
		LOG_COLORED
	};

public:
	static void init(lua_State* L);

private:
	static int log(lua_State* L, LogType logtype = LogType::LOG_INFO);
	static int logInfo(lua_State* L);
	static int logDebug(lua_State* L);
	static int logWarning(lua_State* L);
	static int logError(lua_State* L);
	static int logColored(lua_State* L);
};
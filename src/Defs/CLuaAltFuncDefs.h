#pragma once

#include <Main.h>

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
	static void Init(lua_State* L);

private:
	static int inext(lua_State* L);
	static int pairs(lua_State* L);
	static int ipairs(lua_State* L);
	static int ipairsaux(lua_State* L);

	static int Log(lua_State* L, LogType logtype = LogType::LOG_INFO);
	static int LogInfo(lua_State* L);
	static int LogDebug(lua_State* L);
	static int LogWarning(lua_State* L);
	static int LogError(lua_State* L);
	static int LogColored(lua_State* L);

	static int tostringtest(lua_State* L);
};
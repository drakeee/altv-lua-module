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
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int AltIndex(lua_State* L);

	static int dofile(lua_State* L);
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

	static int SetMetaData(lua_State* L);
	static int GetMetaData(lua_State* L);
	static int DeleteMetaData(lua_State* L);
	static int HasMetaData(lua_State* L);
	static int GetSyncedMetaData(lua_State* L);
	static int HasSyncedMetaData(lua_State* L);

	static int GetRequiredPermissions(lua_State* L);
	static int GetOptionalPermissions(lua_State* L);

	static int OnServer(lua_State* L);
	static int OffServer(lua_State* L);
	static int OnClient(lua_State* L);
	static int OffClient(lua_State* L);

	static int EmitServer(lua_State* L);

	static int Export(lua_State* L);

	static int IsDebug(lua_State* L);
	static int FileExists(lua_State* L);
	static int FileRead(lua_State* L);
	static int GetEntityByID(lua_State* L);
	static int GetVersion(lua_State* L);
	static int GetBranch(lua_State* L);

	static int Hash(lua_State* L);

#ifdef ALT_SERVER_API
	static int GetRootDirectory(lua_State* L);

	static int StartResource(lua_State* L);
	static int StopResource(lua_State* L);
	static int RestartResource(lua_State* L);

	static int EmitClient(lua_State* L);

	static int SetSyncedMetaData(lua_State* L);
	static int DeleteSyncedMetaData(lua_State* L);

	static int GetPlayersByName(lua_State* L);

	static int GetNetTime(lua_State* L);
#endif

	static int tostringtest(lua_State* L);
};
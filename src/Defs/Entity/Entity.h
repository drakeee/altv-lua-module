#pragma once

#include <Main.h>

namespace lua::Class
{
	class Entity
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int tostring(lua_State* L);
		static int pairs(lua_State* L);
		static int ipairs(lua_State* L);

		static int GetID(lua_State* L);

		static int GetNetworkOwner(lua_State* L);

		static int GetModel(lua_State* L);

		//static int SetPosition(lua_State* L);
		//static int GetPosition(lua_State* L);
		static int SetRotation(lua_State* L);
		static int GetRotation(lua_State* L);

		static int GetVisible(lua_State* L);

		static int HasSyncedMetaData(lua_State* L);
		static int GetSyncedMetaData(lua_State* L);
		static int HasStreamSyncedMetaData(lua_State* L);
		static int GetStreamSyncedMetaData(lua_State* L);

#ifdef ALT_SERVER_API
		static int SetNetworkOwner(lua_State* L);

		static int SetSyncedMetaData(lua_State* L);
		static int DeleteSyncedMetaData(lua_State* L);
		static int SetStreamSyncedMetaData(lua_State* L);
		static int DeleteStreamSyncedMetaData(lua_State* L);
		static int SetVisible(lua_State* L);
#else
		static int GetScriptGuid(lua_State* L);
		static int GetEntityByScriptGuid(lua_State* L);
#endif
	};
}
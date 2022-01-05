#pragma once

#ifdef ALT_CLIENT_API
#include <Main.h>

namespace lua::Class
{
	class WebSocket
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int On(lua_State* L);
		static int Off(lua_State* L);

		static int Start(lua_State* L);
		static int Send(lua_State* L);
		static int Stop(lua_State* L);

		static int AddSubProtocol(lua_State* L);
		static int GetSubProtocols(lua_State* L);

		static int SetExtraHeader(lua_State* L);
		static int GetExtraHeaders(lua_State* L);

		static int SetAutoReconnect(lua_State* L);
		static int GetAutoReconnect(lua_State* L);
		static int SetPerMessageDeflate(lua_State* L);
		static int GetPerMessageDeflate(lua_State* L);
		static int SetPingInterval(lua_State* L);
		static int GetPingInterval(lua_State* L);
		static int SetURL(lua_State* L);
		static int GetURL(lua_State* L);
		static int GetReadyState(lua_State* L);
	};
}
#endif
#include <Main.h>

#ifdef ALT_CLIENT_API
const char* CLuaWebSocketDefs::ClassName = "WebSocketClient";
void CLuaWebSocketDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaWebSocketDefs::Init");

	lua_beginclass(L, CLuaWebSocketDefs::ClassName, CLuaBaseObjectDefs::ClassName);
	{
		lua_classfunction(L, "on", On);
		lua_classfunction(L, "off", Off);

		lua_classfunction(L, "start", Start);
		lua_classfunction(L, "send", Send);
		lua_classfunction(L, "stop", Stop);

		lua_classfunction(L, "addSubProtocol", AddSubProtocol);
		lua_classfunction(L, "getSubProtocols", GetSubProtocols);

		lua_classfunction(L, "setExtraHeader", SetExtraHeader);
		lua_classfunction(L, "getExtraHeaders", GetExtraHeaders);

		lua_classfunction(L, "setAutoReconnect", SetAutoReconnect);
		lua_classfunction(L, "setPerMessageDeflate", SetPerMessageDeflate);
		lua_classfunction(L, "setPingInterval", SetPingInterval);
		lua_classfunction(L, "setURL", SetURL);
		lua_classfunction(L, "getAutoReconnect", GetAutoReconnect);
		lua_classfunction(L, "getPerMessageDeflate", GetPerMessageDeflate);
		lua_classfunction(L, "getPingInterval", GetPingInterval);
		lua_classfunction(L, "getURL", GetURL);
		lua_classfunction(L, "getReadyState", GetReadyState);

		lua_classvariable(L, "autoReconnect", SetAutoReconnect, GetAutoReconnect);
		lua_classvariable(L, "perMessageDeflate", SetPerMessageDeflate, GetPerMessageDeflate);
		lua_classvariable(L, "pingInterval", SetPingInterval, GetPingInterval);
		lua_classvariable(L, "url", SetURL, GetURL);
		lua_classvariable(L, "readyState", nullptr, GetReadyState);
	}
	lua_endclass(L);

	DEBUG_INFO("CLuaWebSocketDefs::Init ...done");
}

int CLuaWebSocketDefs::On(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	std::string eventName;
	int functionIndex;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadString(eventName);
	argReader.ReadFunction(functionIndex);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
	if (resourceImpl == nullptr)
	{
		Core->LogError("Unable to retrieve resource in WebSocket::On");
		return 0;
	}

	lua_pushboolean(L, resourceImpl->RegisterWebSocketEvent(webSocket, eventName, functionIndex));

	return 1;
}

int CLuaWebSocketDefs::Off(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	std::string eventName;
	int functionIndex;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadString(eventName);
	argReader.ReadFunction(functionIndex);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
	if (resourceImpl == nullptr)
	{
		Core->LogError("Unable to retrieve resource in WebSocket::On");
		return 0;
	}

	lua_pushboolean(L, resourceImpl->RemoveWebSocketEvent(webSocket, eventName, functionIndex));

	return 1;
}

int CLuaWebSocketDefs::Start(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->Start();

	return 0;
}

int CLuaWebSocketDefs::Send(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	std::string message;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadString(message);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webSocket->Send(message));

	return 1;
}

int CLuaWebSocketDefs::Stop(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->Stop();

	return 0;
}

int CLuaWebSocketDefs::AddSubProtocol(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	std::string protocol;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadString(protocol);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->AddSubProtocol(protocol);

	return 0;
}

int CLuaWebSocketDefs::GetSubProtocols(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto& allProtocols = webSocket->GetSubProtocols();

	lua_newtable(L);
	for (size_t i = 0; i < allProtocols.GetSize(); i++)
	{
		lua_pushnumber(L, (int)(i + 1));
		lua_pushstring(L, allProtocols[i].CStr());
		lua_rawset(L, -3);
	}

	return 1;
}

int CLuaWebSocketDefs::SetExtraHeader(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	std::string name;
	std::string value;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadString(name);
	argReader.ReadString(value);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->SetExtraHeader(name, value);

	return 0;
}

int CLuaWebSocketDefs::GetExtraHeaders(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto& allHeaders = webSocket->GetExtraHeaders();
	lua_pushmvalue(L, allHeaders);

	return 1;
}

int CLuaWebSocketDefs::SetAutoReconnect(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	bool toggle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadBool(toggle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->SetAutoReconnectEnabled(toggle);

	return 0;
}

int CLuaWebSocketDefs::GetAutoReconnect(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webSocket->IsAutoReconnectEnabled());
	return 1;
}

int CLuaWebSocketDefs::SetPerMessageDeflate(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	bool toggle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadBool(toggle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->SetPerMessageDeflateEnabled(toggle);

	return 0;
}

int CLuaWebSocketDefs::GetPerMessageDeflate(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webSocket->IsPerMessageDeflateEnabled());

	return 1;
}

int CLuaWebSocketDefs::SetPingInterval(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	uint16_t seconds;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadNumber(seconds);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->SetPingInterval(seconds);

	return 0;
}

int CLuaWebSocketDefs::GetPingInterval(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, webSocket->GetPingInterval());

	return 1;
}

int CLuaWebSocketDefs::SetURL(lua_State* L)
{
	alt::IWebSocketClient* webSocket;
	std::string url;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);
	argReader.ReadString(url);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webSocket->SetUrl(url);

	return 0;
}

int CLuaWebSocketDefs::GetURL(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, webSocket->GetUrl());

	return 1;
}

int CLuaWebSocketDefs::GetReadyState(lua_State* L)
{
	alt::IWebSocketClient* webSocket;

	CArgReader argReader(L);
	argReader.ReadBaseObject(webSocket);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, webSocket->GetReadyState());

	return 1;
}
#endif
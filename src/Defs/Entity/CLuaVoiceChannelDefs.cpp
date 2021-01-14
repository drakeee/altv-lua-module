#include <Main.h>

#ifdef ALT_SERVER_API
const char* CLuaVoiceChannelDefs::ClassName = "VoiceChannel";
void CLuaVoiceChannelDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaVoiceChannelDefs::Init");

	lua_globalfunction(L, "createVoiceChannel", Create);
	lua_globalfunction(L, "isVoiceChannelSpatial", IsSpatial);
	lua_globalfunction(L, "getVoiceChannelMaxDistance", GetMaxDistance);
	lua_globalfunction(L, "isPlayerInVoiceChannel", HasPlayer);
	lua_globalfunction(L, "addPlayerToVoiceChannel", AddPlayer);
	lua_globalfunction(L, "removePlayerFromVoiceChannel", RemovePlayer);
	lua_globalfunction(L, "isPlayerMutedInVoiceChannel", IsPlayerMuted);
	lua_globalfunction(L, "mutePlayerInVoiceChannel", MutePlayer);
	lua_globalfunction(L, "unmutePlayerInVoiceChannel", UnmutePlayer);

	lua_beginclass(L, ClassName, CLuaWorldObjectDefs::ClassName);
	{
		lua_classfunction(L, "new", Create);
		lua_classfunction(L, "isSpatial", IsSpatial);
		lua_classfunction(L, "getMaxDistance", GetMaxDistance);
		lua_classfunction(L, "hasPlayer", HasPlayer);
		lua_classfunction(L, "addPlayer", AddPlayer);
		lua_classfunction(L, "removePlayer", RemovePlayer);
		lua_classfunction(L, "isPlayerMuted", IsPlayerMuted);
		lua_classfunction(L, "mutePlayer", MutePlayer);
		lua_classfunction(L, "unmutePlayer", UnmutePlayer);

		lua_classvariable(L, "spatial", nullptr, "isSpatial");
		lua_classvariable(L, "maxDistance", nullptr, "getMaxDistance");
	}
	lua_endclass(L);

	DEBUG_INFO("CLuaVoiceChannelDefs::Init ...done");
}

int CLuaVoiceChannelDefs::Create(lua_State* L)
{
	bool spatial;
	float maxDistance;

	CArgReader argReader(L);
	argReader.ReadBool(spatial);
	argReader.ReadNumber(maxDistance);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto voiceChannel = Core->CreateVoiceChannel(spatial, maxDistance);
	if (voiceChannel)
	{
		lua_pushbaseobject(L, voiceChannel.Get());

		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(voiceChannel.Get());
	}
	else
		lua_pushnil(L);

	return 1;
}

int CLuaVoiceChannelDefs::IsSpatial(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, voiceChannel->IsSpatial());

	return 1;
}

int CLuaVoiceChannelDefs::GetMaxDistance(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, voiceChannel->GetMaxDistance());

	return 1;
}

int CLuaVoiceChannelDefs::HasPlayer(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, voiceChannel->HasPlayer(player));

	return 1;
}

int CLuaVoiceChannelDefs::AddPlayer(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	voiceChannel->AddPlayer(player);

	return 0;
}

int CLuaVoiceChannelDefs::RemovePlayer(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	voiceChannel->RemovePlayer(player);

	return 0;
}

int CLuaVoiceChannelDefs::IsPlayerMuted(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, voiceChannel->IsPlayerMuted(player));

	return 1;
}

int CLuaVoiceChannelDefs::MutePlayer(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	voiceChannel->MutePlayer(player);

	return 0;
}

int CLuaVoiceChannelDefs::UnmutePlayer(lua_State* L)
{
	alt::IVoiceChannel* voiceChannel;
	alt::IPlayer* player;

	CArgReader argReader(L);
	argReader.ReadBaseObject(voiceChannel);
	argReader.ReadBaseObject(player);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	voiceChannel->UnmutePlayer(player);

	return 0;
}
#endif
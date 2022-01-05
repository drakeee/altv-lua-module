#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
	const char* Voice::ClassName = "Voice";
	void Voice::Init(lua_State* L)
	{
		DEBUG_INFO("Voice::Init");

		lua_globalfunction(L, "setVoiceInputMuted", SetVoiceInputMuted);
		lua_globalfunction(L, "isVoiceInputMuted", IsVoiceInputMuted);
		lua_globalfunction(L, "isVoiceActivationEnabled", IsVoiceActivationEnabled);
		lua_globalfunction(L, "toggleVoiceControls", ToggleVoiceControls);

		lua_beginclass(L, Voice::ClassName);
		{
			lua_classfunction(L, "toggleControls", ToggleVoiceControls);

			lua_classvariable(L, "muteInput", SetVoiceInputMuted, IsVoiceInputMuted);
			lua_classvariable(L, "activityInputEnabled", nullptr, IsVoiceActivationEnabled);
			//lua_classvariable(L, "activationKey", nullptr, GetVoiceActivationKey);
		}
		lua_endclass(L);

		DEBUG_INFO("Voice::Init ...done");
	}

	int Voice::SetVoiceInputMuted(lua_State* L)
	{
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->SetVoiceInputMuted(state);

		return 0;
	}

	int Voice::IsVoiceInputMuted(lua_State* L)
	{
		lua_pushboolean(L, Core->IsVoiceInputMuted());

		return 1;
	}

	int Voice::IsVoiceActivationEnabled(lua_State* L)
	{
		lua_pushboolean(L, Core->IsVoiceActivationEnabled());

		return 1;
	}

	//int Voice::GetVoiceActivationKey(lua_State* L)
	//{
	//	lua_pushboolean(L, Core->GetVoiceActivationKey());
	//
	//	return 1;
	//}

	int Voice::ToggleVoiceControls(lua_State* L)
	{
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->ToggleVoiceControls(state);

		return 0;
	}
}
#endif
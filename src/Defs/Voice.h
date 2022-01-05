#pragma once

#include <Main.h>

namespace lua::Class
{
	class Voice
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);
	private:
		static int SetVoiceInputMuted(lua_State* L);
		static int IsVoiceInputMuted(lua_State* L);
		static int IsVoiceActivationEnabled(lua_State* L);
		static int ToggleVoiceControls(lua_State* L);
		//static int GetVoiceActivationKey(lua_State* L);
	};
}
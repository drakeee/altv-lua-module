#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API

namespace lua::Class
{
	class Audio
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
        static int CreateAudio(lua_State* L);
        static int On(lua_State* L);
        static int Off(lua_State* L);

        static int SetSource(lua_State* L); //data/file/url
        static int GetSource(lua_State* L);

        static int SetLoop(lua_State* L);
        static int SetVolume(lua_State* L);  //0.0 - 1.0 range
        static int SetCategory(lua_State* L); //default: radio

        static int IsLoop(lua_State* L);
        static int GetVolume(lua_State* L);
        static int GetCategory(lua_State* L);

        static int IsFrontendPlay(lua_State* L);

        static int AddOutput(lua_State* L);
        static int RemoveOutput(lua_State* L);
        static int GetOutputs(lua_State* L);

        static int Play(lua_State* L);
        static int Pause(lua_State* L);
        static int Reset(lua_State* L);
        static int GetCurrentTime(lua_State* L); //seconds
        static int GetMaxTime(lua_State* L); //seconds
        static int Seek(lua_State* L); //seconds
        static int IsPlaying(lua_State* L);
	};
}

#endif
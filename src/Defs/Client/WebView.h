#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
    class WebView
    {
    public:
	    static const char* ClassName;
	    static void Init(lua_State* L);

    private:
        static int tostring(lua_State* L);

        static int CreateWebView(lua_State* L);
        static int On(lua_State* L);
        static int Off(lua_State* L);
        static int Trigger(lua_State* L);
        static int Focus(lua_State* L);
        static int Unfocus(lua_State* L);
        static int IsFocused(lua_State* L);
        static int GetUrl(lua_State* L);
        static int SetUrl(lua_State* L);
        static int IsVisible(lua_State* L);
        static int SetVisible(lua_State* L);
        static int IsOverlay(lua_State* L);
        static int IsReady(lua_State* L);
        static int SetExtraHeader(lua_State* L);
        static int SetZoomLevel(lua_State* L);
        static int GetSize(lua_State* L);
        static int SetSize(lua_State* L);
        static int GetPosition(lua_State* L);
        static int SetPosition(lua_State* L);
    };
}
#endif
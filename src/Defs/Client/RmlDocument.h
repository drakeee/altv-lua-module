#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API

namespace lua::Class
{
    class RmlDocument
    {
    public:
        static const char* ClassName;
        static void Init(lua_State* L);

    private:
        static int tostring(lua_State* L);

        static int CreateRmlDocument(lua_State* L);

        static int SetTitle(lua_State* L);
        static int GetTitle(lua_State* L);
        static int GetSourceUrl(lua_State* L);

        static int CreateElement(lua_State* L);
        static int CreateTextNode(lua_State* L);

        static int Hide(lua_State* L);
        static int Show(lua_State* L);
        static int IsVisible(lua_State* L);
        static int IsModal(lua_State* L);

        static int GetBody(lua_State* L);

        static int Update(lua_State* L);
    };
}

#endif
#pragma once

#include <Main.h>

class CLuaMapDataDefs
{
public:
    static const char* ClassName;
    static void Init(lua_State* L);

private:
    static int GetZoomScale(lua_State* L);
    static int GetZoomSpeed(lua_State* L);
    static int GetScrollSpeed(lua_State* L);
    static int GetTilesCountX(lua_State* L);
    static int GetTilesCountY(lua_State* L);

    static int SetZoomScale(lua_State* L);
    static int SetZoomSpeed(lua_State* L);
    static int SetScrollSpeed(lua_State* L);
    static int SetTilesCountX(lua_State* L);
    static int SetTilesCountY(lua_State* L);
};
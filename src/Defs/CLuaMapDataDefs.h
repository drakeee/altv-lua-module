#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API
class CLuaMapDataDefs
{
public:
    static const char* ClassName;
    static void Init(lua_State* L);

private:
    static int CreateMapZoom(lua_State* L);

    static int Get(lua_State* L);
    static int Reset(lua_State* L);
    static int ResetAll(lua_State* L);

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
#endif
#include <Main.h>

const char* CLuaMapDataDefs::ClassName = "MapData";
void CLuaMapDataDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "getMapDataZoomScale", GetZoomScale);
	lua_globalfunction(L, "getMapDataZoomSpeed", GetZoomSpeed);
	lua_globalfunction(L, "getMapDataScrollSpeed", GetScrollSpeed);
	lua_globalfunction(L, "getMapDataTilesCountX", GetTilesCountX);
	lua_globalfunction(L, "getMapDataTilesCountY", GetTilesCountY);

	lua_globalfunction(L, "setMapDataZoomScale", SetZoomScale);
	lua_globalfunction(L, "setMapDataZoomSpeed", SetZoomSpeed);
	lua_globalfunction(L, "setMapDataScrollSpeed", SetScrollSpeed);
	lua_globalfunction(L, "setMapDataTilesCountX", SetTilesCountX);
	lua_globalfunction(L, "setMapDataTilesCountY", SetTilesCountY);

	lua_beginclass(L, CLuaMapDataDefs::ClassName);
	{
		lua_classfunction(L, "getZoomScale", GetZoomScale);
		lua_classfunction(L, "getZoomSpeed", GetZoomSpeed);
		lua_classfunction(L, "getScrollSpeed", GetScrollSpeed);
		lua_classfunction(L, "getTilesCountX", GetTilesCountX);
		lua_classfunction(L, "getTilesCountY", GetTilesCountY);

		lua_classfunction(L, "setZoomScale", SetZoomScale);
		lua_classfunction(L, "setZoomSpeed", SetZoomSpeed);
		lua_classfunction(L, "setScrollSpeed", SetScrollSpeed);
		lua_classfunction(L, "setTilesCountX", SetTilesCountX);
		lua_classfunction(L, "setTilesCountY", SetTilesCountY);

		lua_classvariable(L, "zoomScale", "setZoomScale", "getZoomScale");
		lua_classvariable(L, "zoomSpeed", "setZoomSpeed", "getZoomSpeed");
		lua_classvariable(L, "scrollSpeed", "setScrollSpeed", "getScrollSpeed");
		lua_classvariable(L, "tilesCountX", "setTilesCountX", "getTilesCountX");
		lua_classvariable(L, "tilesCountY", "setTilesCountY", "getTilesCountY");
	}
	lua_endclass(L);
}

#define MAPDATA_GET_DEFINE(GET) \
int CLuaMapDataDefs::GET(lua_State* L) { alt::IMapData* mapData; CArgReader argReader(L); argReader.ReadUserData(mapData); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } lua_pushnumber(L, mapData->GET()); return 1;}

#define MAPDATA_SET_DEFINE(SET) \
int CLuaMapDataDefs::SET(lua_State* L) { alt::IMapData* mapData; float value; CArgReader argReader(L); argReader.ReadUserData(mapData); argReader.ReadNumber(value); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } mapData->SET(value); return 0;}

MAPDATA_GET_DEFINE(GetZoomScale)
MAPDATA_GET_DEFINE(GetZoomSpeed)
MAPDATA_GET_DEFINE(GetScrollSpeed)
MAPDATA_GET_DEFINE(GetTilesCountX)
MAPDATA_GET_DEFINE(GetTilesCountY)

MAPDATA_SET_DEFINE(SetZoomScale)
MAPDATA_SET_DEFINE(SetZoomSpeed)
MAPDATA_SET_DEFINE(SetScrollSpeed)
MAPDATA_SET_DEFINE(SetTilesCountX)
MAPDATA_SET_DEFINE(SetTilesCountY)

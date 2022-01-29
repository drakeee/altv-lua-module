#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
	const char* MapData::ClassName = "MapZoomData";
	void MapData::Init(lua_State* L)
	{
		DEBUG_INFO("MapData::Init");

		lua_beginclass(L, MapData::ClassName);
		{
			lua_classfunction(L, "get", Get);
			lua_classfunction(L, "reset", Reset);
			lua_classfunction(L, "resetAll", ResetAll);

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

			lua_classvariable(L, "zoomScale", SetZoomScale, GetZoomScale);
			lua_classvariable(L, "zoomSpeed", SetZoomSpeed, GetZoomSpeed);
			lua_classvariable(L, "scrollSpeed", SetScrollSpeed, GetScrollSpeed);
			lua_classvariable(L, "tilesCountX", SetTilesCountX, GetTilesCountX);
			lua_classvariable(L, "tilesCountY", SetTilesCountY, GetTilesCountY);

			//JS alias
			lua_classvariable(L, "fZoomScale", SetZoomScale, GetZoomScale);
			lua_classvariable(L, "fZoomSpeed", SetZoomSpeed, GetZoomSpeed);
			lua_classvariable(L, "fScrollSpeed", SetScrollSpeed, GetScrollSpeed);
			lua_classvariable(L, "vTilesX", SetTilesCountX, GetTilesCountX);
			lua_classvariable(L, "vTilesY", SetTilesCountY, GetTilesCountY);
		}
		lua_endclass(L);

		DEBUG_INFO("MapData::Init ...done");
	}

	int MapData::CreateMapZoom(lua_State* L)
	{
		ArgumentReader argReader(L);

		if (argReader.IsCurrentType(LUA_TNUMBER))
		{
			uint8_t zoomDataId;
			argReader.ReadNumber(zoomDataId);

			auto data = Core->GetMapData(zoomDataId);
			L_ASSERT(data, "zoomData with this id not found");

			lua_pushmapdata(L, data);
		}
		else
		{
			std::string zoomDataAlias;
			argReader.ReadString(zoomDataAlias);

			auto data = Core->GetMapData(zoomDataAlias);
			L_ASSERT(data, "zoomData with this id not found");

			uint8_t id = Core->GetMapDataIDFromAlias(zoomDataAlias);
			lua_pushnumber(L, id);
		}

		return 1;
	}

	int MapData::Get(lua_State* L)
	{
		ArgumentReader argReader(L);

		L_ASSERT(argReader.IsCurrentType(LUA_TNUMBER) || argReader.IsCurrentType(LUA_TSTRING), "zoomDataId must be a number or string");

		return CreateMapZoom(L);
	}

	int MapData::Reset(lua_State* L)
	{
		uint8_t zoomDataId;

		ArgumentReader argReader(L);
		argReader.ReadNumber(zoomDataId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		Core->ResetMapData(zoomDataId);

		return 0;
	}

	int MapData::ResetAll(lua_State* L)
	{
		Core->ResetAllMapData();
		return 0;
	}

#define MAPDATA_GET_DEFINE(GET) \
int MapData::GET(lua_State* L) { alt::IMapData* mapData; ArgumentReader argReader(L); argReader.ReadUserData(mapData); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } lua_pushnumber(L, mapData->GET()); return 1;}

#define MAPDATA_SET_DEFINE(SET) \
int MapData::SET(lua_State* L) { alt::IMapData* mapData; float value; ArgumentReader argReader(L); argReader.ReadUserData(mapData); argReader.ReadNumber(value); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } mapData->SET(value); return 0;}

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
}
#endif
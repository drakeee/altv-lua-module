#pragma once

#include <Main.h>

class CLuaBlipDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
#ifdef ALT_SERVER_API
	static int Create(lua_State* L);
	static int CreateAttached(lua_State* L);
#else
	static int CreateAreaBlip(lua_State* L);
	static int CreateRadiusBlip(lua_State* L);
	static int CreatePointBlip(lua_State* L);
	static int CreatePedBlip(lua_State* L);
	static int CreateVehicleBlip(lua_State* L);
#endif

	static int IsGlobal(lua_State* L);
	static int GetTarget(lua_State* L);

	static int IsAttached(lua_State* L);
	static int AttachedTo(lua_State* L);
	static int GetBlipType(lua_State* L);

#ifdef ALT_CLIENT_API
	static int GetScaleXY(lua_State* L);
	static int GetDisplay(lua_State* L);
	static int GetSprite(lua_State* L);
	static int GetColor(lua_State* L);
	static int GetSecondaryColor(lua_State* L);
	static int GetAlpha(lua_State* L);
	static int GetFlashTimer(lua_State* L);
	static int GetFlashInterval(lua_State* L);
	static int GetAsFriendly(lua_State* L);
	static int GetRoute(lua_State* L);
	static int GetBright(lua_State* L);
	static int GetNumber(lua_State* L);
	static int GetShowCone(lua_State* L);
	static int GetFlashes(lua_State* L);
	static int GetFlashesAlternate(lua_State* L);
	static int GetAsShortRange(lua_State* L);
	static int GetPriority(lua_State* L);
	static int GetRotation(lua_State* L);
	static int GetGxtName(lua_State* L);
	static int GetName(lua_State* L);
	static int GetRouteColor(lua_State* L);
	static int GetPulse(lua_State* L);
	static int GetAsMissionCreator(lua_State* L);
	static int GetTickVisible(lua_State* L);
	static int GetHeadingIndicatorVisible(lua_State* L);
	static int GetOutlineIndicatorVisible(lua_State* L);
	static int GetFriendIndicatorVisible(lua_State* L);
	static int GetCrewIndicatorVisible(lua_State* L);
	static int GetCategory(lua_State* L);
	static int GetAsHighDetail(lua_State* L);
	static int GetShrinked(lua_State* L);

	static int SetDisplay(lua_State* L);
	static int SetScaleXY(lua_State* L);
	static int SetSprite(lua_State* L);
	static int SetColor(lua_State* L);
	static int SetRoute(lua_State* L);
	static int SetRouteColor(lua_State* L);
	static int SetSecondaryColor(lua_State* L);
	static int SetAlpha(lua_State* L);
	static int SetFlashTimer(lua_State* L);
	static int SetFlashInterval(lua_State* L);
	static int SetAsFriendly(lua_State* L);
	static int SetBright(lua_State* L);
	static int SetNumber(lua_State* L);
	static int SetShowCone(lua_State* L);
	static int SetFlashes(lua_State* L);
	static int SetFlashesAlternate(lua_State* L);
	static int SetAsShortRange(lua_State* L);
	static int SetPriority(lua_State* L);
	static int SetRotation(lua_State* L);
	static int SetGxtName(lua_State* L);
	static int SetName(lua_State* L);
	static int SetPulse(lua_State* L);
	static int SetAsMissionCreator(lua_State* L);
	static int SetTickVisible(lua_State* L);
	static int SetHeadingIndicatorVisible(lua_State* L);
	static int SetOutlineIndicatorVisible(lua_State* L);
	static int SetFriendIndicatorVisible(lua_State* L);
	static int SetCrewIndicatorVisible(lua_State* L);
	static int SetCategory(lua_State* L);
	static int SetAsHighDetail(lua_State* L);
	static int SetShrinked(lua_State* L);
	static int Fade(lua_State* L);
#endif

	/*static int SetSprite(lua_State* L);
	static int SetColor(lua_State* L);
	static int SetRoute(lua_State* L);
	static int SetRouteColor(lua_State* L);*/
};
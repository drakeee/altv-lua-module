#include <Main.h>

const char* CLuaBlipDefs::ClassName = "Blip";
void CLuaBlipDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "createBlip", Create);
	lua_globalfunction(L, "createBlipAttached", CreateAttached);
	lua_globalfunction(L, "isBlipGlobal", IsGlobal);
	lua_globalfunction(L, "getBlipTarget", GetTarget);
	lua_globalfunction(L, "isBlipAttached", IsAttached);
	lua_globalfunction(L, "getBlipAttachedTo", AttachedTo);
	lua_globalfunction(L, "getBlipType", GetBlipType);
	/*lua_globalfunction(L, "setBlipSprite", SetSprite);
	lua_globalfunction(L, "setBlipColor", SetColor);
	lua_globalfunction(L, "setBlipRoute", SetRoute);
	lua_globalfunction(L, "setBlipRouteColor", SetRouteColor);*/

	lua_beginclass(L, ClassName, CLuaWorldObjectDefs::ClassName);
	{
		lua_classfunction(L, "new", Create);
		lua_classfunction(L, "isGlobal", IsGlobal);
		lua_classfunction(L, "getTarget", GetTarget);
		lua_classfunction(L, "isAttached", IsAttached);
		lua_classfunction(L, "getAttachedTo", AttachedTo);
		lua_classfunction(L, "getBlipType", GetBlipType);

#ifdef ALT_CLIENT_API
		lua_classfunction(L, "getScaleXY", GetScaleXY);
		lua_classfunction(L, "getDisplay", GetDisplay);
		lua_classfunction(L, "getSprite", GetSprite);
		lua_classfunction(L, "getColor", GetColor);
		lua_classfunction(L, "getSecondaryColor", GetSecondaryColor);
		lua_classfunction(L, "getAlpha", GetAlpha);
		lua_classfunction(L, "getFlashTimer", GetFlashTimer);
		lua_classfunction(L, "getFlashInterval", GetFlashInterval);
		lua_classfunction(L, "getAsFriendly", GetAsFriendly);
		lua_classfunction(L, "getRoute", GetRoute);
		lua_classfunction(L, "getBright", GetBright);
		lua_classfunction(L, "getNumber", GetNumber);
		lua_classfunction(L, "getShowCone", GetShowCone);
		lua_classfunction(L, "getFlashes", GetFlashes);
		lua_classfunction(L, "getFlashesAlternate", GetFlashesAlternate);
		lua_classfunction(L, "getAsShortRange", GetAsShortRange);
		lua_classfunction(L, "getPriority", GetPriority);
		lua_classfunction(L, "getRotation", GetRotation);
		lua_classfunction(L, "getGxtName", GetGxtName);
		lua_classfunction(L, "getName", GetName);
		lua_classfunction(L, "getRouteColor", GetRouteColor);
		lua_classfunction(L, "getPulse", GetPulse);
		lua_classfunction(L, "getAsMissionCreator", GetAsMissionCreator);
		lua_classfunction(L, "getTickVisible", GetTickVisible);
		lua_classfunction(L, "getHeadingIndicatorVisible", GetHeadingIndicatorVisible);
		lua_classfunction(L, "getOutlineIndicatorVisible", GetOutlineIndicatorVisible);
		lua_classfunction(L, "getFriendIndicatorVisible", GetFriendIndicatorVisible);
		lua_classfunction(L, "getCrewIndicatorVisible", GetCrewIndicatorVisible);
		lua_classfunction(L, "getCategory", GetCategory);
		lua_classfunction(L, "getAsHighDetail", GetAsHighDetail);
		lua_classfunction(L, "getShrinked", GetShrinked);

		lua_classfunction(L, "setDisplay", SetDisplay);
		lua_classfunction(L, "setScaleXY", SetScaleXY);
		lua_classfunction(L, "setSprite", SetSprite);
		lua_classfunction(L, "setColor", SetColor);
		lua_classfunction(L, "setRoute", SetRoute);
		lua_classfunction(L, "setRouteColor", SetRouteColor);
		lua_classfunction(L, "setSecondaryColor", SetSecondaryColor);
		lua_classfunction(L, "setAlpha", SetAlpha);
		lua_classfunction(L, "setFlashTimer", SetFlashTimer);
		lua_classfunction(L, "setFlashInterval", SetFlashInterval);
		lua_classfunction(L, "setAsFriendly", SetAsFriendly);
		lua_classfunction(L, "setBright", SetBright);
		lua_classfunction(L, "setNumber", SetNumber);
		lua_classfunction(L, "setShowCone", SetShowCone);
		lua_classfunction(L, "setFlashes", SetFlashes);
		lua_classfunction(L, "setFlashesAlternate", SetFlashesAlternate);
		lua_classfunction(L, "setAsShortRange", SetAsShortRange);
		lua_classfunction(L, "setPriority", SetPriority);
		lua_classfunction(L, "setRotation", SetRotation);
		lua_classfunction(L, "setGxtName", SetGxtName);
		lua_classfunction(L, "setName", SetName);
		lua_classfunction(L, "setPulse", SetPulse);
		lua_classfunction(L, "setAsMissionCreator", SetAsMissionCreator);
		lua_classfunction(L, "setTickVisible", SetTickVisible);
		lua_classfunction(L, "setHeadingIndicatorVisible", SetHeadingIndicatorVisible);
		lua_classfunction(L, "setOutlineIndicatorVisible", SetOutlineIndicatorVisible);
		lua_classfunction(L, "setFriendIndicatorVisible", SetFriendIndicatorVisible);
		lua_classfunction(L, "setCrewIndicatorVisible", SetCrewIndicatorVisible);
		lua_classfunction(L, "setCategory", SetCategory);
		lua_classfunction(L, "setAsHighDetail", SetAsHighDetail);
		lua_classfunction(L, "setShrinked", SetShrinked);
		lua_classfunction(L, "fade", Fade);

		lua_classvariable(L, "display", "setDisplay", "getDisplay");
		lua_classvariable(L, "scaleXY", "setScaleXY", "getScaleXY");
		lua_classvariable(L, "sprite", "setSprite", "getSprite");
		lua_classvariable(L, "color", "setColor", "getColor");
		lua_classvariable(L, "secondaryColor", "setSecondaryColor", "getSecondaryColor");
		lua_classvariable(L, "alpha", "setAlpha", "getAlpha");
		lua_classvariable(L, "flashTimer", "setFlashTimer", "getFlashTimer");
		lua_classvariable(L, "flashInterval", "setFlashInterval", "getFlashInterval");
		lua_classvariable(L, "asFriendly", "setAsFriendly", "getAsFriendly");
		lua_classvariable(L, "route", "setRoute", "getRoute");
		lua_classvariable(L, "bright", "setBright", "getBright");
		lua_classvariable(L, "number", "setNumber", "getNumber");
		lua_classvariable(L, "showCone", "setShowCone", "getShowCone");
		lua_classvariable(L, "flashes", "setFlashes", "getFlashes");
		lua_classvariable(L, "flashesAlternate", "setFlashesAlternate", "getFlashesAlternate");
		lua_classvariable(L, "asShortRange", "setAsShortRange", "getAsShortRange");
		lua_classvariable(L, "priority", "setPriority", "getPriority");
		lua_classvariable(L, "rotation", "setRotation", "getRotation");
		lua_classvariable(L, "gxtName", "setGxtName", "getGxtName");
		lua_classvariable(L, "name", "setName", "getName");
		lua_classvariable(L, "routeColor", "setRouteColor", "getRouteColor");
		lua_classvariable(L, "pulse", "setPulse", "getPulse");
		lua_classvariable(L, "asMissionCreator", "setAsMissionCreator", "getAsMissionCreator");
		lua_classvariable(L, "tickVisible", "setTickVisible", "getTickVisible");
		lua_classvariable(L, "headingIndicatorVisible", "setHeadingIndicatorVisible", "getHeadingIndicatorVisible");
		lua_classvariable(L, "outlineIndicatorVisible", "setOutlineIndicatorVisible", "getOutlineIndicatorVisible");
		lua_classvariable(L, "friendIndicatorVisible", "setFriendIndicatorVisible", "getFriendIndicatorVisible");
		lua_classvariable(L, "crewIndicatorVisible", "setCrewIndicatorVisible", "getCrewIndicatorVisible");
		lua_classvariable(L, "category", "setCategory", "getCategory");
		lua_classvariable(L, "asHighDetail", "setAsHighDetail", "getAsHighDetail");
		lua_classvariable(L, "shrinked", "setShrinked", "getShrinked");
#endif

		/*lua_classfunction(L, "setSprite", SetSprite);
		lua_classfunction(L, "setColor", SetColor);
		lua_classfunction(L, "setRoute", SetRoute);
		lua_classfunction(L, "setRouteColor", SetRouteColor);*/


		lua_classvariable(L, "global", nullptr, "isGlobal");
		lua_classvariable(L, "target", nullptr, "getTarget");
		lua_classvariable(L, "attached", nullptr, "isAttached");
		lua_classvariable(L, "attachedTo", nullptr, "getAttachedTo");
		lua_classvariable(L, "blipType", nullptr, "getBlipType");
		/*lua_classvariable(L, "sprite", "setSprite", nullptr);
		lua_classvariable(L, "color", "setColor", nullptr);
		lua_classvariable(L, "route", "setRoute", nullptr);
		lua_classvariable(L, "routeColor", "setRouteColor", nullptr);*/
	}
	lua_endclass(L);

	lua_beginclass(L, "BlipAttached", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreateAttached);
	}
	lua_endclass(L);
}

int CLuaBlipDefs::Create(lua_State* L)
{

	alt::IPlayer* player;
	int type;
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(type);
	argReader.ReadVector(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

#ifdef ALT_SERVER_API
	auto blip = Core->CreateBlip(player, static_cast<alt::IBlip::BlipType>(type), position);
#else
	auto blip = Core->CreateBlip(static_cast<alt::IBlip::BlipType>(type), position);
#endif
	
	auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
	resourceImpl->AddEntity(blip.Get());

	lua_pushbaseobject(L, blip.Get());

	return 1;
}

int CLuaBlipDefs::CreateAttached(lua_State* L)
{

	alt::IPlayer* player;
	int type;
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(player);
	argReader.ReadNumber(type);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

#ifdef ALT_SERVER_API
	auto blip = Core->CreateBlip(player, static_cast<alt::IBlip::BlipType>(type), entity);
#else
	auto blip = Core->CreateBlip(static_cast<alt::IBlip::BlipType>(type), entity->GetScriptGuid());
#endif

	lua_pushbaseobject(L, blip.Get());

	return 1;
}

#define BLIP_GET_DEFINE(PUSH, GET) \
int CLuaBlipDefs::GET(lua_State* L) { alt::IBlip* blip; CArgReader argReader(L); argReader.ReadBaseObject(blip); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } PUSH(L, blip->GET()); return 1;}

#define BLIP_SET_DEFINE(TYPE, READER, SET, HA) \
int CLuaBlipDefs::SET(lua_State* L) { alt::IBlip* blip; TYPE value; CArgReader argReader(L); argReader.ReadBaseObject(blip); argReader.READER(value); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } blip->SET(value##HA); return 0;}


int CLuaBlipDefs::AttachedTo(lua_State* L)
{
	alt::IBlip* blip;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	if (blip->AttachedTo())
	{
		lua_pushbaseobject(L, blip->AttachedTo().Get());
	}
	else
	{
		lua_pushnil(L);
	}

	return 1;
}

int CLuaBlipDefs::GetBlipType(lua_State* L)
{
	alt::IBlip* blip;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, static_cast<int>(blip->GetBlipType()));

	return 1;
}

BLIP_GET_DEFINE(lua_pushboolean, IsGlobal)
BLIP_GET_DEFINE(lua_pushbaseobject, GetTarget)
BLIP_GET_DEFINE(lua_pushboolean, IsAttached)

#ifdef ALT_CLIENT_API
BLIP_GET_DEFINE(lua_pushvector, GetScaleXY)
BLIP_GET_DEFINE(lua_pushnumber, GetDisplay)
BLIP_GET_DEFINE(lua_pushnumber, GetSprite)
BLIP_GET_DEFINE(lua_pushnumber, GetColor)
BLIP_GET_DEFINE(lua_pushrgba, GetSecondaryColor)
BLIP_GET_DEFINE(lua_pushnumber, GetAlpha)
BLIP_GET_DEFINE(lua_pushnumber, GetFlashTimer)
BLIP_GET_DEFINE(lua_pushnumber, GetFlashInterval)
BLIP_GET_DEFINE(lua_pushboolean, GetAsFriendly)
BLIP_GET_DEFINE(lua_pushboolean, GetRoute)
BLIP_GET_DEFINE(lua_pushboolean, GetBright)
BLIP_GET_DEFINE(lua_pushnumber, GetNumber)
BLIP_GET_DEFINE(lua_pushboolean, GetShowCone)
BLIP_GET_DEFINE(lua_pushboolean, GetFlashes)
BLIP_GET_DEFINE(lua_pushboolean, GetFlashesAlternate)
BLIP_GET_DEFINE(lua_pushboolean, GetAsShortRange)
BLIP_GET_DEFINE(lua_pushnumber, GetPriority)
BLIP_GET_DEFINE(lua_pushnumber, GetRotation)
BLIP_GET_DEFINE(lua_pushstring, GetGxtName)
BLIP_GET_DEFINE(lua_pushstring, GetName)
BLIP_GET_DEFINE(lua_pushrgba, GetRouteColor)
BLIP_GET_DEFINE(lua_pushboolean, GetPulse)
BLIP_GET_DEFINE(lua_pushboolean, GetAsMissionCreator)
BLIP_GET_DEFINE(lua_pushboolean, GetTickVisible)
BLIP_GET_DEFINE(lua_pushboolean, GetHeadingIndicatorVisible)
BLIP_GET_DEFINE(lua_pushboolean, GetOutlineIndicatorVisible)
BLIP_GET_DEFINE(lua_pushboolean, GetFriendIndicatorVisible)
BLIP_GET_DEFINE(lua_pushboolean, GetCrewIndicatorVisible)
BLIP_GET_DEFINE(lua_pushnumber, GetCategory)
BLIP_GET_DEFINE(lua_pushboolean, GetAsHighDetail)
BLIP_GET_DEFINE(lua_pushboolean, GetShrinked)

BLIP_SET_DEFINE(int, ReadNumber, SetDisplay)
BLIP_SET_DEFINE(int, ReadNumber, SetSprite)
BLIP_SET_DEFINE(int, ReadNumber, SetColor)
BLIP_SET_DEFINE(bool, ReadBool, SetRoute)
BLIP_SET_DEFINE(LRGBA, ReadRGBA, SetRouteColor)
BLIP_SET_DEFINE(LRGBA, ReadRGBA, SetSecondaryColor)
BLIP_SET_DEFINE(int, ReadNumber, SetAlpha)
BLIP_SET_DEFINE(int, ReadNumber, SetFlashTimer)
BLIP_SET_DEFINE(int, ReadNumber, SetFlashInterval)
BLIP_SET_DEFINE(bool, ReadBool, SetAsFriendly)
BLIP_SET_DEFINE(bool, ReadBool, SetBright)
BLIP_SET_DEFINE(int, ReadNumber, SetNumber)
BLIP_SET_DEFINE(bool, ReadBool, SetShowCone)
BLIP_SET_DEFINE(bool, ReadBool, SetFlashes)
BLIP_SET_DEFINE(bool, ReadBool, SetFlashesAlternate)
BLIP_SET_DEFINE(bool, ReadBool, SetAsShortRange)
BLIP_SET_DEFINE(int, ReadNumber, SetPriority)
BLIP_SET_DEFINE(float, ReadNumber, SetRotation)
BLIP_SET_DEFINE(std::string, ReadString, SetGxtName, .c_str())
BLIP_SET_DEFINE(std::string, ReadString, SetName, .c_str())
BLIP_SET_DEFINE(bool, ReadBool, SetPulse)
BLIP_SET_DEFINE(bool, ReadBool, SetAsMissionCreator)
BLIP_SET_DEFINE(bool, ReadBool, SetTickVisible)
BLIP_SET_DEFINE(bool, ReadBool, SetHeadingIndicatorVisible)
BLIP_SET_DEFINE(bool, ReadBool, SetOutlineIndicatorVisible)
BLIP_SET_DEFINE(bool, ReadBool, SetFriendIndicatorVisible)
BLIP_SET_DEFINE(bool, ReadBool, SetCrewIndicatorVisible)
BLIP_SET_DEFINE(int, ReadNumber, SetCategory)
BLIP_SET_DEFINE(bool, ReadBool, SetAsHighDetail)
BLIP_SET_DEFINE(bool, ReadBool, SetShrinked)

int CLuaBlipDefs::Fade(lua_State* L)
{
	alt::IBlip* blip;
	uint32_t opacity;
	uint32_t duration;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);
	argReader.ReadNumber(opacity);
	argReader.ReadNumber(duration);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	blip->Fade(opacity, duration);

	return 0;
}

int CLuaBlipDefs::SetScaleXY(lua_State* L)
{
	alt::IBlip* blip;
	float X;
	float Y;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);
	argReader.ReadNumber(X);
	argReader.ReadNumber(Y);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	blip->SetScaleXY(X, Y);

	return 0;
}
#endif

//int CLuaBlipDefs::SetSprite(lua_State* L)
//{
//	alt::IBlip* blip;
//	uint16_t sprite;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(blip);
//	argReader.ReadNumber(sprite);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	blip->SetSprite(sprite);
//
//	return 0;
//}
//
//int CLuaBlipDefs::SetColor(lua_State* L)
//{
//	alt::IBlip* blip;
//	uint8_t color;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(blip);
//	argReader.ReadNumber(color);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	blip->SetColor(color);
//
//	return 0;
//}
//
//int CLuaBlipDefs::SetRoute(lua_State* L)
//{
//	alt::IBlip* blip;
//	bool state;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(blip);
//	argReader.ReadBool(state);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	blip->SetRoute(state);
//
//	return 0;
//}
//
//int CLuaBlipDefs::SetRouteColor(lua_State* L)
//{
//	alt::IBlip* blip;
//	uint8_t color;
//
//	CArgReader argReader(L);
//	argReader.ReadBaseObject(blip);
//	argReader.ReadNumber(color);
//
//	if (argReader.HasAnyError())
//	{
//		argReader.GetErrorMessages();
//		return 0;
//	}
//
//	blip->SetRouteColor(color);
//
//	return 0;
//}
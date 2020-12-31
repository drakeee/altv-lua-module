#include <Main.h>

const char* CLuaBlipDefs::ClassName = "Blip";
void CLuaBlipDefs::Init(lua_State* L)
{
#ifdef ALT_SERVER_API
	lua_globalfunction(L, "createBlip", Create);
	lua_globalfunction(L, "createBlipAttached", CreateAttached);
#else
	lua_globalfunction(L, "createAreaBlip", CreateAreaBlip);
	lua_globalfunction(L, "createRadiusBlip", CreateRadiusBlip);
	lua_globalfunction(L, "createPointBlip", CreatePointBlip);
	lua_globalfunction(L, "createPedBlip", CreatePedBlip);
	lua_globalfunction(L, "createVehicleBlip", CreateVehicleBlip);

	lua_globalfunction(L, "getBlipScaleXY", GetScaleXY);
	lua_globalfunction(L, "getBlipDisplay", GetDisplay);
	lua_globalfunction(L, "getBlipSprite", GetSprite);
	lua_globalfunction(L, "getBlipColor", GetColor);
	lua_globalfunction(L, "getBlipSecondaryColor", GetSecondaryColor);
	lua_globalfunction(L, "getBlipAlpha", GetAlpha);
	lua_globalfunction(L, "getBlipFlashTimer", GetFlashTimer);
	lua_globalfunction(L, "getBlipFlashInterval", GetFlashInterval);
	lua_globalfunction(L, "getBlipAsFriendly", GetAsFriendly);
	lua_globalfunction(L, "getBlipRoute", GetRoute);
	lua_globalfunction(L, "getBlipBright", GetBright);
	lua_globalfunction(L, "getBlipNumber", GetNumber);
	lua_globalfunction(L, "getBlipShowCone", GetShowCone);
	lua_globalfunction(L, "getBlipFlashes", GetFlashes);
	lua_globalfunction(L, "getBlipFlashesAlternate", GetFlashesAlternate);
	lua_globalfunction(L, "getBlipAsShortRange", GetAsShortRange);
	lua_globalfunction(L, "getBlipPriority", GetPriority);
	lua_globalfunction(L, "getBlipRotation", GetRotation);
	lua_globalfunction(L, "getBlipGxtName", GetGxtName);
	lua_globalfunction(L, "getBlipName", GetName);
	lua_globalfunction(L, "getBlipRouteColor", GetRouteColor);
	lua_globalfunction(L, "getBlipPulse", GetPulse);
	lua_globalfunction(L, "getBlipAsMissionCreator", GetAsMissionCreator);
	lua_globalfunction(L, "getBlipTickVisible", GetTickVisible);
	lua_globalfunction(L, "getBlipHeadingIndicatorVisible", GetHeadingIndicatorVisible);
	lua_globalfunction(L, "getBlipOutlineIndicatorVisible", GetOutlineIndicatorVisible);
	lua_globalfunction(L, "getBlipFriendIndicatorVisible", GetFriendIndicatorVisible);
	lua_globalfunction(L, "getBlipCrewIndicatorVisible", GetCrewIndicatorVisible);
	lua_globalfunction(L, "getBlipCategory", GetCategory);
	lua_globalfunction(L, "getBlipAsHighDetail", GetAsHighDetail);
	lua_globalfunction(L, "getBlipShrinked", GetShrinked);

	lua_globalfunction(L, "setBlipDisplay", SetDisplay);
	lua_globalfunction(L, "setBlipScaleXY", SetScaleXY);
	lua_globalfunction(L, "setBlipSprite", SetSprite);
	lua_globalfunction(L, "setBlipColor", SetColor);
	lua_globalfunction(L, "setBlipRoute", SetRoute);
	lua_globalfunction(L, "setBlipRouteColor", SetRouteColor);
	lua_globalfunction(L, "setBlipSecondaryColor", SetSecondaryColor);
	lua_globalfunction(L, "setBlipAlpha", SetAlpha);
	lua_globalfunction(L, "setBlipFlashTimer", SetFlashTimer);
	lua_globalfunction(L, "setBlipFlashInterval", SetFlashInterval);
	lua_globalfunction(L, "setBlipAsFriendly", SetAsFriendly);
	lua_globalfunction(L, "setBlipBright", SetBright);
	lua_globalfunction(L, "setBlipNumber", SetNumber);
	lua_globalfunction(L, "setBlipShowCone", SetShowCone);
	lua_globalfunction(L, "setBlipFlashes", SetFlashes);
	lua_globalfunction(L, "setBlipFlashesAlternate", SetFlashesAlternate);
	lua_globalfunction(L, "setBlipAsShortRange", SetAsShortRange);
	lua_globalfunction(L, "setBlipPriority", SetPriority);
	lua_globalfunction(L, "setBlipRotation", SetRotation);
	lua_globalfunction(L, "setBlipGxtName", SetGxtName);
	lua_globalfunction(L, "setBlipName", SetName);
	lua_globalfunction(L, "setBlipPulse", SetPulse);
	lua_globalfunction(L, "setBlipAsMissionCreator", SetAsMissionCreator);
	lua_globalfunction(L, "setBlipTickVisible", SetTickVisible);
	lua_globalfunction(L, "setBlipHeadingIndicatorVisible", SetHeadingIndicatorVisible);
	lua_globalfunction(L, "setBlipOutlineIndicatorVisible", SetOutlineIndicatorVisible);
	lua_globalfunction(L, "setBlipFriendIndicatorVisible", SetFriendIndicatorVisible);
	lua_globalfunction(L, "setBlipCrewIndicatorVisible", SetCrewIndicatorVisible);
	lua_globalfunction(L, "setBlipCategory", SetCategory);
	lua_globalfunction(L, "setBlipAsHighDetail", SetAsHighDetail);
	lua_globalfunction(L, "setBlipShrinked", SetShrinked);
	lua_globalfunction(L, "fadeBlip", Fade);
#endif
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
#ifdef ALT_SERVER_API
		lua_classfunction(L, "new", Create);
#endif
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

#ifdef ALT_SERVER_API
	lua_beginclass(L, "BlipAttached", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreateAttached);
	}
#else
	lua_beginclass(L, "AreaBlip", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreateAreaBlip);
	}
	lua_endclass(L);

	lua_beginclass(L, "RadiusBlip", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreateRadiusBlip);
	}
	lua_endclass(L);

	lua_beginclass(L, "PointBlip", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreatePointBlip);
	}
	lua_endclass(L);

	lua_beginclass(L, "PedBlip", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreatePedBlip);
	}
	lua_endclass(L);

	lua_beginclass(L, "VehicleBlip", CLuaBlipDefs::ClassName);
	{
		lua_classfunction(L, "new", CreateVehicleBlip);
	}
	lua_endclass(L);
#endif

	lua_endclass(L);
}

#ifdef ALT_SERVER_API
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

	auto blip = Core->CreateBlip(player, static_cast<alt::IBlip::BlipType>(type), position);	
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

	auto blip = Core->CreateBlip(player, static_cast<alt::IBlip::BlipType>(type), entity);

	lua_pushbaseobject(L, blip.Get());

	return 1;
}
#else
int CLuaBlipDefs::CreateAreaBlip(lua_State* L)
{
	alt::Position position;
	float width;
	float height;

	CArgReader argReader(L);
	argReader.ReadVector(position);
	argReader.ReadNumber(width);
	argReader.ReadNumber(height);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, Core->CreateBlip(position, width, height));

	return 1;
}

int CLuaBlipDefs::CreateRadiusBlip(lua_State* L)
{
	alt::Position position;
	float radius;

	CArgReader argReader(L);
	argReader.ReadVector(position);
	argReader.ReadNumber(radius);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, Core->CreateBlip(position, radius));

	return 1;
}

int CLuaBlipDefs::CreatePointBlip(lua_State* L)
{
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadVector(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, Core->CreateBlip(alt::IBlip::BlipType::DESTINATION, position));

	return 1;
}

int CLuaBlipDefs::CreatePedBlip(lua_State* L)
{
	int32_t pedId;

	CArgReader argReader(L);
	argReader.ReadNumber(pedId);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, Core->CreateBlip(alt::IBlip::BlipType::PED, pedId));

	return 1;
}

int CLuaBlipDefs::CreateVehicleBlip(lua_State* L)
{
	int32_t vehicleId;

	CArgReader argReader(L);
	argReader.ReadNumber(vehicleId);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, Core->CreateBlip(alt::IBlip::BlipType::VEHICLE, vehicleId));

	return 1;
}
#endif

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
BLIP_GET_DEFINE(lua_pushvector2, GetScaleXY)
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
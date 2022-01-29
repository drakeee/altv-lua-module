#include <Main.h>

namespace lua::Class
{
	const char* Blip::ClassName = "Blip";
	void Blip::Init(lua_State* L)
	{
		DEBUG_INFO("Blip::Init");

		lua_beginclass(L, ClassName, WorldObject::ClassName);
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

			lua_classvariable(L, "display", SetDisplay, GetDisplay);
			lua_classvariable(L, "scaleXY", SetScaleXY, GetScaleXY);
			lua_classvariable(L, "sprite", SetSprite, GetSprite);
			lua_classvariable(L, "color", SetColor, GetColor);
			lua_classvariable(L, "secondaryColor", SetSecondaryColor, GetSecondaryColor);
			lua_classvariable(L, "alpha", SetAlpha, GetAlpha);
			lua_classvariable(L, "flashTimer", SetFlashTimer, GetFlashTimer);
			lua_classvariable(L, "flashInterval", SetFlashInterval, GetFlashInterval);
			lua_classvariable(L, "asFriendly", SetAsFriendly, GetAsFriendly);
			lua_classvariable(L, "route", SetRoute, GetRoute);
			lua_classvariable(L, "bright", SetBright, GetBright);
			lua_classvariable(L, "number", SetNumber, GetNumber);
			lua_classvariable(L, "showCone", SetShowCone, GetShowCone);
			lua_classvariable(L, "flashes", SetFlashes, GetFlashes);
			lua_classvariable(L, "flashesAlternate", SetFlashesAlternate, GetFlashesAlternate);
			lua_classvariable(L, "asShortRange", SetAsShortRange, GetAsShortRange);
			lua_classvariable(L, "priority", SetPriority, GetPriority);
			lua_classvariable(L, "rotation", SetRotation, GetRotation);
			lua_classvariable(L, "gxtName", SetGxtName, GetGxtName);
			lua_classvariable(L, "name", SetName, GetName);
			lua_classvariable(L, "routeColor", SetRouteColor, GetRouteColor);
			lua_classvariable(L, "pulse", SetPulse, GetPulse);
			lua_classvariable(L, "asMissionCreator", SetAsMissionCreator, GetAsMissionCreator);
			lua_classvariable(L, "tickVisible", SetTickVisible, GetTickVisible);
			lua_classvariable(L, "headingIndicatorVisible", SetHeadingIndicatorVisible, GetHeadingIndicatorVisible);
			lua_classvariable(L, "outlineIndicatorVisible", SetOutlineIndicatorVisible, GetOutlineIndicatorVisible);
			lua_classvariable(L, "friendIndicatorVisible", SetFriendIndicatorVisible, GetFriendIndicatorVisible);
			lua_classvariable(L, "crewIndicatorVisible", SetCrewIndicatorVisible, GetCrewIndicatorVisible);
			lua_classvariable(L, "category", SetCategory, GetCategory);
			lua_classvariable(L, "asHighDetail", SetAsHighDetail, GetAsHighDetail);
			lua_classvariable(L, "shrinked", SetShrinked, GetShrinked);
#endif

			/*lua_classfunction(L, SetSprite, SetSprite);
			lua_classfunction(L, SetColor, SetColor);
			lua_classfunction(L, SetRoute, SetRoute);
			lua_classfunction(L, SetRouteColor, SetRouteColor);*/


			lua_classvariable(L, "global", nullptr, IsGlobal);
			lua_classvariable(L, "target", nullptr, GetTarget);
			lua_classvariable(L, "attached", nullptr, IsAttached);
			lua_classvariable(L, "attachedTo", nullptr, AttachedTo);
			lua_classvariable(L, "blipType", nullptr, GetBlipType);
			/*lua_classvariable(L, "sprite", SetSprite, nullptr);
			lua_classvariable(L, "color", SetColor, nullptr);
			lua_classvariable(L, "route", SetRoute, nullptr);
			lua_classvariable(L, "routeColor", SetRouteColor, nullptr);*/
		}
		lua_endclass(L);

#ifdef ALT_SERVER_API
		lua_beginclass(L, "BlipAttached", Blip::ClassName);
		{
			lua_classfunction(L, "new", CreateAttached);
		}
		lua_endclass(L);
#else
		lua_beginclass(L, "AreaBlip", Blip::ClassName);
		{
			lua_classfunction(L, "new", CreateAreaBlip);
		}
		lua_endclass(L);

		lua_beginclass(L, "RadiusBlip", Blip::ClassName);
		{
			lua_classfunction(L, "new", CreateRadiusBlip);
		}
		lua_endclass(L);

		lua_beginclass(L, "PointBlip", Blip::ClassName);
		{
			lua_classfunction(L, "new", CreatePointBlip);
		}
		lua_endclass(L);

		lua_beginclass(L, "PedBlip", Blip::ClassName);
		{
			lua_classfunction(L, "new", CreatePedBlip);
		}
		lua_endclass(L);

		lua_beginclass(L, "VehicleBlip", Blip::ClassName);
		{
			lua_classfunction(L, "new", CreateVehicleBlip);
		}
		lua_endclass(L);
#endif

		DEBUG_INFO("Blip::Init ...done");
	}

#ifdef ALT_SERVER_API
	int Blip::Create(lua_State* L)
	{

		alt::IPlayer* player;
		int type;
		alt::Position position;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(player);
		argReader.ReadNumber(type);
		argReader.ReadVector(position);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto blip = Core->CreateBlip(player, static_cast<alt::IBlip::BlipType>(type), position);
		auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(blip.Get());

		lua_pushbaseobject(L, blip.Get());

		return 1;
	}

	int Blip::CreateAttached(lua_State* L)
	{

		alt::IPlayer* player;
		int type;
		alt::IEntity* entity;

		ArgumentReader argReader(L);
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
	int Blip::CreateAreaBlip(lua_State* L)
	{
		alt::Position position;
		float width;
		float height;

		ArgumentReader argReader(L);
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

	int Blip::CreateRadiusBlip(lua_State* L)
	{
		alt::Position position;
		float radius;

		ArgumentReader argReader(L);
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

	int Blip::CreatePointBlip(lua_State* L)
	{
		alt::Position position;

		ArgumentReader argReader(L);
		argReader.ReadVector(position);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, Core->CreateBlip(alt::IBlip::BlipType::DESTINATION, position));

		return 1;
	}

	int Blip::CreatePedBlip(lua_State* L)
	{
		int32_t pedId;

		ArgumentReader argReader(L);
		argReader.ReadNumber(pedId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, Core->CreateBlip(alt::IBlip::BlipType::PED, pedId));

		return 1;
	}

	int Blip::CreateVehicleBlip(lua_State* L)
	{
		int32_t vehicleId;

		ArgumentReader argReader(L);
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
int Blip::GET(lua_State* L) { alt::IBlip* blip; ArgumentReader argReader(L); argReader.ReadBaseObject(blip); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } PUSH(L, blip->GET()); return 1;}

#define BLIP_SET_DEFINE(TYPE, READER, SET, HA) \
int Blip::SET(lua_State* L) { alt::IBlip* blip; TYPE value; ArgumentReader argReader(L); argReader.ReadBaseObject(blip); argReader.READER(value); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } blip->SET(value##HA); return 0;}


	int Blip::AttachedTo(lua_State* L)
	{
		alt::IBlip* blip;

		ArgumentReader argReader(L);
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

	int Blip::GetBlipType(lua_State* L)
	{
		alt::IBlip* blip;

		ArgumentReader argReader(L);
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
		BLIP_SET_DEFINE(alt::RGBA, ReadRGBA, SetRouteColor)
		BLIP_SET_DEFINE(alt::RGBA, ReadRGBA, SetSecondaryColor)
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

		int Blip::Fade(lua_State* L)
	{
		alt::IBlip* blip;
		uint32_t opacity;
		uint32_t duration;

		ArgumentReader argReader(L);
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

	int Blip::SetScaleXY(lua_State* L)
	{
		alt::IBlip* blip;
		float X;
		float Y;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(blip);
		argReader.ReadNumber(X);
		argReader.ReadNumber(Y);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		blip->SetScaleXY(alt::Vector2f(X, Y));

		return 0;
	}
#endif

	//int Blip::SetSprite(lua_State* L)
	//{
	//	alt::IBlip* blip;
	//	uint16_t sprite;
	//
	//	ArgumentReader argReader(L);
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
	//int Blip::SetColor(lua_State* L)
	//{
	//	alt::IBlip* blip;
	//	uint8_t color;
	//
	//	ArgumentReader argReader(L);
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
	//int Blip::SetRoute(lua_State* L)
	//{
	//	alt::IBlip* blip;
	//	bool state;
	//
	//	ArgumentReader argReader(L);
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
	//int Blip::SetRouteColor(lua_State* L)
	//{
	//	alt::IBlip* blip;
	//	uint8_t color;
	//
	//	ArgumentReader argReader(L);
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
}
#include <Main.h>
const char* CLuaBlipDefs::ClassName = "Blip";
void CLuaBlipDefs::Init(lua_State* L)
{
	lua_beginclass(L, ClassName, CLuaWorldObjectDefs::ClassName);
	{
		lua_classfunction(L, "new", Create);
		lua_classfunction(L, "isGlobal", IsGlobal);
		lua_classfunction(L, "getTarget", GetTarget);
		lua_classfunction(L, "isAttached", IsAttached);
		lua_classfunction(L, "attachedTo", AttachedTo);
		lua_classfunction(L, "getBlipType", GetBlipType);
		lua_classfunction(L, "setSprite", SetSprite);
		lua_classfunction(L, "setColor", SetColor);
		lua_classfunction(L, "setRoute", SetRoute);
		lua_classfunction(L, "setRouteColor", SetRouteColor);


		lua_classvariable(L, "global", nullptr, "isGlobal");
		lua_classvariable(L, "target", nullptr, "getTarget");
		lua_classvariable(L, "attached", nullptr, "isAttached");
		lua_classvariable(L, "attachedTo", nullptr, "attachedTo");
		lua_classvariable(L, "type", nullptr, "getBlipType");
		lua_classvariable(L, "sprite", "setSprite", nullptr);
		lua_classvariable(L, "color", "setColor", nullptr);
		lua_classvariable(L, "route", "setRoute", nullptr);
		lua_classvariable(L, "routeColor", "setRouteColor", nullptr);
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

	auto blip = Core->CreateBlip(player, static_cast<alt::IBlip::BlipType>(type), position);

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

int CLuaBlipDefs::IsGlobal(lua_State* L)
{
	alt::IBlip* blip;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, blip->IsGlobal());

	return 1;
}

int CLuaBlipDefs::GetTarget(lua_State* L)
{
	alt::IBlip* blip;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, blip->GetTarget().Get());

	return 1;
}

int CLuaBlipDefs::IsAttached(lua_State* L)
{
	alt::IBlip* blip;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, blip->IsAttached());

	return 1;
}

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

int CLuaBlipDefs::SetSprite(lua_State* L)
{
	alt::IBlip* blip;
	uint16_t sprite;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);
	argReader.ReadNumber(sprite);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	blip->SetSprite(sprite);

	return 0;
}

int CLuaBlipDefs::SetColor(lua_State* L)
{
	alt::IBlip* blip;
	uint8_t color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);
	argReader.ReadNumber(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	blip->SetColor(color);

	return 0;
}

int CLuaBlipDefs::SetRoute(lua_State* L)
{
	alt::IBlip* blip;
	bool state;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);
	argReader.ReadBool(state);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	blip->SetRoute(state);

	return 0;
}

int CLuaBlipDefs::SetRouteColor(lua_State* L)
{
	alt::IBlip* blip;
	uint8_t color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(blip);
	argReader.ReadNumber(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	blip->SetRouteColor(color);

	return 0;
}
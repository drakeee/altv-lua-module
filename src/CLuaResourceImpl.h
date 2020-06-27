#pragma once

#include "Main.h"

class CLuaResourceImpl : public alt::IResource::Impl
{
public:
	CLuaResourceImpl(alt::IResource* resource);
	~CLuaResourceImpl();

	bool Start() override;
	bool Stop() override;

	bool OnEvent(const alt::CEvent* ev) override;
	void OnTick() override;

	void OnCreateBaseObject(alt::Ref<alt::IBaseObject> object) override;
	void OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object) override;

private:
	lua_State* resourceState = nullptr;
	alt::IResource* resource;

	const std::list<std::string> eventTypes{
		"NONE",

		// Shared
		"PLAYER_CONNECT",
		"PLAYER_DISCONNECT",

		"RESOURCE_START",
		"RESOURCE_STOP",
		"RESOURCE_ERROR",

		"SERVER_SCRIPT_EVENT",
		"CLIENT_SCRIPT_EVENT",

		"META_CHANGE",
		"SYNCED_META_CHANGE",
		"STREAM_SYNCED_META_CHANGE",
		"GLOBAL_META_CHANGE",
		"GLOBAL_SYNCED_META_CHANGE",

		"PLAYER_DAMAGE",
		"PLAYER_DEATH",
		"FIRE_EVENT",
		"EXPLOSION_EVENT",
		"WEAPON_DAMAGE_EVENT",
		"VEHICLE_DESTROY",

		"CHECKPOINT_EVENT",
		"COLSHAPE_EVENT",
		"PLAYER_ENTER_VEHICLE",
		"PLAYER_LEAVE_VEHICLE",
		"PLAYER_CHANGE_VEHICLE_SEAT",

		"REMOVE_ENTITY_EVENT",

		"DATA_NODE_RECEIVED_EVENT",

		"CONSOLE_COMMAND_EVENT",

		// Client
		"CONNECTION_COMPLETE",
		"DISCONNECT_EVENT",
		"WEB_VIEW_EVENT",
		"KEYBOARD_EVENT",
		"GAME_ENTITY_CREATE",
		"GAME_ENTITY_DESTROY",

		"ALL",
		"SIZE"
	};
};
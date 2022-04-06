#pragma once

#define MODULE_VERSION "0.1.0"
#define ADDITIONAL_MODULE_FOLDER "modules"

// #ifndef ALT_SERVER_API
// 	#define ALT_SERVER_API
// #endif

#ifdef _WIN32
static const char* preferred_separator = "\\";
#else
static const char* preferred_separator = "/";

#define sprintf_s sprintf
#endif

//Include basic stuff
#include <iostream>
//#include <filesystem>
#include <cassert>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

//Semantic versioning
#include <semver.hpp>

//Include AltV SDK
#include <SDK.h>
#include <version/version.h>

#include <events/CFireEvent.h>
#include <events/CStartProjectileEvent.h>
#include <events/CPlayerWeaponChangeEvent.h>
#include <events/CVehicleAttachEvent.h>
#include <events/CVehicleDetachEvent.h>
#include <events/CNetOwnerChangeEvent.h>
#include <events/CPlayerEnteringVehicleEvent.h>

//Include Lua
#include <lua.hpp>

extern alt::ICore* Core;

extern bool isClient;
extern bool isServer;

const alt::String p_s(preferred_separator);

typedef alt::Vector3f Vector3fp;
typedef alt::Vector2f Vector2fp;

#include "VehicleModels.hpp"

#include "Helpers/LuaHelpers.h"
#include "Helpers/ArgumentReader.h"
#include "EventManager.h"
#include "LuaScriptRuntime.h"
#include "LuaResourceImpl.h"
#include "Helpers/MetaFunction.h"

#include <Defs/Alt.h>
#include <Defs/Config.h>
#include <Defs/Client/Native.h>
#include <Defs/Resource.h>
#include <Defs/Shared/Vector2.h>
#include <Defs/Shared/Vector3.h>
#include <Defs/Shared/RGBA.h>
#include <Defs/Client/HandlingData.h>
#include <Defs/Client/MapData.h>
#include <Defs/Client/DiscordManager.h>
#include <Defs/Voice.h>
#include <Defs/Client/Audio.h>
#include <Defs/Client/RmlDocument.h>
#include <Defs/Client/RmlElement.h>
#include <Defs/Client/WebView.h>
#include <Defs/Client/WebSocket.h>
#include <Defs/Entity/BaseObject.h>
#include <Defs/Entity/WorldObject.h>
#include <Defs/Entity/Entity.h>
#include <Defs/Entity/Player.h>
#include <Defs/Entity/Vehicle.h>
#include <Defs/Entity/Blip.h>
#include <Defs/Entity/Checkpoint.h>
#include <Defs/Entity/ColShape.h>
#include <Defs/Entity/VoiceChannel.h>

#include <Defs/Shared/MiscScripts.h>
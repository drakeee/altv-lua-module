#pragma once

#define MODULE_VERSION "0.1.0"
#define ALT_SERVER_API

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

//Semantic versioning
#include <semver.hpp>

//Include AltV SDK
#include <SDK.h>
#include <events/CFireEvent.h>
#include <events/CStartProjectileEvent.h>

//Include Lua
#include <lua.hpp>

//Include SQL libraries
//#include <mysql.h>
//#include <CDatabaseManager.h>
//#include <Database/MariaDatabase.h>

extern alt::ICore* Core;

typedef alt::Vector<float, 3, alt::PointLayout> Vector3fp;

#include "CVehModels.h"
#include "CVehMods.h"
#include "LRGBA.h"

#include "CLuaDefs.h"
#include "CArgReader.h"
#include "CLuaScriptRuntime.h"
#include "CLuaResourceImpl.h"
#include "CLuaFunctionDefs.h"

#include <Defs/CLuaAltFuncDefs.h>
#include <Defs/CLuaResourceFuncDefs.h>
#include <Defs/CLuaVector3Defs.h>
#include <Defs/CLuaRGBADefs.h>
#include <Defs/Entity/CLuaBaseObjectDefs.h>
#include <Defs/Entity/CLuaWorldObjectDefs.h>
#include <Defs/Entity/CLuaEntityDefs.h>
#include <Defs/Entity/CLuaPlayerDefs.h>
#include <Defs/Entity/CLuaVehicleDefs.h>
#include <Defs/Entity/CLuaBlipDefs.h>
#include <Defs/Entity/CLuaCheckpointDefs.h>
#include <Defs/Entity/CLuaColShapeDefs.h>
#include <Defs/Entity/CLuaVoiceChannelDefs.h>

#include <Defs/CLuaMiscScripts.h>
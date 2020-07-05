// altv-lua-module.h : Include file for standard system include files,
// or project specific include files.

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

//Include AltV SDK
#include <SDK.h>

//Include Lua
#include <lua.hpp>

extern alt::ICore* Core;

//#include "CLuaDefs.h"
#include "CLuaDefs2.h"
#include "CArgReader.h"
#include "CLuaScriptRuntime.h"
#include "CLuaResourceImpl.h"
#include "CLuaFunctionDefs.h"

#include <Defs/CLuaAltFuncDefs.h>
#include <Defs/CLuaVector3Defs.h>
#include <Defs/Entity/CLuaBaseObjectDefs.h>
#include <Defs/Entity/CLuaEntityDefs.h>
#include <Defs/Entity/CLuaVehicleDefs.h>
#include "Main.h"
#include <chrono>
#include <fstream>

alt::ICore* Core;

#ifdef ALT_SERVER_API
bool isClient = false;
bool isServer = true;
#else
bool isClient = true;
bool isServer = false;
#endif

#ifdef ALT_SERVER_API

EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);
	Core = _core;

	auto& runtime = LuaScriptRuntime::Instance();
	
	_core->LogInfo(alt::String("Lua server module. Version: v" + alt::String(runtime.GetVersion().to_string())));
	_core->RegisterScriptRuntime("lua", &runtime);
	
	return true;
}
#else
EXPORT alt::IScriptRuntime *CreateScriptRuntime(alt::ICore *_core)
{
    alt::ICore::SetInstance(_core);
	Core = _core;

    auto runtime = &LuaScriptRuntime::Instance();

	_core->LogInfo(alt::String("Lua client module. Version: v" + alt::String(runtime->GetVersion().to_string())));

    return runtime;
}

EXPORT const char* GetType()
{
	return "lua";
}
#endif

EXPORT const char* GetSDKHash()
{
	return ALT_SDK_VERSION;
}
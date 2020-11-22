#include "Main.h"
#include <chrono>
#include <fstream>

alt::ICore* Core;

EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);
	Core = _core;


	auto& runtime = CLuaScriptRuntime::Instance();
	
	_core->LogInfo(alt::String("Lua module. Version: v" + runtime.GetVersion().to_string()));
	_core->RegisterScriptRuntime("lua", &runtime);
	
	return true;
}

EXPORT uint32_t GetSDKVersion()
{
	return alt::ICore::SDK_VERSION;
}
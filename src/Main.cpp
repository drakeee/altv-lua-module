#include "Main.h"

alt::ICore* Core;

EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);

	auto& runtime = CLuaScriptRuntime::Instance();

	_core->LogInfo(alt::String("Lua module has been loaded. Version: " MODULE_VERSION));
	_core->RegisterScriptRuntime("lua", &runtime);

	Core = _core;

	return true;
}

EXPORT uint32_t GetSDKVersion()
{
	return alt::ICore::SDK_VERSION;
}
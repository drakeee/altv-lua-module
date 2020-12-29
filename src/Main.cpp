#include "Main.h"
#include <chrono>
#include <fstream>

alt::ICore* Core;

#ifdef ALT_SERVER_API
EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);
	Core = _core;

	auto& runtime = CLuaScriptRuntime::Instance();
	
	_core->LogInfo(alt::String("Lua server module. Version: v" + runtime.GetVersion().to_string()));
	_core->RegisterScriptRuntime("lua", &runtime);
	
	return true;
}
#else
EXPORT alt::IScriptRuntime *CreateJSScriptRuntime(alt::ICore *_core)
{
    alt::ICore::SetInstance(_core);
	Core = _core;

    auto runtime = &CLuaScriptRuntime::Instance();

	_core->LogInfo(alt::String("Lua client module. Version: v" + runtime->GetVersion().to_string()));

    return runtime;
}
#endif

EXPORT uint32_t GetSDKVersion()
{
	return alt::ICore::SDK_VERSION;
}
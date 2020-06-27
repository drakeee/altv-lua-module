#include "Main.h"

alt::ICore* Core;

EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);

	_core->LogInfo(alt::String("Lua module has been loaded. Version: " MODULE_VERSION));
	_core->RegisterScriptRuntime("lua", &CLuaScriptRuntime::Instance());

	Core = _core;

	//auto& apiCore = alt::ICore::Instance();
	//auto& runtime = CNodeScriptRuntime::Instance();

	
	//_core->RegisterScriptRuntime("lua", )

	//apiCore.RegisterScriptRuntime("js", &runtime);
	//apiCore.SubscribeCommand("js-module", &CommandHandler);

	return true;
}

EXPORT uint32_t GetSDKVersion()
{
	return alt::ICore::SDK_VERSION;
}
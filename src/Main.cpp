#include "Main.h"

alt::ICore* Core;

EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);

	auto& runtime = CLuaScriptRuntime::Instance();

	_core->LogInfo(alt::String("Lua module has been loaded. Version: " MODULE_VERSION));
	_core->RegisterScriptRuntime("lua", &runtime);

	Core = _core;

	auto &dataReader = CVehModels::Instance(); //instantiate the reader
	auto &dataMods = CVehMods::Instance();

	CVehModels::VehicleInfo* bison_name = dataReader.GetVehicleInfo("bison"); //you can get vehicle informations by name
	CVehModels::VehicleInfo* bison_hash = dataReader.GetVehicleInfo(202226976); //also you can get vehicle informations by hash

	auto bison_by_name = dataReader["bison"]; //you can also use the [] operator for both cases as well
	auto bison_by_hash = dataReader[202226976];

	if (bison_name == nullptr)
	{
		//vehicle information not found
	}
	else
	{
		//vehicle information found
	}

	//if you want you can loop through all of the vehicle information by hashes
	for (auto vehicleInfo : dataReader.GetVehicleInfosByHash())
	{
		//vehicleInfo.first -> this will hold the vehicle hash number
		//vehicleInfo.second -> will point to a VehicleInfo*
	}

	//also you can loop through all of the vehicle informations by vehicle names
	for (auto vehicleInfo : dataReader.GetVehicleInfosByString())
	{
		//vehicleInfo.first -> this will hold the vehicle name
		//vehicleInfo.second -> will point to a VehicleInfo*
	}

	//Core->LogInfo("Info: " + std::to_string(veh->GetVehicleCount()));

	int intTest[2];
	Core->LogInfo("IntSize: " + std::to_string(sizeof intTest));

	return true;
}

EXPORT uint32_t GetSDKVersion()
{
	return alt::ICore::SDK_VERSION;
}
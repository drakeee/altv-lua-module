#include "Main.h"

namespace lua::Class
{
	const char* Vehicle::ClassName = "Vehicle";
	void Vehicle::Init(lua_State* L)
	{
		DEBUG_INFO("Vehicle::Init");

		lua_beginclass(L, ClassName, Entity::ClassName);
		{
			//lua_classmeta(L, "__gc", destroy);
			lua_classmeta(L, "__tostring", tostring);
			lua_classmeta(L, "__pairs", pairs);
			lua_classmeta(L, "__ipairs", ipairs);

			lua_classfunction(L, "getDriver", GetDriver);
			lua_classfunction(L, "isDestroyed", IsDestroyed);
			lua_classfunction(L, "getMod", GetMod);
			lua_classfunction(L, "getModsCount", GetModsCount);
			lua_classfunction(L, "getModKitsCount", GetModKitsCount);
			lua_classfunction(L, "getModKit", GetModKit);
			lua_classfunction(L, "isPrimaryColorRGB", IsPrimaryColorRGB);
			lua_classfunction(L, "getPrimaryColor", GetPrimaryColor);
			lua_classfunction(L, "getPrimaryColorRGB", GetPrimaryColorRGB);
			lua_classfunction(L, "isSecondaryColorRGB", IsSecondaryColorRGB);
			lua_classfunction(L, "getSecondaryColor", GetSecondaryColor);
			lua_classfunction(L, "getSecondaryColorRGB", GetSecondaryColorRGB);
			lua_classfunction(L, "getPearlColor", GetPearlColor);
			lua_classfunction(L, "getWheelColor", GetWheelColor);
			lua_classfunction(L, "getInteriorColor", GetInteriorColor);
			lua_classfunction(L, "getDashboardColor", GetDashboardColor);
			lua_classfunction(L, "isTireSmokeColorCustom", IsTireSmokeColorCustom);
			lua_classfunction(L, "getTireSmokeColor", GetTireSmokeColor);
			lua_classfunction(L, "getWheelType", GetWheelType);
			lua_classfunction(L, "getWheelVariation", GetWheelVariation);
			lua_classfunction(L, "getRearWheelVariation", GetRearWheelVariation);
			lua_classfunction(L, "getCustomTires", GetCustomTires);
			lua_classfunction(L, "getSpecialDarkness", GetSpecialDarkness);
			lua_classfunction(L, "getNumberplateIndex", GetNumberplateIndex);
			lua_classfunction(L, "getNumberplateText", GetNumberplateText);
			lua_classfunction(L, "getWindowTint", GetWindowTint);
			lua_classfunction(L, "getDirtLevel", GetDirtLevel);
			lua_classfunction(L, "isExtraOn", IsExtraOn);
			lua_classfunction(L, "isNeonActive", IsNeonActive);
			lua_classfunction(L, "getNeonActive", GetNeonActive);
			lua_classfunction(L, "getNeonColor", GetNeonColor);
			lua_classfunction(L, "getLivery", GetLivery);
			lua_classfunction(L, "getRoofLivery", GetRoofLivery);
			lua_classfunction(L, "getAppearanceDataBase64", GetAppearanceDataBase64);
			lua_classfunction(L, "isEngineOn", IsEngineOn);
			lua_classfunction(L, "isHandbrakeActive", IsHandbrakeActive);
			lua_classfunction(L, "getHeadlightColor", GetHeadlightColor);
			lua_classfunction(L, "getRadioStationIndex", GetRadioStationIndex);
			lua_classfunction(L, "isSirenActive", IsSirenActive);
			// TODO document available values. Enum?
			lua_classfunction(L, "getLockState", GetLockState);
			// TODO document available values. Enum?
			lua_classfunction(L, "getDoorState", GetDoorState);
			lua_classfunction(L, "isWindowOpened", IsWindowOpened);
			lua_classfunction(L, "isDaylightOn", IsDaylightOn);
			lua_classfunction(L, "isNightlightOn", IsNightlightOn);
			lua_classfunction(L, "getRoofState", GetRoofState);
			lua_classfunction(L, "isFlamethrowerActive", IsFlamethrowerActive);
			lua_classfunction(L, "getLightsMultiplier", GetLightsMultiplier);
			lua_classfunction(L, "getGameStateBase64", GetGameStateBase64);
			lua_classfunction(L, "getEngineHealth", GetEngineHealth);
			lua_classfunction(L, "getPetrolTankHealth", GetPetrolTankHealth);
			lua_classfunction(L, "getWheelsCount", GetWheelsCount);
			lua_classfunction(L, "isWheelBurst", IsWheelBurst);
			lua_classfunction(L, "doesWheelHasTire", DoesWheelHasTire);
			lua_classfunction(L, "isWheelDetached", IsWheelDetached);
			lua_classfunction(L, "isWheelOnFire", IsWheelOnFire);
			lua_classfunction(L, "getWheelHealth", GetWheelHealth);
			lua_classfunction(L, "getRepairsCount", GetRepairsCount);
			lua_classfunction(L, "getBodyHealth", GetBodyHealth);
			lua_classfunction(L, "getBodyAdditionalHealth", GetBodyAdditionalHealth);
			lua_classfunction(L, "getHealthDataBase64", GetHealthDataBase64);
			lua_classfunction(L, "getPartDamageLevel", GetPartDamageLevel);
			lua_classfunction(L, "getPartBulletHoles", GetPartBulletHoles);
			lua_classfunction(L, "isLightDamaged", IsLightDamaged);
			lua_classfunction(L, "isWindowDamaged", IsWindowDamaged);
			lua_classfunction(L, "isSpecialLightDamaged", IsSpecialLightDamaged);
			lua_classfunction(L, "hasArmoredWindows", HasArmoredWindows);
			lua_classfunction(L, "getArmoredWindowHealth", GetArmoredWindowHealth);
			lua_classfunction(L, "getArmoredWindowShootCount", GetArmoredWindowShootCount);
			lua_classfunction(L, "getBumperDamageLevel", GetBumperDamageLevel);
			lua_classfunction(L, "getDamageDataBase64", GetDamageDataBase64);
			lua_classfunction(L, "isManualEngineControl", IsManualEngineControl);
			lua_classfunction(L, "getScriptDataBase64", GetScriptDataBase64);
			lua_classfunction(L, "getAll", ipairs);

	#ifdef ALT_SERVER_API
			lua_classfunction(L, "new", CreateVehicle);

			lua_classfunction(L, "repair", Repair);
			lua_classfunction(L, "setMod", SetMod);
			lua_classfunction(L, "setModKit", SetModKit);
			lua_classfunction(L, "setPrimaryColor", SetPrimaryColor);
			lua_classfunction(L, "setPrimaryColorRGB", SetPrimaryColorRGB);
			lua_classfunction(L, "setSecondaryColor", SetSecondaryColor);
			lua_classfunction(L, "setSecondaryColorRGB", SetSecondaryColorRGB);
			lua_classfunction(L, "setPearlColor", SetPearlColor);
			lua_classfunction(L, "setWheelColor", SetWheelColor);
			lua_classfunction(L, "setInteriorColor", SetInteriorColor);
			lua_classfunction(L, "setDashboardColor", SetDashboardColor);
			lua_classfunction(L, "setTireSmokeColor", SetTireSmokeColor);
			lua_classfunction(L, "setWheels", SetWheels);
			lua_classfunction(L, "setRearWheels", SetRearWheels);
			lua_classfunction(L, "setCustomTires", SetCustomTires);
			lua_classfunction(L, "setSpecialDarkness", SetSpecialDarkness);
			lua_classfunction(L, "setNumberplateIndex", SetNumberplateIndex);
			lua_classfunction(L, "setNumberplateText", SetNumberplateText);
			lua_classfunction(L, "setWindowTint", SetWindowTint);
			lua_classfunction(L, "setDirtLevel", SetDirtLevel);
			lua_classfunction(L, "setNeonActive", SetNeonActive);
			lua_classfunction(L, "setNeonColor", SetNeonColor);
			lua_classfunction(L, "setLivery", SetLivery);
			lua_classfunction(L, "setRoofLivery", SetRoofLivery);
			lua_classfunction(L, "setEngineOn", SetEngineOn);
			lua_classfunction(L, "setHeadlightColor", SetHeadlightColor);
			lua_classfunction(L, "setRadioStationIndex", SetRadioStationIndex);
			lua_classfunction(L, "setSirenActive", SetSirenActive);
			lua_classfunction(L, "setLockState", SetLockState);
			lua_classfunction(L, "setDoorState", SetDoorState);
			lua_classfunction(L, "setWindowOpened", SetWindowOpened);
			lua_classfunction(L, "setRoofState", SetRoofState);
			lua_classfunction(L, "setLightsMultiplier", SetLightsMultiplier);
			lua_classfunction(L, "setEngineHealth", SetEngineHealth);
			lua_classfunction(L, "setPetrolTankHealth", SetPetrolTankHealth);
			lua_classfunction(L, "setWheelBurst", SetWheelBurst);
			lua_classfunction(L, "setWheelHasTire", SetWheelHasTire);
			lua_classfunction(L, "setWheelDetached", SetWheelDetached);
			lua_classfunction(L, "setWheelOnFire", SetWheelOnFire);
			lua_classfunction(L, "setWheelHealth", SetWheelHealth);
			lua_classfunction(L, "setBodyHealth", SetBodyHealth);
			lua_classfunction(L, "setBodyAdditionalHealth", SetBodyAdditionalHealth);
			lua_classfunction(L, "setPartDamageLevel", SetPartDamageLevel);
			lua_classfunction(L, "setPartBulletHoles", SetPartBulletHoles);
			lua_classfunction(L, "setLightDamaged", SetLightDamaged);
			lua_classfunction(L, "setWindowDamaged", SetWindowDamaged);
			lua_classfunction(L, "setSpecialLightDamaged", SetSpecialLightDamaged);
			lua_classfunction(L, "setArmoredWindowHealth", SetArmoredWindowHealth);
			lua_classfunction(L, "setArmoredWindowShootCount", SetArmoredWindowShootCount);
			lua_classfunction(L, "setBumperDamageLevel", SetBumperDamageLevel);
			lua_classfunction(L, "setManualEngineControl", SetManualEngineControl);
			lua_classfunction(L, "toggleExtra", ToggleExtra);
			lua_classfunction(L, "loadAppearanceDataFromBase64", LoadAppearanceDataFromBase64);
			lua_classfunction(L, "loadGameStateFromBase64", LoadGameStateFromBase64);
			lua_classfunction(L, "loadHealthDataFromBase64", LoadHealthDataFromBase64);
			lua_classfunction(L, "loadDamageDataFromBase64", LoadDamageDataFromBase64);
			lua_classfunction(L, "loadScriptDataFromBase64", LoadScriptDataFromBase64);
			lua_classfunction(L, "getAttached", GetAttached);
			lua_classfunction(L, "getAttachedTo", GetAttachedTo);
			lua_classfunction(L, "setDriftMode", SetDriftMode);
			lua_classfunction(L, "isDriftModeEnabled", IsDriftMode);

			lua_classfunction(L, "setTrainEngineId", SetTrainEngineId);
			lua_classfunction(L, "setTrainLinkedToBackwardId", SetTrainLinkedToBackwardId);
			lua_classfunction(L, "setTrainLinkedToForwardId", SetTrainLinkedToForwardId);

			lua_classfunction(L, "isBoatAnchorActive", IsBoatAnchorActive);
			lua_classfunction(L, "setBoatAnchorActive", SetBoatAnchorActive);

			lua_classfunction(L, "setSearchLightTo", SetSearchLight);

			lua_classvariable(L, "modKit", SetModKit, GetModKit);
			lua_classvariable(L, "primaryColor", SetPrimaryColor, GetPrimaryColor);
			lua_classvariable(L, "secondaryColor", SetSecondaryColor, GetSecondaryColor);
			lua_classvariable(L, "secondaryColorRGB", SetSecondaryColorRGB, GetSecondaryColorRGB);
			lua_classvariable(L, "pearlColor", SetPearlColor, GetPearlColor);
			lua_classvariable(L, "wheelColor", SetWheelColor, GetWheelColor);
			lua_classvariable(L, "interiorColor", SetInteriorColor, GetInteriorColor);
			lua_classvariable(L, "dashboardColor", SetDashboardColor, GetDashboardColor);
			lua_classvariable(L, "tireSmokeColor", SetTireSmokeColor, GetTireSmokeColor);
			lua_classvariable(L, "rearWheels", SetRearWheels, nullptr);
			lua_classvariable(L, "customTires", SetCustomTires, GetCustomTires);
			lua_classvariable(L, "specialDarkness", SetSpecialDarkness, GetSpecialDarkness);
			lua_classvariable(L, "numberplateIndex", SetNumberplateIndex, GetNumberplateIndex);
			lua_classvariable(L, "numberplateText", SetNumberplateText, GetNumberplateText);
			lua_classvariable(L, "windowTint", SetWindowTint, GetWindowTint);
			lua_classvariable(L, "dirtLevel", SetDirtLevel, GetDirtLevel);
			lua_classvariable(L, "neonColor", SetNeonColor, GetNeonColor);
			lua_classvariable(L, "livery", SetLivery, GetLivery);
			lua_classvariable(L, "roofLivery", SetRoofLivery, GetRoofLivery);
			lua_classvariable(L, "engineOn", SetEngineOn, nullptr);
			lua_classvariable(L, "headlightColor", SetHeadlightColor, GetHeadlightColor);
			lua_classvariable(L, "radioStationIndex", SetRadioStationIndex, GetRadioStationIndex);
			lua_classvariable(L, "sirenActive", SetSirenActive, IsSirenActive);
			lua_classvariable(L, "lockState", SetLockState, GetLockState);
			lua_classvariable(L, "doorState", SetDoorState, GetDoorState);
			lua_classvariable(L, "roof", SetRoofState, GetRoofState);
			lua_classvariable(L, "lightsMultiplier", SetLightsMultiplier, GetLightsMultiplier);
			lua_classvariable(L, "engineHealth", SetEngineHealth, GetEngineHealth);
			lua_classvariable(L, "petrolTankHealth", SetPetrolTankHealth, GetPetrolTankHealth);
			lua_classvariable(L, "bodyHealth", SetBodyHealth, GetBodyHealth);
			lua_classvariable(L, "bodyAdditionalHealth", SetBodyAdditionalHealth, GetBodyAdditionalHealth);
			lua_classvariable(L, "manualEngineControl", SetManualEngineControl, IsManualEngineControl);
			lua_classvariable(L, "appearanceDataBase64", LoadAppearanceDataFromBase64, GetAppearanceDataBase64);
			lua_classvariable(L, "gameStateBase64", LoadGameStateFromBase64, GetGameStateBase64);
			lua_classvariable(L, "healthDataBase64", LoadHealthDataFromBase64, GetHealthDataBase64);
			lua_classvariable(L, "damageDataBase64", LoadDamageDataFromBase64, GetDamageDataBase64);
			lua_classvariable(L, "scriptDataBase64", LoadScriptDataFromBase64, GetScriptDataBase64);
			lua_classvariable(L, "attached", nullptr, GetAttached);
			lua_classvariable(L, "attachedTo", nullptr, GetAttachedTo);

			lua_classvariable(L, "driftModeEnabled", SetDriftMode, IsDriftMode);

			lua_classvariable(L, "isMissionTrain", SetTrainMissionTrain, IsTrainMissionTrain);
			lua_classvariable(L, "trainTrackId", SetTrainTrackId, GetTrainTrackId);
			lua_classvariable(L, "trainEngineId", nullptr, GetTrainEngineId);
			lua_classvariable(L, "trainConfigIndex", SetTrainConfigIndex, GetTrainConfigIndex);
			lua_classvariable(L, "trainDistanceFromEngine", SetTrainDistanceFromEngine, GetTrainDistanceFromEngine);
			lua_classvariable(L, "isTrainEngine", SetTrainIsEngine, IsTrainEngine);
			lua_classvariable(L, "isTrainCaboose", SetTrainIsCaboose, IsTrainCaboose);
			lua_classvariable(L, "trainDirection", SetTrainDirection, GetTrainDirection);
			lua_classvariable(L, "trainPassengerCarriages", SetTrainHasPassengerCarriages, HasTrainPassengerCarriages);
			lua_classvariable(L, "trainRenderDerailed", SetTrainRenderDerailed, GetTrainRenderDerailed);
			lua_classvariable(L, "trainForceDoorsOpen", SetTrainForceDoorsOpen, GetTrainForceDoorsOpen);
			lua_classvariable(L, "trainCruiseSpeed", SetTrainCruiseSpeed, GetTrainCruiseSpeed);
			lua_classvariable(L, "trainCarriageConfigIndex", SetTrainCarriageConfigIndex, GetTrainCarriageConfigIndex);
			lua_classvariable(L, "trainLinkedToBackwardId", nullptr, GetTrainLinkedToBackwardId);
			lua_classvariable(L, "trainLinkedToForwardId", nullptr, GetTrainLinkedToForwardId);
	#else
			lua_classfunction(L, "getWheelSpeed", GetWheelSpeed);
			lua_classfunction(L, "getCurrentGear", GetCurrentGear);
			lua_classfunction(L, "getCurrentRPM", GetCurrentRPM);
			lua_classfunction(L, "getSpeedVector", GetSpeedVector);

			lua_classfunction(L, "isHandlingModified", IsHandlingModified);
			lua_classfunction(L, "getHandling", GetHandling);
			lua_classfunction(L, "resetHandling", ResetHandling);

			lua_classvariable(L, "modKit", nullptr, GetModKit);
			lua_classvariable(L, "primaryColor", nullptr, GetPrimaryColor);
			lua_classvariable(L, "secondaryColor", nullptr, GetSecondaryColor);
			lua_classvariable(L, "secondaryColorRGB", nullptr, GetSecondaryColorRGB);
			lua_classvariable(L, "pearlColor", nullptr, GetPearlColor);
			lua_classvariable(L, "wheelColor", nullptr, GetWheelColor);
			lua_classvariable(L, "interiorColor", nullptr, GetInteriorColor);
			lua_classvariable(L, "dashboardColor", nullptr, GetDashboardColor);
			lua_classvariable(L, "tireSmokeColor", nullptr, GetTireSmokeColor);
			//lua_classvariable(L, "rearWheels", nullptr, nullptr);
			lua_classvariable(L, "customTires", nullptr, GetCustomTires);
			lua_classvariable(L, "specialDarkness", nullptr, GetSpecialDarkness);
			lua_classvariable(L, "numberplateIndex", nullptr, GetNumberplateIndex);
			lua_classvariable(L, "numberplateText", nullptr, GetNumberplateText);
			lua_classvariable(L, "windowTint", nullptr, GetWindowTint);
			lua_classvariable(L, "dirtLevel", nullptr, GetDirtLevel);
			lua_classvariable(L, "neonColor", nullptr, GetNeonColor);
			lua_classvariable(L, "livery", nullptr, GetLivery);
			lua_classvariable(L, "roofLivery", nullptr, GetRoofLivery);
			//lua_classvariable(L, "engineOn", nullptr, nullptr);
			lua_classvariable(L, "headlightColor", nullptr, GetHeadlightColor);
			lua_classvariable(L, "radioStationIndex", nullptr, GetRadioStationIndex);
			lua_classvariable(L, "sirenActive", nullptr, IsSirenActive);
			lua_classvariable(L, "lockState", nullptr, GetLockState);
			lua_classvariable(L, "doorState", nullptr, GetDoorState);
			lua_classvariable(L, "roof", nullptr, GetRoofState);
			lua_classvariable(L, "lightsMultiplier", nullptr, GetLightsMultiplier);
			lua_classvariable(L, "engineHealth", nullptr, GetEngineHealth);
			lua_classvariable(L, "petrolTankHealth", nullptr, GetPetrolTankHealth);
			lua_classvariable(L, "bodyHealth", nullptr, GetBodyHealth);
			lua_classvariable(L, "bodyAdditionalHealth", nullptr, GetBodyAdditionalHealth);
			lua_classvariable(L, "manualEngineControl", nullptr, IsManualEngineControl);
			lua_classvariable(L, "appearanceDataBase64", nullptr, GetAppearanceDataBase64);
			lua_classvariable(L, "gameStateBase64", nullptr, GetGameStateBase64);
			lua_classvariable(L, "healthDataBase64", nullptr, GetHealthDataBase64);
			lua_classvariable(L, "damageDataBase64", nullptr, GetDamageDataBase64);
			lua_classvariable(L, "scriptDataBase64", nullptr, GetScriptDataBase64);

			lua_classvariable(L, "wheelSpeed", nullptr, GetWheelSpeed);
			lua_classvariable(L, "currentGear", nullptr, GetCurrentGear);
			lua_classvariable(L, "currentRPM", nullptr, GetCurrentRPM);
			lua_classvariable(L, "speedVector", nullptr, GetSpeedVector);
			lua_classvariable(L, "maxGear", SetMaxGear, GetMaxGear);

			lua_classvariable(L, "handling", nullptr, GetHandling);

			lua_classvariable(L, "indicatorLights", SetLightsIndicator, GetLightsIndicator);
	#endif

			lua_classvariable(L, "destroyed", nullptr, IsDestroyed);
			lua_classvariable(L, "driver", nullptr, GetDriver);
			lua_classvariable(L, "modKitsCount", nullptr, GetModKitsCount);
			lua_classvariable(L, "wheelType", nullptr, GetWheelType);
			lua_classvariable(L, "wheelVariation", nullptr, GetWheelVariation);
			lua_classvariable(L, "rearWheelVariation", nullptr, GetRearWheelVariation);
			lua_classvariable(L, "handbrakeActive", nullptr, IsHandbrakeActive);
			lua_classvariable(L, "daylightOn", nullptr, IsDaylightOn);
			lua_classvariable(L, "nightlightOn", nullptr, IsNightlightOn);
			lua_classvariable(L, "flamethrowerActive", nullptr, IsFlamethrowerActive);
			lua_classvariable(L, "wheelsCount", nullptr, GetWheelsCount);
			lua_classvariable(L, "repairsCount", nullptr, GetRepairsCount);
			lua_classvariable(L, "armoredWindows", nullptr, HasArmoredWindows);
			lua_classvariable(L, "all", nullptr, ipairs);
		}
		lua_endclass(L);

		lua_newtable(L);
		for (auto vehicle : VehicleModels::Instance().GetVehicleInfosByHash())
		{
			lua_pushnumber(L, vehicle.first);
			lua_pushstring(L, vehicle.second->vehicleName);
			lua_rawset(L, -3);

			lua_pushstring(L, vehicle.second->vehicleName);
			lua_pushnumber(L, vehicle.first);
			lua_rawset(L, -3);
		}
		lua_setglobal(L, "vehicleModel");

		DEBUG_INFO("Vehicle::Init ...done");
	}

	/*int Vehicle::destroy(lua_State* L)
	{
		alt::IVehicle* vehicle = nullptr;

		//lua_stacktrace(L, "destroy");

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (!argReader.HasAnyError())
		{
			//delete vehicle;
			Core->DestroyBaseObject(vehicle);

	#ifndef NDEBUG
			Core->LogInfo("Vehicle garbage collected!");
	#endif

			lua_pushboolean(L, true);
			return 1;
		}

		argReader.GetErrorMessages();

		DEBUG_INFO("Vehicle failed to destroyed");

		lua_pushboolean(L, false);
		return 1;
	}*/

	int Vehicle::next(lua_State* L)
	{
		Core->LogInfo("Vehicle::next");

		return 0;
	}

	int Vehicle::pairs(lua_State* L)
	{
		return 0;
	}

	int Vehicle::ipairs(lua_State* L)
	{
		lua_newtable(L);
		auto allVehicle = alt::ICore::Instance().GetVehicles();
		for (size_t i = 0; i < allVehicle.GetSize(); i++)
		{
			lua_pushnumber(L, (int)(i + 1));
			lua_pushbaseobject(L, allVehicle[i].Get());
			lua_rawset(L, -3);
		}

		return 1;
	}

	int Vehicle::tostring(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaScriptRuntime* runtime = &LuaScriptRuntime::Instance();
		auto vehModels = &VehicleModels::Instance();

		std::string type("userdata:" + runtime->GetBaseObjectType(vehicle) + ":" + vehModels->GetVehicleInfo(vehicle->GetModel())->vehicleName);

		lua_pushstring(L, type.c_str());

		return 1;
	}

	#ifdef ALT_SERVER_API
	int Vehicle::CreateVehicle(lua_State* L)
	{
		uint32_t modelHash;
		std::string modelStr;
		alt::Position position;
		alt::Rotation rotation;

		ArgumentReader argReader(L);
		if(argReader.IsCurrentType(LUA_TNUMBER))
			argReader.ReadNumber(modelHash);
		else if (argReader.IsCurrentType(LUA_TSTRING))
		{
			argReader.ReadString(modelStr);
			modelHash = Core->Hash(modelStr);
		}
		argReader.ReadVector(position);
		argReader.ReadVector(rotation);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		/*argReader.ReadNumber(position[0]);
		argReader.ReadNumber(position[1]);
		argReader.ReadNumber(position[2]);

		argReader.ReadNumber(rotation[0]);
		argReader.ReadNumber(rotation[1]);
		argReader.ReadNumber(rotation[2]);*/

		//alt::Position pos(position[0], position[1], position[2]);
		//alt::Rotation rot(rotation[0], rotation[1], rotation[2]);

		alt::Ref<alt::IVehicle> vehicle = Core->CreateVehicle(
			modelHash,
			position,
			rotation
		);

		if (vehicle.Get() != nullptr)
		{
			lua_pushbaseobject(L, vehicle.Get());

			auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
			resourceImpl->AddEntity(vehicle.Get());
		}
		else
			lua_pushnil(L);

	#ifdef _DEBUG
		Core->LogInfo("Vehicle(" + std::to_string(modelHash) + ", {"+ std::to_string(position.x) +", "+ std::to_string(position.y) +", "+ std::to_string(position.z) +"}, {" + std::to_string(rotation.roll) + ", " + std::to_string(rotation.pitch) + ", " + std::to_string(rotation.yaw) + "})");
	#endif

		return 1;
	}

	int Vehicle::SetMod(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int category;
		int id;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(category);
		argReader.ReadNumber(id);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->SetMod(category, id));

		return 1;
	}

	int Vehicle::SetModKit(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int id;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(id);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->SetModKit(id));

		return 1;
	}

	int Vehicle::SetPrimaryColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetPrimaryColor(color.toInt());

		return 0;
	}

	int Vehicle::SetPrimaryColorRGB(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetPrimaryColorRGB(color);

		return 0;
	}

	int Vehicle::SetSecondaryColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetSecondaryColor(color.toInt());

		return 0;
	}

	int Vehicle::SetSecondaryColorRGB(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetSecondaryColorRGB(color);

		return 0;
	}

	int Vehicle::SetPearlColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetPearlColor(color.toInt());

		return 0;
	}

	int Vehicle::SetWheelColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheelColor(color.toInt());

		return 0;
	}

	int Vehicle::SetInteriorColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetInteriorColor(color.toInt());

		return 0;
	}

	int Vehicle::SetDashboardColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetDashboardColor(color.toInt());

		return 0;
	}

	int Vehicle::SetTireSmokeColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTireSmokeColor(color);

		return 0;
	}

	int Vehicle::SetWheels(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int type;
		int variation;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(type);
		argReader.ReadNumber(variation);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheels(type, variation);

		return 0;
	}

	int Vehicle::SetRearWheels(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int variation;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(variation);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetRearWheels(variation);

		return 0;
	}

	int Vehicle::SetCustomTires(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetCustomTires(state);

		return 0;
	}

	int Vehicle::SetSpecialDarkness(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetSpecialDarkness(value);

		return 0;
	}

	int Vehicle::SetNumberplateIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int index;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(index);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetNumberplateIndex(index);

		return 0;
	}

	int Vehicle::SetNumberplateText(lua_State* L)
	{
		alt::IVehicle* vehicle;
		std::string text;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadString(text);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetNumberplateText(text);

		return 0;
	}

	int Vehicle::SetWindowTint(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int tint;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(tint);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWindowTint(tint);

		return 0;
	}

	int Vehicle::SetDirtLevel(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int level;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(level);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetDirtLevel(level);

		return 0;
	}

	int Vehicle::ToggleExtra(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int extra;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(extra);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->ToggleExtra(extra, state);

		return 0;
	}

	int Vehicle::SetNeonActive(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool left, right, front, back;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(left);
		argReader.ReadBool(right);
		argReader.ReadBool(front);
		argReader.ReadBool(back);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetNeonActive(left, right, front, back);

		return 0;
	}

	int Vehicle::SetNeonColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetNeonColor(color);

		return 0;
	}

	int Vehicle::SetLivery(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int livery;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(livery);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetLivery(livery);

		return 0;
	}

	int Vehicle::SetRoofLivery(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int roofLivery;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(roofLivery);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetRoofLivery(roofLivery);

		return 0;
	}

	int Vehicle::LoadAppearanceDataFromBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;
		std::string appearance;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadString(appearance);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->LoadAppearanceDataFromBase64(appearance);

		return 0;
	}

	int Vehicle::SetEngineOn(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetEngineOn(state);

		return 0;
	}

	int Vehicle::SetHeadlightColor(lua_State* L)
	{
		alt::IVehicle* vehicle;
		alt::RGBA color;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadRGBA(color);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetHeadlightColor(color.toInt());

		return 0;
	}

	int Vehicle::SetRadioStationIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int stationIndex;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(stationIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetRadioStationIndex(stationIndex);

		return 0;
	}

	int Vehicle::SetLockState(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetLockState(state);

		return 0;
	}

	int Vehicle::SetSirenActive(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetSirenActive(state);

		return 0;
	}

	int Vehicle::SetDoorState(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int doorId;
		int state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(doorId);
		argReader.ReadNumber(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetDoorState(doorId, state);

		return 0;
	}

	int Vehicle::SetWindowOpened(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWindowOpened(windowId, state);

		return 0;
	}

	int Vehicle::SetRoofState(lua_State* L)
	{
		alt::IVehicle* vehicle;
		uint8_t state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetRoofState(state);

		return 0;
	}

	int Vehicle::SetLightsMultiplier(lua_State* L)
	{
		alt::IVehicle* vehicle;
		float multiplier;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(multiplier);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetLightsMultiplier(multiplier);

		return 0;
	}

	int Vehicle::LoadGameStateFromBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;
		std::string base64;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadString(base64);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->LoadGameStateFromBase64(base64);

		return 0;
	}

	int Vehicle::SetEngineHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int health;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(health);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetEngineHealth(health);

		return 0;
	}

	int Vehicle::SetPetrolTankHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int health;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(health);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetPetrolTankHealth(health);

		return 0;
	}

	int Vehicle::SetWheelBurst(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheelBurst(wheelId, state);

		return 0;
	}

	int Vehicle::SetWheelHasTire(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheelHasTire(wheelId, state);

		return 0;
	}

	int Vehicle::SetWheelDetached(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheelDetached(wheelId, state);

		return 0;
	}

	int Vehicle::SetWheelOnFire(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheelOnFire(wheelId, state);

		return 0;
	}

	int Vehicle::SetWheelHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;
		float health;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);
		argReader.ReadNumber(health);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWheelHealth(wheelId, health);

		return 0;
	}

	int Vehicle::SetBodyHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int health;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(health);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetBodyHealth(health);

		return 0;
	}

	int Vehicle::SetBodyAdditionalHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int health;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(health);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetBodyAdditionalHealth(health);

		return 0;
	}

	int Vehicle::LoadHealthDataFromBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;
		std::string base64;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadString(base64);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->LoadHealthDataFromBase64(base64);

		return 0;
	}

	int Vehicle::SetPartDamageLevel(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int partId;
		int damage;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(partId);
		argReader.ReadNumber(damage);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetPartDamageLevel(partId, damage);

		return 0;
	}

	int Vehicle::SetPartBulletHoles(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int partId;
		int shootsCount;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(partId);
		argReader.ReadNumber(shootsCount);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetPartBulletHoles(partId, shootsCount);

		return 0;
	}

	int Vehicle::SetLightDamaged(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int lightId;
		bool isDamaged;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(lightId);
		argReader.ReadBool(isDamaged);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetLightDamaged(lightId, isDamaged);

		return 0;
	}

	int Vehicle::SetWindowDamaged(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;
		bool isDamaged;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);
		argReader.ReadBool(isDamaged);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetWindowDamaged(windowId, isDamaged);

		return 0;
	}

	int Vehicle::SetSpecialLightDamaged(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int specialLightId;
		bool isDamaged;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(specialLightId);
		argReader.ReadBool(isDamaged);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetSpecialLightDamaged(specialLightId, isDamaged);

		return 0;
	}

	int Vehicle::SetArmoredWindowHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;
		float health;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);
		argReader.ReadNumber(health);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetArmoredWindowHealth(windowId, health);

		return 0;
	}

	int Vehicle::SetArmoredWindowShootCount(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;
		int count;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);
		argReader.ReadNumber(count);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetArmoredWindowShootCount(windowId, count);

		return 0;
	}

	int Vehicle::SetBumperDamageLevel(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int bumperId;
		int damageLevel;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(bumperId);
		argReader.ReadNumber(damageLevel);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetBumperDamageLevel(bumperId, damageLevel);

		return 0;
	}

	int Vehicle::LoadDamageDataFromBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;
		std::string base64;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadString(base64);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->LoadDamageDataFromBase64(base64);

		return 0;
	}

	int Vehicle::SetManualEngineControl(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetManualEngineControl(state);

		return 0;
	}

	int Vehicle::LoadScriptDataFromBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;
		std::string base64;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadString(base64);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->LoadScriptDataFromBase64(base64);

		return 0;
	}

	int Vehicle::Repair(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetFixed();

		return 0;
	}

	int Vehicle::GetAttached(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, vehicle->GetAttached().Get());

		return 1;
	}

	int Vehicle::GetAttachedTo(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, vehicle->GetAttachedTo().Get());

		return 1;
	}

	int Vehicle::IsDriftMode(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsDriftMode());

		return 1;
	}

	int Vehicle::SetDriftMode(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetDriftMode(state);

		return 0;
	}

	int Vehicle::IsTrainMissionTrain(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsTrainMissionTrain());

		return 1;
	}

	int Vehicle::SetTrainMissionTrain(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainMissionTrain(value);

		return 0;
	}

	int Vehicle::GetTrainTrackId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetTrainTrackId());

		return 1;
	}

	int Vehicle::SetTrainTrackId(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int8_t value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainTrackId(value);

		return 0;
	}

	int Vehicle::GetTrainEngineId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		if (vehicle->GetTrainEngineId().Get() != nullptr)
			lua_pushbaseobject(L, vehicle->GetTrainEngineId());
		else
			lua_pushnil(L);

		return 1;
	}

	int Vehicle::SetTrainEngineId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainEngineId(vehicle);

		return 0;
	}

	int Vehicle::GetTrainConfigIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetTrainConfigIndex());

		return 1;
	}

	int Vehicle::SetTrainConfigIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int8_t trainConfigIndex;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(trainConfigIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainConfigIndex(trainConfigIndex);

		return 0;
	}

	int Vehicle::GetTrainDistanceFromEngine(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetTrainDistanceFromEngine());

		return 1;
	}

	int Vehicle::SetTrainDistanceFromEngine(lua_State* L)
	{
		alt::IVehicle* vehicle;
		float distanceFromEngine;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(distanceFromEngine);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainDistanceFromEngine(distanceFromEngine);

		return 0;
	}

	int Vehicle::IsTrainEngine(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsTrainEngine());

		return 1;
	}

	int Vehicle::SetTrainIsEngine(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool isEngine;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(isEngine);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainIsEngine(isEngine);

		return 0;
	}

	int Vehicle::IsTrainCaboose(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsTrainCaboose());

		return 1;
	}

	int Vehicle::SetTrainIsCaboose(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool isCaboose;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(isCaboose);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainIsCaboose(isCaboose);

		return 0;
	}

	int Vehicle::GetTrainDirection(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->GetTrainDirection());

		return 1;
	}

	int Vehicle::SetTrainDirection(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool direction;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(direction);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainDirection(direction);

		return 0;
	}

	int Vehicle::HasTrainPassengerCarriages(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->HasTrainPassengerCarriages());

		return 1;
	}

	int Vehicle::SetTrainHasPassengerCarriages(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool hasPassengerCarriages;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(hasPassengerCarriages);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainHasPassengerCarriages(hasPassengerCarriages);

		return 0;
	}

	int Vehicle::GetTrainRenderDerailed(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->GetTrainRenderDerailed());

		return 1;
	}

	int Vehicle::SetTrainRenderDerailed(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool renderDerailed;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(renderDerailed);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainRenderDerailed(renderDerailed);

		return 0;
	}

	int Vehicle::GetTrainForceDoorsOpen(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->GetTrainForceDoorsOpen());

		return 1;
	}

	int Vehicle::SetTrainForceDoorsOpen(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool forceDoorsOpen;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(forceDoorsOpen);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainForceDoorsOpen(forceDoorsOpen);

		return 0;
	}

	int Vehicle::GetTrainCruiseSpeed(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetTrainCruiseSpeed());

		return 1;
	}

	int Vehicle::SetTrainCruiseSpeed(lua_State* L)
	{
		alt::IVehicle* vehicle;
		float cruiseSpeed;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(cruiseSpeed);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainCruiseSpeed(cruiseSpeed);

		return 0;
	}

	int Vehicle::GetTrainCarriageConfigIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetTrainCarriageConfigIndex());

		return 1;
	}

	int Vehicle::SetTrainCarriageConfigIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int8_t carriageConfigIndex;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(carriageConfigIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetTrainCarriageConfigIndex(carriageConfigIndex);

		return 0;
	}

	int Vehicle::GetTrainLinkedToBackwardId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		if (vehicle->GetTrainLinkedToBackwardId().Get() != nullptr)
			lua_pushbaseobject(L, vehicle->GetTrainLinkedToBackwardId());
		else
			lua_pushnil(L);

		return 1;
	}

	int Vehicle::SetTrainLinkedToBackwardId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::IVehicle* tempVehicle = nullptr;
		if(argReader.IsNextType(LUA_TUSERDATA))
			argReader.ReadBaseObject(tempVehicle);

		vehicle->SetTrainLinkedToBackwardId(tempVehicle);

		return 0;
	}

	int Vehicle::GetTrainLinkedToForwardId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		if (vehicle->GetTrainLinkedToForwardId().Get() != nullptr)
			lua_pushbaseobject(L, vehicle->GetTrainLinkedToForwardId());
		else
			lua_pushnil(L);

		return 1;
	}

	int Vehicle::SetTrainLinkedToForwardId(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::IVehicle* tempVehicle = nullptr;
		if (argReader.IsNextType(LUA_TUSERDATA))
			argReader.ReadBaseObject(tempVehicle);

		vehicle->SetTrainLinkedToForwardId(tempVehicle);

		return 0;
	}

	int Vehicle::IsBoatAnchorActive(lua_State* L)
	{
		alt::IVehicle* vehicle;
		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsBoatAnchorActive());

		return 1;
	}
	
	int Vehicle::SetBoatAnchorActive(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetBoatAnchorActive(state);

		return 0;
	}

	int Vehicle::SetSearchLight(lua_State* L)
	{
		alt::IVehicle* vehicle;
		bool state;
		alt::IVehicle* spottedEntity;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadBool(state);
		argReader.ReadBaseObject(spottedEntity);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetSearchLight(state, spottedEntity);

		return 0;
	}

	#else
	int Vehicle::GetWheelSpeed(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWheelSpeed());

		return 1;
	}

	int Vehicle::GetCurrentGear(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetCurrentGear());

		return 1;
	}

	int Vehicle::GetCurrentRPM(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetCurrentRPM());

		return 1;
	}

	int Vehicle::GetSpeedVector(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector3(L, vehicle->GetSpeedVector());

		return 1;
	}

	int Vehicle::IsHandlingModified(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsHandlingModified());

		return 1;
	}

	int Vehicle::GetHandling(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->ReplaceHandling();
		lua_pushhandlingdata(L, vehicle->GetHandling().Get());

		return 1;
	}

	int Vehicle::ResetHandling(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->ResetHandling();

		return 0;
	}

	int Vehicle::ReplaceHandling(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->ReplaceHandling();

		return 0;
	}

	int Vehicle::GetMaxGear(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetMaxGear());

		return 1;
	}

	int Vehicle::SetCurrentGear(lua_State* L)
	{
		alt::IVehicle* vehicle;
		uint16_t currentGear;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(currentGear);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetCurrentGear(currentGear);

		return 0;
	}

	int Vehicle::SetMaxGear(lua_State* L)
	{
		alt::IVehicle* vehicle;
		uint16_t gearMax;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(gearMax);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetMaxGear(gearMax);

		return 0;
	}

	int Vehicle::GetLightsIndicator(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetLightsIndicator());

		return 1;
	}

	int Vehicle::SetLightsIndicator(lua_State* L)
	{
		alt::IVehicle* vehicle;
		uint8_t lightsIndicatorFlag;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(lightsIndicatorFlag);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		vehicle->SetLightsIndicator(lightsIndicatorFlag);

		return 0;
	}

	#endif

	int Vehicle::GetDriver(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, vehicle->GetDriver().Get());

		return 1;
	}

	int Vehicle::IsDestroyed(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsDestroyed());

		return 1;
	}

	int Vehicle::GetMod(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int category;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(category);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetMod(category));

		return 1;
	}

	int Vehicle::GetModsCount(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int category;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(category);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetModsCount(category));

		return 1;
	}

	int Vehicle::GetModKitsCount(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetModKitsCount());

		return 1;
	}

	int Vehicle::GetModKit(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetModKit());

		return 1;
	}

	int Vehicle::IsPrimaryColorRGB(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsPrimaryColorRGB());

		return 1;
	}

	int Vehicle::GetPrimaryColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->GetPrimaryColor());

		return 1;
	}

	int Vehicle::GetPrimaryColorRGB(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushrgba(L, vehicle->GetPrimaryColorRGB());

		return 1;
	}

	int Vehicle::IsSecondaryColorRGB(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsSecondaryColorRGB());

		return 1;
	}

	int Vehicle::GetSecondaryColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetSecondaryColor());

		return 1;
	}

	int Vehicle::GetSecondaryColorRGB(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushrgba(L, vehicle->GetSecondaryColorRGB());

		return 1;
	}

	int Vehicle::GetPearlColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetPearlColor());

		return 1;
	}

	int Vehicle::GetWheelColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWheelColor());

		return 1;
	}

	int Vehicle::GetInteriorColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetInteriorColor());

		return 1;
	}

	int Vehicle::GetDashboardColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetDashboardColor());

		return 1;
	}

	int Vehicle::IsTireSmokeColorCustom(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsTireSmokeColorCustom());

		return 1;
	}

	int Vehicle::GetTireSmokeColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushrgba(L, vehicle->GetTireSmokeColor());

		return 1;
	}

	int Vehicle::GetWheelType(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWheelType());

		return 1;
	}

	int Vehicle::GetWheelVariation(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWheelVariation());

		return 1;
	}

	int Vehicle::GetRearWheelVariation(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetRearWheelVariation());

		return 1;
	}

	int Vehicle::GetCustomTires(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->GetCustomTires());

		return 1;
	}

	int Vehicle::GetSpecialDarkness(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetSpecialDarkness());

		return 1;
	}

	int Vehicle::GetNumberplateIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetNumberplateIndex());

		return 1;
	}

	int Vehicle::GetNumberplateText(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, vehicle->GetNumberplateText());

		return 1;
	}

	int Vehicle::GetWindowTint(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWindowTint());

		return 1;
	}

	int Vehicle::GetDirtLevel(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetDirtLevel());

		return 1;
	}

	int Vehicle::IsExtraOn(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int extraId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(extraId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsExtraOn(extraId));

		return 1;
	}

	int Vehicle::IsNeonActive(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsNeonActive());

		return 1;
	}

	int Vehicle::GetNeonActive(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		bool left, right, front, back;
		vehicle->GetNeonActive(&left, &right, &front, &back);
	
		lua_pushboolean(L, left);
		lua_pushboolean(L, right);
		lua_pushboolean(L, front);
		lua_pushboolean(L, back);

		return 4;
	}

	int Vehicle::GetNeonColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushrgba(L, vehicle->GetNeonColor());

		return 1;
	}

	int Vehicle::GetLivery(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetLivery());

		return 1;
	}

	int Vehicle::GetRoofLivery(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetRoofLivery());

		return 1;
	}

	int Vehicle::GetAppearanceDataBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, vehicle->GetAppearanceDataBase64());

		return 1;
	}

	////vehicle game state
	int Vehicle::IsEngineOn(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsEngineOn());

		return 1;
	}

	int Vehicle::IsHandbrakeActive(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsHandbrakeActive());

		return 1;
	}

	int Vehicle::GetHeadlightColor(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetHeadlightColor());

		return 1;
	}

	int Vehicle::GetRadioStationIndex(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetRadioStationIndex());

		return 0;
	}

	int Vehicle::IsSirenActive(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsSirenActive());

		return 1;
	}

	//// TODO document available values. Enum?
	int Vehicle::GetLockState(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetLockState());

		return 1;
	}

	//// TODO document available values. Enum?
	int Vehicle::GetDoorState(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int doorId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(doorId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetDoorState(doorId));

		return 1;
	}

	int Vehicle::IsWindowOpened(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsWindowOpened(windowId));

		return 1;
	}

	int Vehicle::IsDaylightOn(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsDaylightOn());

		return 1;
	}

	int Vehicle::IsNightlightOn(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsNightlightOn());

		return 1;
	}

	int Vehicle::GetRoofState(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetRoofState());

		return 1;
	}

	int Vehicle::IsFlamethrowerActive(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsFlamethrowerActive());

		return 1;
	}

	int Vehicle::GetLightsMultiplier(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetLightsMultiplier());

		return 1;
	}

	int Vehicle::GetGameStateBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, vehicle->GetGameStateBase64());

		return 1;
	}

	////vehicle health
	int Vehicle::GetEngineHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetEngineHealth());

		return 1;
	}

	int Vehicle::GetPetrolTankHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetPetrolTankHealth());

		return 1;
	}

	int Vehicle::GetWheelsCount(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWheelsCount());

		return 1;
	}

	int Vehicle::IsWheelBurst(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsWheelBurst(wheelId));

		return 1;
	}

	int Vehicle::DoesWheelHasTire(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->DoesWheelHasTire(wheelId));

		return 1;
	}

	int Vehicle::IsWheelDetached(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsWheelDetached(wheelId));

		return 1;
	}

	int Vehicle::IsWheelOnFire(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsWheelOnFire(wheelId));

		return 1;
	}

	int Vehicle::GetWheelHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int wheelId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(wheelId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetWheelHealth(wheelId));

		return 1;
	}

	int Vehicle::GetRepairsCount(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetRepairsCount());

		return 1;
	}

	//// Will be moved to event
	////int<IEntity> GetLastAttacker(lua_State* L);
	////int Vehicle::GetLastDamagedWith(lua_State* L);

	int Vehicle::GetBodyHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetBodyHealth());

		return 1;
	}

	int Vehicle::GetBodyAdditionalHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetBodyAdditionalHealth());

		return 1;
	}

	int Vehicle::GetHealthDataBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, vehicle->GetHealthDataBase64());

		return 1;
	}

	//// vehicle damage
	int Vehicle::GetPartDamageLevel(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int partId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(partId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetPartDamageLevel(partId));

		return 1;
	}

	int Vehicle::GetPartBulletHoles(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int partId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(partId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetPartBulletHoles(partId));

		return 1;
	}

	int Vehicle::IsLightDamaged(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int lightId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(lightId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsLightDamaged(lightId));

		return 1;
	}

	int Vehicle::IsWindowDamaged(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsWindowDamaged(windowId));

		return 1;
	}

	int Vehicle::IsSpecialLightDamaged(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int specialLightId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(specialLightId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsSpecialLightDamaged(specialLightId));

		return 1;
	}

	int Vehicle::HasArmoredWindows(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->HasArmoredWindows());

		return 1;
	}

	int Vehicle::GetArmoredWindowHealth(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetArmoredWindowHealth(windowId));

		return 1;
	}

	int Vehicle::GetArmoredWindowShootCount(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int windowId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(windowId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetArmoredWindowShootCount(windowId));

		return 1;
	}

	int Vehicle::GetBumperDamageLevel(lua_State* L)
	{
		alt::IVehicle* vehicle;
		int bumperId;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);
		argReader.ReadNumber(bumperId);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, vehicle->GetBumperDamageLevel(bumperId));

		return 1;
	}

	int Vehicle::GetDamageDataBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, vehicle->GetDamageDataBase64());

		return 1;
	}

	////vehicle script data
	int Vehicle::IsManualEngineControl(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, vehicle->IsManualEngineControl());

		return 1;
	}

	int Vehicle::GetScriptDataBase64(lua_State* L)
	{
		alt::IVehicle* vehicle;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(vehicle);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, vehicle->GetScriptDataBase64());

		return 1;
	}

	//
	//int Vehicle::IsDestroyed(lua_State* L);

	//int Vehicle::SetVehiclePosition(lua_State* L)
	//{
	//	alt::IVehicle *vehicle;
	//	alt::Position position;
	//
	//	ArgumentReader argReader(L);
	//	argReader.ReadBaseObject(vehicle);
	//	argReader.ReadVector(position);
	//
	//	if (argReader.HasAnyError())
	//	{
	//		argReader.GetErrorMessages();
	//		return 0;
	//	}
	//
	//	vehicle->SetPosition(position);
	//
	//#ifdef _DEBUG
	//	Core->LogInfo("SetVehiclePosition("+std::to_string(vehicle->GetModel())+", {" + std::to_string(position.x) + ", "+ std::to_string(position.y) +", "+ std::to_string(position.z) +"})");
	//#endif
	//
	//	lua_pushboolean(L, 1);
	//
	//	return 1;
	//}

	//int Vehicle::GetVehiclePosition(lua_State* L)
	//{
	//	alt::IVehicle* vehicle;
	//	alt::Position position;
	//
	//	ArgumentReader argReader(L);
	//	argReader.ReadBaseObject(vehicle);
	//
	//	if (argReader.HasAnyError())
	//	{
	//		argReader.GetErrorMessages();
	//		return 0;
	//	}
	//
	//	position = vehicle->GetPosition();
	//	Vector3fp* t = new Vector3fp(position);
	//
	//#ifdef _DEBUG
	//	printf("GetPosition: %p\n", t);
	//#endif
	//
	//	//lua_userdata(L, "Vector3", t, false);
	//
	//	return 1;
	//}
}

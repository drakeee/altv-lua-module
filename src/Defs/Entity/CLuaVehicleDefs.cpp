#include "Main.h"

const char* CLuaVehicleDefs::ClassName = "Vehicle";
void CLuaVehicleDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "createVehicle", CreateVehicle);
	lua_globalfunction(L, "getVehicleDriver", GetDriver);
	lua_globalfunction(L, "isVehicleDestroyed", IsDestroyed);

	lua_globalfunction(L, "getVehicleMod", GetMod);
	lua_globalfunction(L, "getVehicleModsCount", GetModsCount);
	lua_globalfunction(L, "setVehicleMod", SetMod);

	lua_globalfunction(L, "getVehicleModKitsCount", GetModKitsCount);
	lua_globalfunction(L, "getVehicleModKit", GetModKit);
	lua_globalfunction(L, "setVehicleModKit", SetModKit);

	lua_globalfunction(L, "isVehiclePrimaryColorRGB", IsPrimaryColorRGB);
	lua_globalfunction(L, "getVehiclePrimaryColor", GetPrimaryColor);
	lua_globalfunction(L, "getVehiclePrimaryColorRGB", GetPrimaryColorRGB);
	lua_globalfunction(L, "setVehiclePrimaryColor", SetPrimaryColor);
	lua_globalfunction(L, "setVehiclePrimaryColorRGB", SetPrimaryColorRGB);

	lua_globalfunction(L, "isVehicleSecondaryColorRGB", IsSecondaryColorRGB);
	lua_globalfunction(L, "getVehicleSecondaryColor", GetSecondaryColor);
	lua_globalfunction(L, "getVehicleSecondaryColorRGB", GetSecondaryColorRGB);
	lua_globalfunction(L, "setVehicleSecondaryColor", SetSecondaryColor);
	lua_globalfunction(L, "setVehicleSecondaryColorRGB", SetSecondaryColorRGB);

	lua_globalfunction(L, "getVehiclePearlColor", GetPearlColor);
	lua_globalfunction(L, "setVehiclePearlColor", SetPearlColor);

	lua_globalfunction(L, "getVehicleWheelColor", GetWheelColor);
	lua_globalfunction(L, "setVehicleWheelColor", SetWheelColor);

	lua_globalfunction(L, "getVehicleInteriorColor", GetInteriorColor);
	lua_globalfunction(L, "setVehicleInteriorColor", SetInteriorColor);

	lua_globalfunction(L, "getVehicleDashboardColor", GetDashboardColor);
	lua_globalfunction(L, "setVehicleDashboardColor", SetDashboardColor);

	lua_globalfunction(L, "isVehicleTireSmokeColorCustom", IsTireSmokeColorCustom);
	lua_globalfunction(L, "getVehicleTireSmokeColor", GetTireSmokeColor);
	lua_globalfunction(L, "setVehicleTireSmokeColor", SetTireSmokeColor);

	lua_globalfunction(L, "getVehicleWheelType", GetWheelType);
	lua_globalfunction(L, "getVehicleWheelVariation", GetWheelVariation);
	lua_globalfunction(L, "getVehicleRearWheelVariation", GetRearWheelVariation);
	lua_globalfunction(L, "setVehicleWheels", SetWheels);
	lua_globalfunction(L, "setVehicleRearWheels", SetRearWheels);

	lua_globalfunction(L, "getVehicleCustomTires", GetCustomTires);
	lua_globalfunction(L, "setVehicleCustomTires", SetCustomTires);

	lua_globalfunction(L, "getVehicleSpecialDarkness", GetSpecialDarkness);
	lua_globalfunction(L, "setVehicleSpecialDarkness", SetSpecialDarkness);

	lua_globalfunction(L, "getVehicleNumberplateIndex", GetNumberplateIndex);
	lua_globalfunction(L, "setVehicleNumberplateIndex", SetNumberplateIndex);

	lua_globalfunction(L, "getVehicleNumberplateText", GetNumberplateText);
	lua_globalfunction(L, "setVehicleNumberplateText", SetNumberplateText);

	lua_globalfunction(L, "getVehicleWindowTint", GetWindowTint);
	lua_globalfunction(L, "setVehicleWindowTint", SetWindowTint);

	lua_globalfunction(L, "getVehicleDirtLevel", GetDirtLevel);
	lua_globalfunction(L, "setVehicleDirtLevel", SetDirtLevel);

	lua_globalfunction(L, "isVehicleExtraOn", IsExtraOn);
	lua_globalfunction(L, "toggleVehicleExtra", ToggleExtra);

	lua_globalfunction(L, "isVehicleNeonActive", IsNeonActive);
	lua_globalfunction(L, "getVehicleNeonActive", GetNeonActive);
	lua_globalfunction(L, "setVehicleNeonActive", SetNeonActive);
	lua_globalfunction(L, "getVehicleNeonColor", GetNeonColor);
	lua_globalfunction(L, "setVehicleNeonColor", SetNeonColor);

	lua_globalfunction(L, "getVehicleLivery", GetLivery);
	lua_globalfunction(L, "setVehicleLivery", SetLivery);
	lua_globalfunction(L, "getVehicleRoofLivery", GetRoofLivery);
	lua_globalfunction(L, "setVehicleRoofLivery", SetRoofLivery);

	lua_globalfunction(L, "getVehicleAppearanceDataBase64", GetAppearanceDataBase64);
	lua_globalfunction(L, "loadVehicleAppearanceDataFromBase64", LoadAppearanceDataFromBase64);

	//vehicle game state
	lua_globalfunction(L, "isVehicleEngineOn", IsEngineOn);
	lua_globalfunction(L, "setVehicleEngineOn", SetEngineOn);

	lua_globalfunction(L, "isVehicleHandbrakeActive", IsHandbrakeActive);

	lua_globalfunction(L, "getVehicleHeadlightColor", GetHeadlightColor);
	lua_globalfunction(L, "setVehicleHeadlightColor", SetHeadlightColor);

	lua_globalfunction(L, "getVehicleRadioStationIndex", GetRadioStationIndex);
	lua_globalfunction(L, "setVehicleRadioStationIndex", SetRadioStationIndex);

	lua_globalfunction(L, "isVehicleSirenActive", IsSirenActive);
	lua_globalfunction(L, "setVehicleSirenActive", SetSirenActive);

	// TODO document available values. Enum?
	lua_globalfunction(L, "getVehicleLockState", GetLockState);
	lua_globalfunction(L, "setVehicleLockState", SetLockState);

	// TODO document available values. Enum?
	lua_globalfunction(L, "getVehicleDoorState", GetDoorState);
	lua_globalfunction(L, "setVehicleDoorState", SetDoorState);

	lua_globalfunction(L, "isVehicleWindowOpened", IsWindowOpened);
	lua_globalfunction(L, "setVehicleWindowOpened", SetWindowOpened);

	lua_globalfunction(L, "isVehicleDaylightOn", IsDaylightOn);
	lua_globalfunction(L, "isVehicleNightlightOn", IsNightlightOn);

	lua_globalfunction(L, "isVehicleRoofOpened", IsRoofOpened);
	lua_globalfunction(L, "setVehicleRoofOpened", SetRoofOpened);

	lua_globalfunction(L, "isVehicleFlamethrowerActive", IsFlamethrowerActive);

	lua_globalfunction(L, "getVehicleLightsMultiplier", GetLightsMultiplier);
	lua_globalfunction(L, "setVehicleLightsMultiplier", SetLightsMultiplier);

	lua_globalfunction(L, "getVehicleGameStateBase64", GetGameStateBase64);
	lua_globalfunction(L, "loadVehicleGameStateFromBase64", LoadGameStateFromBase64);

	//vehicle health
	lua_globalfunction(L, "getVehicleEngineHealth", GetEngineHealth);
	lua_globalfunction(L, "setVehicleEngineHealth", SetEngineHealth);

	lua_globalfunction(L, "getVehiclePetrolTankHealth", GetPetrolTankHealth);
	lua_globalfunction(L, "setVehiclePetrolTankHealth", SetPetrolTankHealth);

	lua_globalfunction(L, "getVehicleWheelsCount", GetWheelsCount);

	lua_globalfunction(L, "isVehicleWheelBurst", IsWheelBurst);
	lua_globalfunction(L, "setVehicleWheelBurst", SetWheelBurst);

	lua_globalfunction(L, "doesVehicleWheelHasTire", DoesWheelHasTire);
	lua_globalfunction(L, "setVehicleWheelHasTire", SetWheelHasTire);

	lua_globalfunction(L, "isVehicleWheelDetached", IsWheelDetached);
	lua_globalfunction(L, "setVehicleWheelDetached", SetWheelDetached);

	lua_globalfunction(L, "isVehicleWheelOnFire", IsWheelOnFire);
	lua_globalfunction(L, "setVehicleWheelOnFire", SetWheelOnFire);

	lua_globalfunction(L, "getVehicleWheelHealth", GetWheelHealth);
	lua_globalfunction(L, "setVehicleWheelHealth", SetWheelHealth);

	lua_globalfunction(L, "getVehicleRepairsCount", GetRepairsCount);

	// Will be moved to event
	//static int<IEntity> GetVehicleLastAttacker(lua_State* L);
	//static int GetVehicleLastDamagedWith(lua_State* L);

	lua_globalfunction(L, "getVehicleBodyHealth", GetBodyHealth);
	lua_globalfunction(L, "setVehicleBodyHealth", SetBodyHealth);
	lua_globalfunction(L, "getVehicleBodyAdditionalHealth", GetBodyAdditionalHealth);
	lua_globalfunction(L, "setVehicleBodyAdditionalHealth", SetBodyAdditionalHealth);

	lua_globalfunction(L, "getVehicleHealthDataBase64", GetHealthDataBase64);
	lua_globalfunction(L, "loadVehicleHealthDataFromBase64", LoadHealthDataFromBase64);

	// vehicle damage
	lua_globalfunction(L, "getVehiclePartDamageLevel", GetPartDamageLevel);
	lua_globalfunction(L, "setVehiclePartDamageLevel", SetPartDamageLevel);
	lua_globalfunction(L, "getVehiclePartBulletHoles", GetPartBulletHoles);
	lua_globalfunction(L, "setVehiclePartBulletHoles", SetPartBulletHoles);
	lua_globalfunction(L, "isVehicleLightDamaged", IsLightDamaged);
	lua_globalfunction(L, "setVehicleLightDamaged", SetLightDamaged);
	lua_globalfunction(L, "isVehicleWindowDamaged", IsWindowDamaged);
	lua_globalfunction(L, "setVehicleWindowDamaged", SetWindowDamaged);
	lua_globalfunction(L, "isVehicleSpecialLightDamaged", IsSpecialLightDamaged);
	lua_globalfunction(L, "setVehicleSpecialLightDamaged", SetSpecialLightDamaged);
	lua_globalfunction(L, "hasVehicleArmoredWindows", HasArmoredWindows);
	lua_globalfunction(L, "getVehicleArmoredWindowHealth", GetArmoredWindowHealth);
	lua_globalfunction(L, "setVehicleArmoredWindowHealth", SetArmoredWindowHealth);
	lua_globalfunction(L, "getVehicleArmoredWindowShootCount", GetArmoredWindowShootCount);
	lua_globalfunction(L, "setVehicleArmoredWindowShootCount", SetArmoredWindowShootCount);
	lua_globalfunction(L, "getVehicleBumperDamageLevel", GetBumperDamageLevel);
	lua_globalfunction(L, "setVehicleBumperDamageLevel", SetBumperDamageLevel);

	lua_globalfunction(L, "getVehicleDamageDataBase64", GetDamageDataBase64);
	lua_globalfunction(L, "loadVehicleDamageDataFromBase64", LoadDamageDataFromBase64);

	//vehicle script data
	lua_globalfunction(L, "setVehicleManualEngineControl", SetManualEngineControl);
	lua_globalfunction(L, "isVehicleManualEngineControl", IsManualEngineControl);

	lua_globalfunction(L, "getVehicleScriptDataBase64", GetScriptDataBase64);
	lua_globalfunction(L, "loadVehicleScriptDataFromBase64", LoadScriptDataFromBase64);
	//lua_globalfunction(L, "setVehiclePosition", SetVehiclePosition);
	//lua_globalfunction(L, "getVehiclePosition", GetVehiclePosition);

	lua_beginclass(L, ClassName, CLuaEntityDefs::ClassName);
	{
		lua_classmeta(L, "__gc", CLuaVehicleDefs::destroy);
		lua_classmeta(L, "__next", next);
		lua_classmeta(L, "__pairs", pairs);
		lua_classmeta(L, "__ipairs", ipairs);

		lua_classfunction(L, "new", "createVehicle");
		lua_classfunction(L, "getDriver", "getVehicleDriver");
		lua_classfunction(L, "isDestroyed", "isVehicleDestroyed");

		lua_classfunction(L, "getMod", "getVehicleMod");
		lua_classfunction(L, "getModsCount", "getVehicleModsCount");
		lua_classfunction(L, "setMod", "setVehicleMod");

		lua_classfunction(L, "getModKitsCount", "getVehicleModKitsCount");
		lua_classfunction(L, "getModKit", "getVehicleModKit");
		lua_classfunction(L, "setModKit", "setVehicleModKit");

		lua_classfunction(L, "isPrimaryColorRGB", "isVehiclePrimaryColorRGB");
		lua_classfunction(L, "getPrimaryColor", "getVehiclePrimaryColor");
		lua_classfunction(L, "getPrimaryColorRGB", "getVehiclePrimaryColorRGB");
		lua_classfunction(L, "setPrimaryColor", "setVehiclePrimaryColor");
		lua_classfunction(L, "setPrimaryColorRGB", "setVehiclePrimaryColorRGB");

		lua_classfunction(L, "isSecondaryColorRGB", "isVehicleSecondaryColorRGB");
		lua_classfunction(L, "getSecondaryColor", "getVehicleSecondaryColor");
		lua_classfunction(L, "getSecondaryColorRGB", "getVehicleSecondaryColorRGB");
		lua_classfunction(L, "setSecondaryColor", "setVehicleSecondaryColor");
		lua_classfunction(L, "setSecondaryColorRGB", "setVehicleSecondaryColorRGB");

		lua_classfunction(L, "getPearlColor", "getVehiclePearlColor");
		lua_classfunction(L, "setPearlColor", "setVehiclePearlColor");

		lua_classfunction(L, "getWheelColor", "getVehicleWheelColor");
		lua_classfunction(L, "setWheelColor", "setVehicleWheelColor");

		lua_classfunction(L, "getInteriorColor", "getVehicleInteriorColor");
		lua_classfunction(L, "setInteriorColor", "setVehicleInteriorColor");

		lua_classfunction(L, "getDashboardColor", "getVehicleDashboardColor");
		lua_classfunction(L, "setDashboardColor", "setVehicleDashboardColor");

		lua_classfunction(L, "isTireSmokeColorCustom", "isVehicleTireSmokeColorCustom");
		lua_classfunction(L, "getTireSmokeColor", "getVehicleTireSmokeColor");
		lua_classfunction(L, "setTireSmokeColor", "setVehicleTireSmokeColor");

		lua_classfunction(L, "getWheelType", "getVehicleWheelType");
		lua_classfunction(L, "getWheelVariation", "getVehicleWheelVariation");
		lua_classfunction(L, "getRearWheelVariation", "getVehicleRearWheelVariation");
		lua_classfunction(L, "setWheels", "setVehicleWheels");
		lua_classfunction(L, "setRearWheels", "setVehicleRearWheels");

		lua_classfunction(L, "getCustomTires", "getVehicleCustomTires");
		lua_classfunction(L, "setCustomTires", "setVehicleCustomTires");

		lua_classfunction(L, "getSpecialDarkness", "getVehicleSpecialDarkness");
		lua_classfunction(L, "setSpecialDarkness", "setVehicleSpecialDarkness");

		lua_classfunction(L, "getNumberplateIndex", "getVehicleNumberplateIndex");
		lua_classfunction(L, "setNumberplateIndex", "setVehicleNumberplateIndex");

		lua_classfunction(L, "getNumberplateText", "getVehicleNumberplateText");
		lua_classfunction(L, "setNumberplateText", "setVehicleNumberplateText");

		lua_classfunction(L, "getWindowTint", "getVehicleWindowTint");
		lua_classfunction(L, "setWindowTint", "setVehicleWindowTint");

		lua_classfunction(L, "getDirtLevel", "getVehicleDirtLevel");
		lua_classfunction(L, "setDirtLevel", "setVehicleDirtLevel");

		lua_classfunction(L, "isExtraOn", "isVehicleExtraOn");
		lua_classfunction(L, "toggleExtra", "toggleVehicleExtra");

		lua_classfunction(L, "isNeonActive", "isVehicleNeonActive");
		lua_classfunction(L, "getNeonActive", "getVehicleNeonActive");
		lua_classfunction(L, "setNeonActive", "setVehicleNeonActive");
		lua_classfunction(L, "getNeonColor", "getVehicleNeonColor");
		lua_classfunction(L, "setNeonColor", "setVehicleNeonColor");

		lua_classfunction(L, "getLivery", "getVehicleLivery");
		lua_classfunction(L, "setLivery", "setVehicleLivery");
		lua_classfunction(L, "getRoofLivery", "getVehicleRoofLivery");
		lua_classfunction(L, "setRoofLivery", "setVehicleRoofLivery");

		lua_classfunction(L, "getAppearanceDataBase64", "getVehicleAppearanceDataBase64");
		lua_classfunction(L, "loadAppearanceDataFromBase64", "loadVehicleAppearanceDataFromBase64");

		//vehicle game state
		lua_classfunction(L, "isEngineOn", "isVehicleEngineOn");
		lua_classfunction(L, "setEngineOn", "setVehicleEngineOn");

		lua_classfunction(L, "isHandbrakeActive", "isVehicleHandbrakeActive");

		lua_classfunction(L, "getHeadlightColor", "getVehicleHeadlightColor");
		lua_classfunction(L, "setHeadlightColor", "setVehicleHeadlightColor");

		lua_classfunction(L, "getRadioStationIndex", "getVehicleRadioStationIndex");
		lua_classfunction(L, "setRadioStationIndex", "setVehicleRadioStationIndex");

		lua_classfunction(L, "isSirenActive", "isVehicleSirenActive");
		lua_classfunction(L, "setSirenActive", "setVehicleSirenActive");

		// TODO document available values. Enum?
		lua_classfunction(L, "getLockState", "getVehicleLockState");
		lua_classfunction(L, "setLockState", "setVehicleLockState");

		// TODO document available values. Enum?
		lua_classfunction(L, "getDoorState", "getVehicleDoorState");
		lua_classfunction(L, "setDoorState", "setVehicleDoorState");

		lua_classfunction(L, "isWindowOpened", "isVehicleWindowOpened");
		lua_classfunction(L, "setWindowOpened", "setVehicleWindowOpened");

		lua_classfunction(L, "isDaylightOn", "isVehicleDaylightOn");
		lua_classfunction(L, "isNightlightOn", "isVehicleNightlightOn");

		lua_classfunction(L, "isRoofOpened", "isVehicleRoofOpened");
		lua_classfunction(L, "setRoofOpened", "setVehicleRoofOpened");

		lua_classfunction(L, "isFlamethrowerActive", "isVehicleFlamethrowerActive");

		lua_classfunction(L, "getLightsMultiplier", "getVehicleLightsMultiplier");
		lua_classfunction(L, "setLightsMultiplier", "setVehicleLightsMultiplier");

		lua_classfunction(L, "getGameStateBase64", "getVehicleGameStateBase64");
		lua_classfunction(L, "loadGameStateFromBase64", "loadVehicleGameStateFromBase64");

		//vehicle health
		lua_classfunction(L, "getEngineHealth", "getVehicleEngineHealth");
		lua_classfunction(L, "setEngineHealth", "setVehicleEngineHealth");

		lua_classfunction(L, "getPetrolTankHealth", "getVehiclePetrolTankHealth");
		lua_classfunction(L, "setPetrolTankHealth", "setVehiclePetrolTankHealth");

		lua_classfunction(L, "getWheelsCount", "getVehicleWheelsCount");

		lua_classfunction(L, "isWheelBurst", "isVehicleWheelBurst");
		lua_classfunction(L, "setWheelBurst", "setVehicleWheelBurst");

		lua_classfunction(L, "doesWheelHasTire", "doesVehicleWheelHasTire");
		lua_classfunction(L, "setWheelHasTire", "setVehicleWheelHasTire");

		lua_classfunction(L, "isWheelDetached", "isVehicleWheelDetached");
		lua_classfunction(L, "setWheelDetached", "setVehicleWheelDetached");

		lua_classfunction(L, "isWheelOnFire", "isVehicleWheelOnFire");
		lua_classfunction(L, "setWheelOnFire", "setVehicleWheelOnFire");

		lua_classfunction(L, "getWheelHealth", "getVehicleWheelHealth");
		lua_classfunction(L, "setWheelHealth", "setVehicleWheelHealth");

		lua_classfunction(L, "getRepairsCount", "getVehicleRepairsCount");

		lua_classfunction(L, "getBodyHealth", "getVehicleBodyHealth");
		lua_classfunction(L, "setBodyHealth", "setVehicleBodyHealth");
		lua_classfunction(L, "getBodyAdditionalHealth", "getVehicleBodyAdditionalHealth");
		lua_classfunction(L, "setBodyAdditionalHealth", "setVehicleBodyAdditionalHealth");

		lua_classfunction(L, "getHealthDataBase64", "getVehicleHealthDataBase64");
		lua_classfunction(L, "loadHealthDataFromBase64", "loadVehicleHealthDataFromBase64");

		// vehicle damage
		lua_classfunction(L, "getPartDamageLevel", "getVehiclePartDamageLevel");
		lua_classfunction(L, "setPartDamageLevel", "setVehiclePartDamageLevel");
		lua_classfunction(L, "getPartBulletHoles", "getVehiclePartBulletHoles");
		lua_classfunction(L, "setPartBulletHoles", "setVehiclePartBulletHoles");
		lua_classfunction(L, "isLightDamaged", "isVehicleLightDamaged");
		lua_classfunction(L, "setLightDamaged", "setVehicleLightDamaged");
		lua_classfunction(L, "isWindowDamaged", "isVehicleWindowDamaged");
		lua_classfunction(L, "setWindowDamaged", "setVehicleWindowDamaged");
		lua_classfunction(L, "isSpecialLightDamaged", "isVehicleSpecialLightDamaged");
		lua_classfunction(L, "setSpecialLightDamaged", "setVehicleSpecialLightDamaged");
		lua_classfunction(L, "hasArmoredWindows", "hasVehicleArmoredWindows");
		lua_classfunction(L, "getArmoredWindowHealth", "getVehicleArmoredWindowHealth");
		lua_classfunction(L, "setArmoredWindowHealth", "setVehicleArmoredWindowHealth");
		lua_classfunction(L, "getArmoredWindowShootCount", "getVehicleArmoredWindowShootCount");
		lua_classfunction(L, "setArmoredWindowShootCount", "setVehicleArmoredWindowShootCount");
		lua_classfunction(L, "getBumperDamageLevel", "getVehicleBumperDamageLevel");
		lua_classfunction(L, "setBumperDamageLevel", "setVehicleBumperDamageLevel");

		lua_classfunction(L, "getDamageDataBase64", "getVehicleDamageDataBase64");
		lua_classfunction(L, "loadDamageDataFromBase64", "loadVehicleDamageDataFromBase64");

		//vehicle script data
		lua_classfunction(L, "setManualEngineControl", "setVehicleManualEngineControl");
		lua_classfunction(L, "isManualEngineControl", "isVehicleManualEngineControl");

		lua_classfunction(L, "getScriptDataBase64", "getVehicleScriptDataBase64");
		lua_classfunction(L, "loadScriptDataFromBase64", "loadVehicleScriptDataFromBase64");
		
		lua_classvariable(L, "destroyed", nullptr, "isDestroyed");
		lua_classvariable(L, "modKitsCount", nullptr, "getModKitsCount");
		lua_classvariable(L, "modKit", "setModKit", "getModKit");
		lua_classvariable(L, "primaryColor", "setPrimaryColor", "getPrimaryColor");
		lua_classvariable(L, "secondaryColor", "setSecondaryColor", "getSecondaryColor");
		lua_classvariable(L, "secondaryColorRGB", "setSecondaryColorRGB", "getSecondaryColorRGB");
		lua_classvariable(L, "pearlColor", "setPearlColor", "getPearlColor");
		lua_classvariable(L, "wheelColor", "setWheelColor", "getWheelColor");
		lua_classvariable(L, "interiorColor", "setInteriorColor", "getInteriorColor");
		lua_classvariable(L, "dashboardColor", "setDashboardColor", "getDashboardColor");
		lua_classvariable(L, "tireSmokeColor", "setTireSmokeColor", "getTireSmokeColor");
		lua_classvariable(L, "wheelType", nullptr, "getWheelType");
		lua_classvariable(L, "wheelVariation", nullptr, "getWheelVariation");
		lua_classvariable(L, "rearWheelVariation", nullptr, "getRearWheelVariation");
		lua_classvariable(L, "rearWheels", "setRearWheels", nullptr);
		lua_classvariable(L, "customTires", "setCustomTires", "getCustomTires");
		lua_classvariable(L, "specialDarkness", "setSpecialDarkness", "getSpecialDarkness");
		lua_classvariable(L, "numberplateIndex", "setNumberplateIndex", "getNumberplateIndex");
		lua_classvariable(L, "numberplateText", "setNumberplateText", "getNumberplateText");
		lua_classvariable(L, "windowTint", "setWindowTint", "getWindowTint");
		lua_classvariable(L, "dirtLevel", "setDirtLevel", "getDirtLevel");
		lua_classvariable(L, "neonColor", "setNeonColor", "getNeonColor");
		lua_classvariable(L, "livery", "setLivery", "getLivery");
		lua_classvariable(L, "roofLivery", "setRoofLivery", "getRoofLivery");
		lua_classvariable(L, "appearanceDataBase64", "loadAppearanceDataFromBase64", "getAppearanceDataBase64");
		lua_classvariable(L, "engineOn", "setEngineOn", nullptr);
		lua_classvariable(L, "handbrakeActive", nullptr, "isHandbrakeActive");
		lua_classvariable(L, "headlightColor", "setHeadlightColor", "getHeadlightColor");
		lua_classvariable(L, "radioStationIndex", "setRadioStationIndex", "getRadioStationIndex");
		lua_classvariable(L, "sirenActive", "setSirenActive", "isSirenActive");
		lua_classvariable(L, "lockState", "setLockState", "getLockState");
		lua_classvariable(L, "doorState", "setDoorState", "getDoorState");
		lua_classvariable(L, "daylightOn", nullptr, "isDaylightOn");
		lua_classvariable(L, "nightlightOn", nullptr, "isNightlightOn");
		lua_classvariable(L, "roofOpened", "setRoofOpened", "isRoofOpened");
		lua_classvariable(L, "flamethrowerActive", nullptr, "isFlamethrowerActive");
		lua_classvariable(L, "lightsMultiplier", "setLightsMultiplier", "getLightsMultiplier");
		lua_classvariable(L, "gameStateBase64", "loadGameStateFromBase64", "getGameStateBase64");
		lua_classvariable(L, "engineHealth", "setEngineHealth", "getEngineHealth");
		lua_classvariable(L, "petrolTankHealth", "setPetrolTankHealth", "getPetrolTankHealth");
		lua_classvariable(L, "wheelsCount", nullptr, "getWheelsCount");
		lua_classvariable(L, "repairsCount", nullptr, "getRepairsCount");
		lua_classvariable(L, "bodyHealth", "setBodyHealth", "getBodyHealth");
		lua_classvariable(L, "bodyAdditionalHealth", "setBodyAdditionalHealth", "getBodyAdditionalHealth");
		lua_classvariable(L, "healthDataBase64", "loadHealthDataFromBase64", "getHealthDataBase64");
		lua_classvariable(L, "armoredWindows", nullptr, "hasArmoredWindows");
		lua_classvariable(L, "damageDataBase64", "loadDamageDataFromBase64", "getDamageDataBase64");
		lua_classvariable(L, "manualEngineControl", "setManualEngineControl", "isManualEngineControl");
		lua_classvariable(L, "scriptDataBase64", "loadScriptDataFromBase64", "getScriptDataBase64");
	}
	lua_endclass(L);
}

/*


	auto allVehicle = vehicles;

	lua_newtable(L);
	int index = 1;
	for(auto vehicle : allVehicle)
	{
		Core->LogInfo("for: " + std::to_string(vehicle->GetModel()));
		lua_pushnumber(L, index);
		lua_pushuserdata(L, "Vehicle", vehicle);
		lua_rawset(L, -3);

		index++;
	}

	lua_stacktrace(L, "CLuaVehicleDefs::ipairs");
*/

int CLuaVehicleDefs::destroy(lua_State* L)
{
	alt::IVehicle* vehicle = nullptr;

	//lua_stacktrace(L, "destroy");

	CArgReader argReader(L);
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

#ifndef NDEBUG
	Core->LogInfo("Vehicle failed to destroyed");
#endif

	lua_pushboolean(L, false);
	return 1;
}

int CLuaVehicleDefs::next(lua_State* L)
{
	Core->LogInfo("CLuaVehicleDefs::next");

	return 0;
}

int CLuaVehicleDefs::pairs(lua_State* L)
{
	

	return 0;
}

int CLuaVehicleDefs::ipairs(lua_State* L)
{
	//Core->LogInfo("CLuaVehicleDefs::ipairs");

	//lua_stacktrace(L, "CLuaVehicleDefs::ipairs1");

	lua_newtable(L);
	auto allVehicle = alt::ICore::Instance().GetVehicles();
	for (size_t i = 0; i < allVehicle.GetSize(); i++)
	{
		lua_pushnumber(L, i + 1);
		//lua_pushuserdata(L, "Vehicle", static_cast<alt::IBaseObject*>(allVehicle[i].Get()));
		lua_pushbaseobject(L, allVehicle[i].Get());
		lua_rawset(L, -3);
	}

	//lua_stacktrace(L, "CLuaVehicleDefs::ipairs2");

	return 1;
}

int CLuaVehicleDefs::tostring(lua_State* L)
{
	return 0;
}

int CLuaVehicleDefs::CreateVehicle(lua_State* L)
{
	unsigned int modelHash;
	alt::Position position;
	alt::Rotation rotation;

	CArgReader argReader(L);
	argReader.ReadNumber(modelHash);
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
		lua_pushbaseobject(L, vehicle.Get());
	else
		lua_pushnil(L);

#ifdef _DEBUG
	Core->LogInfo("Vehicle(" + std::to_string(modelHash) + ", {"+ std::to_string(position.x) +", "+ std::to_string(position.y) +", "+ std::to_string(position.z) +"}, {" + std::to_string(rotation.roll) + ", " + std::to_string(rotation.pitch) + ", " + std::to_string(rotation.yaw) + "})");
#endif

	return 1;
}

int CLuaVehicleDefs::GetDriver(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushbaseobject(L, vehicle->GetDriver().Get());

	return 1;
}

int CLuaVehicleDefs::IsDestroyed(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsDestroyed());

	return 1;
}

int CLuaVehicleDefs::GetMod(lua_State* L)
{
	alt::IVehicle* vehicle;
	int category;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetModsCount(lua_State* L)
{
	alt::IVehicle* vehicle;
	int category;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetMod(lua_State* L)
{
	alt::IVehicle* vehicle;
	int category;
	int id;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetModKitsCount(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetModKitsCount());

	return 1;
}

int CLuaVehicleDefs::GetModKit(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetModKit());

	return 1;
}

int CLuaVehicleDefs::SetModKit(lua_State* L)
{
	alt::IVehicle* vehicle;
	int id;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsPrimaryColorRGB(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsPrimaryColorRGB());

	return 1;
}

int CLuaVehicleDefs::GetPrimaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->GetPrimaryColor());

	return 1;
}

int CLuaVehicleDefs::GetPrimaryColorRGB(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushrgba(L, vehicle->GetPrimaryColorRGB());

	return 1;
}

int CLuaVehicleDefs::SetPrimaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetPrimaryColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::SetPrimaryColorRGB(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsSecondaryColorRGB(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsSecondaryColorRGB());

	return 1;
}

int CLuaVehicleDefs::GetSecondaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetSecondaryColor());

	return 1;
}

int CLuaVehicleDefs::GetSecondaryColorRGB(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushrgba(L, vehicle->GetSecondaryColorRGB());

	return 1;
}

int CLuaVehicleDefs::SetSecondaryColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetSecondaryColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::SetSecondaryColorRGB(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetPearlColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetPearlColor());

	return 1;
}

int CLuaVehicleDefs::SetPearlColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetPearlColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::GetWheelColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetWheelColor());

	return 1;
}

int CLuaVehicleDefs::SetWheelColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetWheelColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::GetInteriorColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetInteriorColor());

	return 1;
}

int CLuaVehicleDefs::SetInteriorColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetInteriorColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::GetDashboardColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetDashboardColor());

	return 1;
}

int CLuaVehicleDefs::SetDashboardColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetDashboardColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::IsTireSmokeColorCustom(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsTireSmokeColorCustom());

	return 1;
}

int CLuaVehicleDefs::GetTireSmokeColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushrgba(L, vehicle->GetTireSmokeColor());

	return 1;
}

int CLuaVehicleDefs::SetTireSmokeColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetWheelType(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetWheelType());

	return 1;
}

int CLuaVehicleDefs::GetWheelVariation(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetWheelVariation());

	return 1;
}

int CLuaVehicleDefs::GetRearWheelVariation(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetRearWheelVariation());

	return 1;
}

int CLuaVehicleDefs::SetWheels(lua_State* L)
{
	alt::IVehicle* vehicle;
	int type;
	int variation;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetRearWheels(lua_State* L)
{
	alt::IVehicle* vehicle;
	int variation;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetCustomTires(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->GetCustomTires());

	return 1;
}

int CLuaVehicleDefs::SetCustomTires(lua_State* L)
{
	alt::IVehicle* vehicle;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetSpecialDarkness(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetSpecialDarkness());

	return 1;
}

int CLuaVehicleDefs::SetSpecialDarkness(lua_State* L)
{
	alt::IVehicle* vehicle;
	int value;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetNumberplateIndex(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetNumberplateIndex());

	return 1;
}

int CLuaVehicleDefs::SetNumberplateIndex(lua_State* L)
{
	alt::IVehicle* vehicle;
	int index;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetNumberplateText(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, vehicle->GetNumberplateText().CStr());

	return 1;
}

int CLuaVehicleDefs::SetNumberplateText(lua_State* L)
{
	alt::IVehicle* vehicle;
	std::string text;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetWindowTint(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetWindowTint());

	return 1;
}

int CLuaVehicleDefs::SetWindowTint(lua_State* L)
{
	alt::IVehicle* vehicle;
	int tint;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetDirtLevel(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetDirtLevel());

	return 1;
}

int CLuaVehicleDefs::SetDirtLevel(lua_State* L)
{
	alt::IVehicle* vehicle;
	int level;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsExtraOn(lua_State* L)
{
	alt::IVehicle* vehicle;
	int extraId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::ToggleExtra(lua_State* L)
{
	alt::IVehicle* vehicle;
	int extra;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsNeonActive(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsNeonActive());

	return 1;
}

int CLuaVehicleDefs::GetNeonActive(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetNeonActive(lua_State* L)
{
	alt::IVehicle* vehicle;
	bool left, right, front, back;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetNeonColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushrgba(L, vehicle->GetNeonColor());

	return 1;
}

int CLuaVehicleDefs::SetNeonColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetLivery(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetLivery());

	return 1;
}

int CLuaVehicleDefs::SetLivery(lua_State* L)
{
	alt::IVehicle* vehicle;
	int livery;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetRoofLivery(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetRoofLivery());

	return 1;
}

int CLuaVehicleDefs::SetRoofLivery(lua_State* L)
{
	alt::IVehicle* vehicle;
	int roofLivery;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetAppearanceDataBase64(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, vehicle->GetAppearanceDataBase64().CStr());

	return 1;
}

int CLuaVehicleDefs::LoadAppearanceDataFromBase64(lua_State* L)
{
	alt::IVehicle* vehicle;
	std::string appearance;

	CArgReader argReader(L);
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

////vehicle game state
int CLuaVehicleDefs::IsEngineOn(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsEngineOn());

	return 1;
}

int CLuaVehicleDefs::SetEngineOn(lua_State* L)
{
	alt::IVehicle* vehicle;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsHandbrakeActive(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsHandbrakeActive());

	return 1;
}

int CLuaVehicleDefs::GetHeadlightColor(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetHeadlightColor());

	return 1;
}

int CLuaVehicleDefs::SetHeadlightColor(lua_State* L)
{
	alt::IVehicle* vehicle;
	alt::RGBA color;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadRGBA(color);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetHeadlightColor(color.GetColor());

	return 0;
}

int CLuaVehicleDefs::GetRadioStationIndex(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetRadioStationIndex());

	return 0;
}

int CLuaVehicleDefs::SetRadioStationIndex(lua_State* L)
{
	alt::IVehicle* vehicle;
	int stationIndex;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsSirenActive(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsSirenActive());

	return 1;
}

int CLuaVehicleDefs::SetSirenActive(lua_State* L)
{
	alt::IVehicle* vehicle;
	bool state;

	CArgReader argReader(L);
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

//// TODO document available values. Enum?
int CLuaVehicleDefs::GetLockState(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetLockState());

	return 1;
}

int CLuaVehicleDefs::SetLockState(lua_State* L)
{
	alt::IVehicle* vehicle;
	int state;

	CArgReader argReader(L);
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

//// TODO document available values. Enum?
int CLuaVehicleDefs::GetDoorState(lua_State* L)
{
	alt::IVehicle* vehicle;
	int doorId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetDoorState(lua_State* L)
{
	alt::IVehicle* vehicle;
	int doorId;
	int state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsWindowOpened(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWindowOpened(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsDaylightOn(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsDaylightOn());

	return 1;
}

int CLuaVehicleDefs::IsNightlightOn(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsNightlightOn());

	return 1;
}

int CLuaVehicleDefs::IsRoofOpened(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsRoofOpened());

	return 1;
}

int CLuaVehicleDefs::SetRoofOpened(lua_State* L)
{
	alt::IVehicle* vehicle;
	bool state;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);
	argReader.ReadBool(state);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	vehicle->SetRoofOpened(state);

	return 0;
}

int CLuaVehicleDefs::IsFlamethrowerActive(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsFlamethrowerActive());

	return 1;
}

int CLuaVehicleDefs::GetLightsMultiplier(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetLightsMultiplier());

	return 1;
}

int CLuaVehicleDefs::SetLightsMultiplier(lua_State* L)
{
	alt::IVehicle* vehicle;
	float multiplier;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetGameStateBase64(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, vehicle->GetGameStateBase64().CStr());

	return 1;
}

int CLuaVehicleDefs::LoadGameStateFromBase64(lua_State* L)
{
	alt::IVehicle* vehicle;
	std::string base64;

	CArgReader argReader(L);
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

////vehicle health
int CLuaVehicleDefs::GetEngineHealth(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetEngineHealth());

	return 1;
}

int CLuaVehicleDefs::SetEngineHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int health;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetPetrolTankHealth(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetPetrolTankHealth());

	return 1;
}

int CLuaVehicleDefs::SetPetrolTankHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int health;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetWheelsCount(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetWheelsCount());

	return 1;
}

int CLuaVehicleDefs::IsWheelBurst(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWheelBurst(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::DoesWheelHasTire(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWheelHasTire(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsWheelDetached(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWheelDetached(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsWheelOnFire(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWheelOnFire(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetWheelHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWheelHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int wheelId;
	float health;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetRepairsCount(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
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
////int CLuaVehicleDefs::GetLastDamagedWith(lua_State* L);

int CLuaVehicleDefs::GetBodyHealth(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetBodyHealth());

	return 1;
}

int CLuaVehicleDefs::SetBodyHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int health;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetBodyAdditionalHealth(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, vehicle->GetBodyAdditionalHealth());

	return 1;
}

int CLuaVehicleDefs::SetBodyAdditionalHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int health;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetHealthDataBase64(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, vehicle->GetHealthDataBase64().CStr());

	return 1;
}

int CLuaVehicleDefs::LoadHealthDataFromBase64(lua_State* L)
{
	alt::IVehicle* vehicle;
	std::string base64;

	CArgReader argReader(L);
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

//// vehicle damage
int CLuaVehicleDefs::GetPartDamageLevel(lua_State* L)
{
	alt::IVehicle* vehicle;
	int partId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetPartDamageLevel(lua_State* L)
{
	alt::IVehicle* vehicle;
	int partId;
	int damage;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetPartBulletHoles(lua_State* L)
{
	alt::IVehicle* vehicle;
	int partId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetPartBulletHoles(lua_State* L)
{
	alt::IVehicle* vehicle;
	int partId;
	int shootsCount;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsLightDamaged(lua_State* L)
{
	alt::IVehicle* vehicle;
	int lightId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetLightDamaged(lua_State* L)
{
	alt::IVehicle* vehicle;
	int lightId;
	bool isDamaged;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsWindowDamaged(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetWindowDamaged(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;
	bool isDamaged;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsSpecialLightDamaged(lua_State* L)
{
	alt::IVehicle* vehicle;
	int specialLightId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetSpecialLightDamaged(lua_State* L)
{
	alt::IVehicle* vehicle;
	int specialLightId;
	bool isDamaged;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::HasArmoredWindows(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->HasArmoredWindows());

	return 1;
}

int CLuaVehicleDefs::GetArmoredWindowHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetArmoredWindowHealth(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;
	float health;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetArmoredWindowShootCount(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetArmoredWindowShootCount(lua_State* L)
{
	alt::IVehicle* vehicle;
	int windowId;
	int count;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetBumperDamageLevel(lua_State* L)
{
	alt::IVehicle* vehicle;
	int bumperId;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::SetBumperDamageLevel(lua_State* L)
{
	alt::IVehicle* vehicle;
	int bumperId;
	int damageLevel;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::GetDamageDataBase64(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, vehicle->GetDamageDataBase64().CStr());

	return 1;
}

int CLuaVehicleDefs::LoadDamageDataFromBase64(lua_State* L)
{
	alt::IVehicle* vehicle;
	std::string base64;

	CArgReader argReader(L);
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

////vehicle script data
int CLuaVehicleDefs::SetManualEngineControl(lua_State* L)
{
	alt::IVehicle* vehicle;
	bool state;

	CArgReader argReader(L);
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

int CLuaVehicleDefs::IsManualEngineControl(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, vehicle->IsManualEngineControl());

	return 1;
}

int CLuaVehicleDefs::GetScriptDataBase64(lua_State* L)
{
	alt::IVehicle* vehicle;

	CArgReader argReader(L);
	argReader.ReadBaseObject(vehicle);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, vehicle->GetScriptDataBase64().CStr());

	return 1;
}

int CLuaVehicleDefs::LoadScriptDataFromBase64(lua_State* L)
{
	alt::IVehicle* vehicle;
	std::string base64;

	CArgReader argReader(L);
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
//
//int CLuaVehicleDefs::IsDestroyed(lua_State* L);

//int CLuaVehicleDefs::SetVehiclePosition(lua_State* L)
//{
//	alt::IVehicle *vehicle;
//	alt::Position position;
//
//	CArgReader argReader(L);
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

//int CLuaVehicleDefs::GetVehiclePosition(lua_State* L)
//{
//	alt::IVehicle* vehicle;
//	alt::Position position;
//
//	CArgReader argReader(L);
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
#pragma once

#include <Main.h>

class CLuaVehicleDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int tostring(lua_State* L);
	static int destroy(lua_State* L);
	static int next(lua_State* L);
	static int pairs(lua_State* L);
	static int ipairs(lua_State* L);

	static int CreateVehicle(lua_State* L);
	static int GetDriver(lua_State* L);
	static int IsDestroyed(lua_State* L);

	static int GetMod(lua_State* L);
	static int GetModsCount(lua_State* L);
	static int SetMod(lua_State* L);

	static int GetModKitsCount(lua_State* L);
	static int GetModKit(lua_State* L);
	static int SetModKit(lua_State* L);

	static int IsPrimaryColorRGB(lua_State* L);
	static int GetPrimaryColor(lua_State* L);
	static int GetPrimaryColorRGB(lua_State* L);
	static int SetPrimaryColor(lua_State* L);
	static int SetPrimaryColorRGB(lua_State* L);

	static int IsSecondaryColorRGB(lua_State* L);
	static int GetSecondaryColor(lua_State* L);
	static int GetSecondaryColorRGB(lua_State* L);
	static int SetSecondaryColor(lua_State* L);
	static int SetSecondaryColorRGB(lua_State* L);

	static int GetPearlColor(lua_State* L);
	static int SetPearlColor(lua_State* L);

	static int GetWheelColor(lua_State* L);
	static int SetWheelColor(lua_State* L);

	static int GetInteriorColor(lua_State* L);
	static int SetInteriorColor(lua_State* L);

	static int GetDashboardColor(lua_State* L);
	static int SetDashboardColor(lua_State* L);

	static int IsTireSmokeColorCustom(lua_State* L);
	static int GetTireSmokeColor(lua_State* L);
	static int SetTireSmokeColor(lua_State* L);

	static int GetWheelType(lua_State* L);
	static int GetWheelVariation(lua_State* L);
	static int GetRearWheelVariation(lua_State* L);
	static int SetWheels(lua_State* L);
	static int SetRearWheels(lua_State* L);

	static int GetCustomTires(lua_State* L);
	static int SetCustomTires(lua_State* L);

	static int GetSpecialDarkness(lua_State* L);
	static int SetSpecialDarkness(lua_State* L);

	static int GetNumberplateIndex(lua_State* L);
	static int SetNumberplateIndex(lua_State* L);

	static int GetNumberplateText(lua_State* L);
	static int SetNumberplateText(lua_State* L);

	static int GetWindowTint(lua_State* L);
	static int SetWindowTint(lua_State* L);

	static int GetDirtLevel(lua_State* L);
	static int SetDirtLevel(lua_State* L);

	static int IsExtraOn(lua_State* L);
	static int ToggleExtra(lua_State* L);

	static int IsNeonActive(lua_State* L);
	static int GetNeonActive(lua_State* L);
	static int SetNeonActive(lua_State* L);
	static int GetNeonColor(lua_State* L);
	static int SetNeonColor(lua_State* L);

	static int GetLivery(lua_State* L);
	static int SetLivery(lua_State* L);
	static int GetRoofLivery(lua_State* L);
	static int SetRoofLivery(lua_State* L);

	static int GetAppearanceDataBase64(lua_State* L);
	static int LoadAppearanceDataFromBase64(lua_State* L);

	//vehicle game state
	static int IsEngineOn(lua_State* L);
	static int SetEngineOn(lua_State* L);

	static int IsHandbrakeActive(lua_State* L);

	static int GetHeadlightColor(lua_State* L);
	static int SetHeadlightColor(lua_State* L);

	static int GetRadioStationIndex(lua_State* L);
	static int SetRadioStationIndex(lua_State* L);

	static int IsSirenActive(lua_State* L);
	static int SetSirenActive(lua_State* L);

	// TODO document available values. Enum?
	static int GetLockState(lua_State* L);
	static int SetLockState(lua_State* L);

	// TODO document available values. Enum?
	static int GetDoorState(lua_State* L);
	static int SetDoorState(lua_State* L);

	static int IsWindowOpened(lua_State* L);
	static int SetWindowOpened(lua_State* L);

	static int IsDaylightOn(lua_State* L);
	static int IsNightlightOn(lua_State* L);

	static int GetRoofState(lua_State* L);
	static int SetRoofState(lua_State* L);

	static int IsFlamethrowerActive(lua_State* L);

	static int GetLightsMultiplier(lua_State* L);
	static int SetLightsMultiplier(lua_State* L);

	static int GetGameStateBase64(lua_State* L);
	static int LoadGameStateFromBase64(lua_State* L);

	//vehicle health
	static int GetEngineHealth(lua_State* L);
	static int SetEngineHealth(lua_State* L);

	static int GetPetrolTankHealth(lua_State* L);
	static int SetPetrolTankHealth(lua_State* L);

	static int GetWheelsCount(lua_State* L);

	static int IsWheelBurst(lua_State* L);
	static int SetWheelBurst(lua_State* L);

	static int DoesWheelHasTire(lua_State* L);
	static int SetWheelHasTire(lua_State* L);

	static int IsWheelDetached(lua_State* L);
	static int SetWheelDetached(lua_State* L);

	static int IsWheelOnFire(lua_State* L);
	static int SetWheelOnFire(lua_State* L);

	static int GetWheelHealth(lua_State* L);
	static int SetWheelHealth(lua_State* L);

	static int GetRepairsCount(lua_State* L);

	// Will be moved to event
	//static int<IEntity> GetLastAttacker(lua_State* L);
	//static int GetLastDamagedWith(lua_State* L);

	static int GetBodyHealth(lua_State* L);
	static int SetBodyHealth(lua_State* L);
	static int GetBodyAdditionalHealth(lua_State* L);
	static int SetBodyAdditionalHealth(lua_State* L);

	static int GetHealthDataBase64(lua_State* L);
	static int LoadHealthDataFromBase64(lua_State* L);

	// vehicle damage
	static int GetPartDamageLevel(lua_State* L);
	static int SetPartDamageLevel(lua_State* L);
	static int GetPartBulletHoles(lua_State* L);
	static int SetPartBulletHoles(lua_State* L);
	static int IsLightDamaged(lua_State* L);
	static int SetLightDamaged(lua_State* L);
	static int IsWindowDamaged(lua_State* L);
	static int SetWindowDamaged(lua_State* L);
	static int IsSpecialLightDamaged(lua_State* L);
	static int SetSpecialLightDamaged(lua_State* L);
	static int HasArmoredWindows(lua_State* L);
	static int GetArmoredWindowHealth(lua_State* L);
	static int SetArmoredWindowHealth(lua_State* L);
	static int GetArmoredWindowShootCount(lua_State* L);
	static int SetArmoredWindowShootCount(lua_State* L);
	static int GetBumperDamageLevel(lua_State* L);
	static int SetBumperDamageLevel(lua_State* L);

	static int GetDamageDataBase64(lua_State* L);
	static int LoadDamageDataFromBase64(lua_State* L);

	//vehicle script data
	static int SetManualEngineControl(lua_State* L);
	static int IsManualEngineControl(lua_State* L);

	static int GetScriptDataBase64(lua_State* L);
	static int LoadScriptDataFromBase64(lua_State* L);

	//static int IsDestroyed(lua_State* L);
};
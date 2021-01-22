#pragma once

#include <Main.h>

class CLuaPlayerDefs
{
public:
	static const char* ClassName;
	static void Init(lua_State* L);

private:
	static int tostring(lua_State* L);
	static int ipairs(lua_State* L);

	static int GetName(lua_State* L);

	static int GetHealth(lua_State* L);
	static int GetMaxHealth(lua_State* L);

	static int GetCurrentWeaponComponents(lua_State* L);

	static int GetCurrentWeaponTintIndex(lua_State* L);

	static int GetCurrentWeapon(lua_State* L);

	static int IsDead(lua_State* L);

	static int IsJumping(lua_State* L);
	static int IsInRagdoll(lua_State* L);
	static int IsAiming(lua_State* L);
	static int IsShooting(lua_State* L);
	static int IsReloading(lua_State* L);

	static int GetArmour(lua_State* L);
	static int GetMaxArmour(lua_State* L);

	static int GetMoveSpeed(lua_State* L);

	/*static int GetWeapon(lua_State* L);
	static int GetAmmo(lua_State* L);*/

	static int GetAimPos(lua_State* L);
	static int GetHeadRotation(lua_State* L);

	static int IsInVehicle(lua_State* L);
	static int GetVehicle(lua_State* L);
	static int GetSeat(lua_State* L);

	static int GetEntityAimingAt(lua_State* L);
	static int GetEntityAimOffset(lua_State* L);

	static int IsFlashlightActive(lua_State* L);

#ifdef ALT_SERVER_API
	static int IsConnected(lua_State* L);
	static int GetPing(lua_State* L);
	static int GetIP(lua_State* L);
	static int GetSocialID(lua_State* L);
	static int GetHwidHash(lua_State* L);
	static int GetHwidExHash(lua_State* L);
	static int GetAuthToken(lua_State* L);
	static int GetClothes(lua_State* L);

	static int Spawn(lua_State* L);
	static int Despawn(lua_State* L);
	static int SetModel(lua_State* L);
	static int SetArmour(lua_State* L);
	static int SetMaxArmour(lua_State* L);
	static int SetCurrentWeapon(lua_State* L);
	static int SetWeaponTintIndex(lua_State* L);
	static int AddWeaponComponent(lua_State* L);
	static int RemoveWeaponComponent(lua_State* L);
	static int ClearBloodDamage(lua_State* L);
	static int SetHealth(lua_State* L);
	static int SetMaxHealth(lua_State* L);
	static int GiveWeapon(lua_State* L);
	static int RemoveWeapon(lua_State* L);
	static int RemoveAllWeapons(lua_State* L);
	static int SetDateTime(lua_State* L);
	static int SetWeather(lua_State* L);
	static int SetClothes(lua_State* L);
	static int Kick(lua_State* L);
#else
	static int GetLocalPlayer(lua_State* L);

	static int IsTalking(lua_State* L);
	static int GetMicLevel(lua_State* L);
#endif
};
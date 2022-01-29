#pragma once

#include <Main.h>

namespace lua::Class
{
#ifdef ALT_CLIENT_API

	class LocalPlayer
	{
	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int GetLocalPlayer(lua_State* L);
		static int GetCurrentAmmo(lua_State* L);
	};

#endif

	class Player
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

		static int IsSuperJumpEnabled(lua_State* L);
		static int IsCrouching(lua_State* L);
		static int IsStealthy(lua_State* L);

		static int GetModel(lua_State* L);

#ifdef ALT_SERVER_API
		static int IsConnected(lua_State* L);
		static int GetPing(lua_State* L);
		static int GetIP(lua_State* L);
		static int GetSocialID(lua_State* L);
		static int GetHwidHash(lua_State* L);
		static int GetHwidExHash(lua_State* L);
		static int GetAuthToken(lua_State* L);

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
		static int Kick(lua_State* L);
		static int GetClothes(lua_State* L);
		static int SetClothes(lua_State* L);
		static int GetDlcClothes(lua_State* L);
		static int SetDlcClothes(lua_State* L);
		static int GetProp(lua_State* L);
		static int SetProp(lua_State* L);
		static int GetDlcProps(lua_State* L);
		static int SetDlcProps(lua_State* L);
		static int ClearProps(lua_State* L);
		static int IsEntityInStreamingRange(lua_State* L);
		static int SetInvincible(lua_State* L);
		static int GetInvincible(lua_State* L);
		static int SetIntoVehicle(lua_State* L);
		static int PlayAmbientSpeech(lua_State* L);
		static int SetHeadOverlay(lua_State* L);
		static int RemoveHeadOverlay(lua_State* L);
		static int SetHeadOverlayColor(lua_State* L);
		static int GetHeadOverlay(lua_State* L);
		static int SetFaceFeature(lua_State* L);
		static int GetFaceFeatureScale(lua_State* L);
		static int RemoveFaceFeature(lua_State* L);
		static int SetHeadBlendPaletteColor(lua_State* L);
		static int GetHeadBlendPaletteColor(lua_State* L);
		static int SetHeadBlendData(lua_State* L);
		static int GetHeadBlendData(lua_State* L);
		static int SetEyeColor(lua_State* L);
		static int GetEyeColor(lua_State* L);
		static int SetHairColor(lua_State* L);
		static int GetHairColor(lua_State* L);
		static int SetHairHighlightColor(lua_State* L);
		static int GetHairHighlightColor(lua_State* L);
		static int GetWeapons(lua_State* L);

		static int HasLocalMetaData(lua_State* L);
		static int SetLocalMetaData(lua_State* L);
		static int GetLocalMetaData(lua_State* L);
		static int DeleteLocalMetaData(lua_State* L);
#else
		static int IsTalking(lua_State* L);
		static int GetMicLevel(lua_State* L);

		static int GetSpatialVolume(lua_State* L);
		static int SetSpatialVolume(lua_State* L);
		static int GetNonSpatialVolume(lua_State* L);
		static int SetNonSpatialVolume(lua_State* L);
#endif
	};
}
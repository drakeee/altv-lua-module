#pragma once

#include <Main.h>

namespace lua::Class
{
	class Alt
	{
	public:
		enum class LogType
		{
			LOG_INFO = 0,
			LOG_DEBUG,
			LOG_WARNING,
			LOG_ERROR,
			LOG_COLORED
		};

	public:
		static const char* ClassName;
		static void Init(lua_State* L);

	private:
		static int AltIndex(lua_State* L);

		static int dofile(lua_State* L);
		static int inext(lua_State* L);
		static int pairs(lua_State* L);
		static int ipairs(lua_State* L);
		static int ipairsaux(lua_State* L);

		static int NextTick(lua_State* L);
		static int EveryTick(lua_State* L);
		static int SetTimeout(lua_State* L);
		static int SetInterval(lua_State* L);
		static int ClearTimer(lua_State* L);

		static int Log(lua_State* L, LogType logtype = LogType::LOG_INFO);
		static int LogInfo(lua_State* L);
		static int LogDebug(lua_State* L);
		static int LogWarning(lua_State* L);
		static int LogError(lua_State* L);
		static int LogColored(lua_State* L);

		static int SetMetaData(lua_State* L);
		static int GetMetaData(lua_State* L);
		static int DeleteMetaData(lua_State* L);
		static int HasMetaData(lua_State* L);
		static int GetSyncedMetaData(lua_State* L);
		static int HasSyncedMetaData(lua_State* L);

		static int GetRequiredPermissions(lua_State* L);
		static int GetOptionalPermissions(lua_State* L);

		static int OnServer(lua_State* L);
		static int OffServer(lua_State* L);
		static int OnClient(lua_State* L);
		static int OffClient(lua_State* L);

		static int EmitServer(lua_State* L);
		static int EmitClient(lua_State* L);

		static int Export(lua_State* L);

		static int IsDebug(lua_State* L);
		static int FileExists(lua_State* L);
		static int FileRead(lua_State* L);
		static int GetEntityByID(lua_State* L);
		static int GetVersion(lua_State* L);
		static int GetBranch(lua_State* L);

		static int Hash(lua_State* L);

		static int GetModuleTime(lua_State* L);

#ifdef ALT_SERVER_API
		static int EmitClientAll(lua_State* L);

		static int GetRootDirectory(lua_State* L);

		static int StartResource(lua_State* L);
		static int StopResource(lua_State* L);
		static int RestartResource(lua_State* L);

		static int SetSyncedMetaData(lua_State* L);
		static int DeleteSyncedMetaData(lua_State* L);

		static int GetPlayersByName(lua_State* L);

		static int GetNetTime(lua_State* L);

		static int SetPassword(lua_State* L);
		static int HashServerPassword(lua_State* L);

		static int StopServer(lua_State* L);

		static int GetVehicleModelByHash(lua_State* L);
#else
		static int require(lua_State* L);

		//virtual alt::IPackage::PathInfo Resolve(IResource* resource, alt::StringView path, StringView currentModulePath) const = 0; //TODO?
		static int SetCharStat(lua_State* L); //done
		static int GetCharStat(lua_State* L); //done
		static int ResetCharStat(lua_State* L); //done

		static int IsSandbox(lua_State* L); //done
		static int IsKeyDown(lua_State* L); //done
		static int IsKeyToggled(lua_State* L); //done
		static int AreControlsEnabled(lua_State* L); //done
		static int SetCursorPosition(lua_State* L); //done
		static int GetCursorPosition(lua_State* L); //done
		static int SetConfigFlag(lua_State* L); //done
		static int GetConfigFlag(lua_State* L); //done
		static int DoesConfigFlagExist(lua_State* L); //done

		static int GetLicenseHash(lua_State* L); //done
		static int GetLocale(lua_State* L); //done
		static int IsInStreamerMode(lua_State* L); //done
		static int IsMenuOpen(lua_State* L); //done
		static int IsConsoleOpen(lua_State* L); //done

		static int ToggleGameControls(lua_State* L);
		static int ShowCursor(lua_State* L);

		//virtual const Array<INative*> GetAllNatives() const = 0;
		//virtual Ref<INative::Context> CreateNativesContext() const = 0;

		static int GetTextureFromDrawable(lua_State* L); //done

		static int RequestIPL(lua_State* L); //done
		static int RemoveIPL(lua_State* L); //done

		static int BeginScaleformMovieMethodMinimap(lua_State* L); //done

		static int GetMsPerGameMinute(lua_State* L); //done
		static int SetMsPerGameMinute(lua_State* L); //done
		static int SetWeatherCycle(lua_State* L); //done
		static int SetWeatherSyncActive(lua_State* L); //done

		static int SetCamFrozen(lua_State* L); //done

		static int GetPermissionState(lua_State* L); //done

		static int TakeScreenshot(lua_State* L); //done
		static int TakeScreenshotGameOnly(lua_State* L); //done

		static int SetAngularVelocity(lua_State* L); //done

		static int IsGameFocused(lua_State* L); //done

		static int LoadModel(lua_State* L);
		static int LoadModelAsync(lua_State* L);

		static int LoadYtyp(lua_State* L);
		static int UnloadYtyp(lua_State* L);

		static int GetHeadshotBase64(lua_State* L);

		static int SetDlcClothes(lua_State* L);
		static int SetDlcProps(lua_State* L);
		static int ClearProps(lua_State* L);

		static int SetWatermarkPosition(lua_State* L);

		static int GetFps(lua_State* L);
		static int GetPing(lua_State* L);
		static int GetTotalPacketsSent(lua_State* L);
		static int GetTotalPacketsLost(lua_State* L);
		static int GetServerIp(lua_State* L);
		static int GetServerPort(lua_State* L);
		static int GetClientPath(lua_State* L);

		static int HasLocalMetaData(lua_State* L);
		static int GetLocalMetaData(lua_State* L);

		static int CopyToClipboard(lua_State* L);

		static int ToggleRmlDebugger(lua_State* L);
		static int LoadRmlFontFace(lua_State* L);
		static int ToggleRmlControl(lua_State* L);

		static int WorldToScreen(lua_State* L);
		static int ScreenToWorld(lua_State* L);
		static int GetCamPos(lua_State* L);
		static int SetMinimapComponentPosition(lua_State* L);
#endif
	};
}
#pragma once

#include "Main.h"

class CLuaResourceImpl;
class CLuaScriptRuntime : public alt::IScriptRuntime
{

public:
	typedef std::function<int(CLuaResourceImpl*, const alt::CEvent*)>				FunctionCallback;
	typedef std::function<const std::vector<int>*(CLuaResourceImpl*, const alt::CEvent*)>	CallbackGetter;
	typedef std::map<std::string, FunctionCallback>					EventsCallbacks;
	typedef std::map<std::string, CallbackGetter>					EventsGetter;

	std::map<alt::IResource*, alt::config::Node::Dict> resourceNodeDictMap;

	alt::IResource::Impl*	CreateImpl(alt::IResource* resource) override;
	void					DestroyImpl(alt::IResource::Impl* impl) override;

	alt::config::Node::Dict	ParseConfig(std::string path);
	CLuaResourceImpl*		GetResourceImplFromState(lua_State* L);
	void					AddResource(lua_State* L, CLuaResourceImpl* resource);
	const std::string		GetBaseObjectType(alt::IBaseObject *baseObject);
	const std::string		GetBaseObjectType(alt::IBaseObject::Type baseType);
	const std::string		GetEventType(const alt::CEvent* ev);
	const std::string		GetEventType(const alt::CEvent::Type ev);
	inline void				RegisterServerCallback(alt::CEvent::Type eventType, CallbackGetter getter, FunctionCallback func)
	{
		this->eventsGetter[this->GetEventType(eventType)] = getter;
		this->eventsCallbacks[this->GetEventType(eventType)] = func;
	}
	inline CallbackGetter GetEventGetter(alt::CEvent::Type eventType)
	{
		return this->eventsGetter[this->GetEventType(eventType)];
	}
	inline FunctionCallback GetEventCallback(const std::string& eventName)
	{
		return this->eventsCallbacks[eventName];
	}
	inline const semver::version& GetVersion(void)
	{
		return this->version;
	}
	inline alt::config::Node::Dict &GetServerConfig(void)
	{
		return this->serverConfigDict;
	}
	inline alt::config::Node::Dict& GetResourceConfig(alt::IResource* resource)
	{
		return this->resourceNodeDictMap[resource];
	}


	static CLuaScriptRuntime& Instance()
	{
		static CLuaScriptRuntime _Instance;
		return _Instance;
	}

	CLuaScriptRuntime();
	~CLuaScriptRuntime() { };

private:
	const semver::version						version{ 0, 4, 2, semver::prerelease::dev };
	alt::config::Node::Dict						serverConfigDict;
	std::map<lua_State*, CLuaResourceImpl*>		resources;
	EventsCallbacks								eventsCallbacks;
	EventsGetter								eventsGetter;

	static bool OnResourceStart(const alt::CEvent* e, void* userData);
	static bool OnResourceStop(const alt::CEvent* e, void* userData);

	const std::vector<std::string> entityTypes{
		"Player",
		"Vehicle",
		"Blip",
		"WebView",
		"VoiceChannel",
		"ColShape",
		"Checkpoint"
	};

	const std::vector<std::string> eventTypes{
		"NONE",

		// Shared
		"playerConnect", //done
		"playerDisconnect", //done

		"anyResourceStart", //done
		"anyResourceStop", //done
		"anyResourceError", //done

		"SERVER_SCRIPT_EVENT",
		"CLIENT_SCRIPT_EVENT",

		"metaChange", //done
		"syncedMetaChange", //done
		"streamSyncedMetaChange", //done
		"globalMetaChange", //done
		"globalSyncedMetaChange", //done

		"playerDamage", //done
		"playerDeath", //done
		"startFire", //done
		"explosion", //done
		"startProjectile", //done
		"weaponDamage", //done
		"vehicleDestroy", //done

		"checkpoint", //
		"colshape", //done
		"playerEnterVehicle", //done
		"playerEnteringVehicle", //done
		"playerLeaveVehicle", //done
		"playerChangeVehicleSeat", //done
		"playerWeaponChange",

		"vehicleAttach", //done
		"vehicleDetach", //done
		"netOwnerChange", //done

		"removeEntity", //done
		"createBaseObject",
		"removeBaseObject",

		"dataNodeReceived",

		"consoleCommand", //done

		// Client
		"connectionComplete",
		"disconnect",
		"webView",
		"keyboard",
		"gameEntityCreate",
		"gameEntityDestroy",

		"ALL",
		"SIZE"
	};
	//alt::ICore* _core = &alt::ICore::Instance();
};
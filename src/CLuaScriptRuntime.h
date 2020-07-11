#pragma once

#include "Main.h"

class CLuaResourceImpl;
class CLuaScriptRuntime : public alt::IScriptRuntime
{

public:
	typedef std::function<int(lua_State*, const alt::CEvent*)>		FunctionCallback;
	typedef std::map<alt::CEvent::Type, FunctionCallback>			EventsCallbacks;

	alt::IResource::Impl*	CreateImpl(alt::IResource* resource) override;
	void					DestroyImpl(alt::IResource::Impl* impl) override;

	CLuaResourceImpl*		GetResourceFromState(lua_State* L);
	const std::string		GetBaseObjectType(alt::IBaseObject *baseObject);
	const std::string		GetBaseObjectType(alt::IBaseObject::Type baseType);
	const std::string		GetEventType(const alt::CEvent* ev);
	inline void				RegisterCallback(alt::CEvent::Type eventType, FunctionCallback func)
	{
		this->eventsCallbacks[eventType] = func;
	}
	inline FunctionCallback GetEventCallback(alt::CEvent::Type eventType)
	{
		return this->eventsCallbacks[eventType];
	}
	inline bool				AddFunctionRef(const void* ptr, int functionRef)
	{
		if (this->IsFunctionRefExists(ptr))
			return false;

		this->functionReferences[ptr] = functionRef;
		return true;
	}
	inline bool				RemoveFunctionRef(const void* ptr)
	{
		if (!this->IsFunctionRefExists(ptr))
			return false;

		this->functionReferences.erase(ptr);
		return true;
	}
	inline bool				IsFunctionRefExists(const void* ptr)
	{
		return this->functionReferences.find(ptr) != this->functionReferences.end();
	}
	inline int				GetFunctionRef(const void* ptr)
	{
		if (!this->IsFunctionRefExists(ptr))
			return LUA_NOREF;

		return this->functionReferences[ptr];
	}


	static CLuaScriptRuntime& Instance()
	{
		static CLuaScriptRuntime _Instance;
		return _Instance;
	}

	CLuaScriptRuntime() {};
	~CLuaScriptRuntime() {};

private:
	std::map<lua_State*, CLuaResourceImpl*>		resources;
	EventsCallbacks								eventsCallbacks;
	std::map<const void*, int>					functionReferences;

	const std::vector<std::string> entityTypes{
		"Player",
		"Vehicle",
		"Blip",
		"WebView",
		"VoiceChannel",
		"ColShape",
		"CheckPoint"
	};

	const std::vector<std::string> eventTypes{
		"NONE",

		// Shared
		"playerConnect", //done
		"playerDisconnect", //done

		"resourceStart", //done
		"resourceStop", //done
		"resourceError", //done

		"SERVER_SCRIPT_EVENT",
		"CLIENT_SCRIPT_EVENT",

		"metaChange", //done
		"syncedMetaChange", //done
		"streamSyncedMetaChange", //done
		"globalMetaChange", //done
		"globalSyncedMetaChange", //done

		"playerDamage", //done
		"playerDeath", //done
		"fire",
		"explosion", //done
		"weaponDamage", //done
		"vehicleDestroy", //done

		"checkpoint", //
		"colshape", //done
		"playerEnterVehicle", //done
		"playerLeaveVehicle", //done
		"playerChangeVehicleSeat", //done

		"removeEntity", //done

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
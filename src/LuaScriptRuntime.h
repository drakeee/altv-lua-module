#pragma once

#include "Main.h"

#ifndef NDEBUG
#define DEBUG_HELPER(x) (alt::String("[Lua] ") + x)
#define DEBUG_INFO(x) Core->LogInfo(DEBUG_HELPER(x))
#define DEBUG_WARNING(x) Core->LogWarning(DEBUG_HELPER(x))
#else
#define DEBUG_INFO(x)
#define DEBUG_WARNING(x)
#endif

class LuaResourceImpl;
class LuaScriptRuntime : public alt::IScriptRuntime
{

public:
	typedef std::function<int(LuaResourceImpl*, const alt::CEvent*)>				FunctionCallback;
	typedef std::function<const std::vector<int>*(LuaResourceImpl*, const alt::CEvent*)>	CallbackGetter;
	typedef std::map<std::string, FunctionCallback>					EventsCallbacks;
	typedef std::map<std::string, CallbackGetter>					EventsGetter;

#ifdef ALT_SERVER_API
	std::map<alt::IResource*, alt::config::Node::Dict> resourceNodeDictMap;
#endif

	alt::IResource::Impl*	CreateImpl(alt::IResource* resource) override;
	void					DestroyImpl(alt::IResource::Impl* impl) override;

	alt::config::Node::Dict	ParseConfig(std::string path);
	LuaResourceImpl*		GetResourceImplFromState(lua_State* L);
	void					AddResource(lua_State* L, LuaResourceImpl* resource);
	const std::string		GetBaseObjectType(alt::IBaseObject *baseObject);
	const std::string		GetBaseObjectType(alt::IBaseObject::Type baseType);
	
	inline const semver::version& GetVersion(void)
	{
		return this->version;
	}
	inline EventManager* GetEventManager(void)
	{
		return this->eventManager;
	}
#ifdef ALT_SERVER_API
	inline alt::config::Node::Dict &GetServerConfig(void)
	{
		return this->serverConfigDict;
	}
	inline alt::config::Node::Dict& GetResourceConfig(alt::IResource* resource)
	{
		return this->resourceNodeDictMap[resource];
	}
#endif

	//Source: https://github.com/altmp/v8-helpers/blob/f4e4c2cacff229df022e68af99756b6f6ef1f6eb/V8ResourceImpl.h#L229
	inline static int64_t GetTime()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now().time_since_epoch())
			.count();
	}

	inline int64_t GetModuleTime()
	{
		return (this->GetTime() - this->moduleStartedTime);
	}

	static LuaScriptRuntime& Instance()
	{
		static LuaScriptRuntime _Instance;
		return _Instance;
	}

private:
	LuaScriptRuntime();
	~LuaScriptRuntime() { };

	const semver::version						version{ 1, 2, 4, alt::ICore::SDK_VERSION, semver::branch::dev };
#ifdef ALT_SERVER_API
	alt::config::Node::Dict						serverConfigDict;

	static bool OnResourceStart(const alt::CEvent* e, void* userData);
	static bool OnResourceStop(const alt::CEvent* e, void* userData);
#endif
	std::map<lua_State*, LuaResourceImpl*>		resources;
	EventsCallbacks								eventsCallbacks;
	EventsGetter								eventsGetter;

	EventManager*								eventManager;

	int64_t										moduleStartedTime;

	const std::vector<std::string> entityTypes{
		"Player",
		"Vehicle",
		"Blip",
		"WebView",
		"VoiceChannel",
		"ColShape",
		"Checkpoint",
		"WebSocketClient",
		"HTTPClient",
		"Audio",
		"RmlElement",
		"RmlDocument",
		"LocalPlayer"
	};
};
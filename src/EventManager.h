#pragma once

#include <Main.h>

#define REGISTER_LOCAL_EVENT(eventType,eventName,...) \
EventManager::Handler eventName(eventType,#eventName,__VA_ARGS__)

class LuaResourceImpl;
class EventManager
{
public:
	typedef std::function<int(LuaResourceImpl*, const alt::CEvent*)>				FunctionCallback;
	typedef std::function<std::vector<int> (LuaResourceImpl*, const alt::CEvent*)>	CallbackGetter;

	class Handler
	{
	public:
		Handler(alt::CEvent::Type eventType, const std::string& eventName, FunctionCallback callback, CallbackGetter getter = nullptr);
		Handler(alt::CEvent::Type eventType, const std::string& eventName, alt::IBaseObject::Type baseObjectType, FunctionCallback callback, CallbackGetter getter = nullptr);
		void Invoke(void);

	private:
		EventManager* eventManager;

		alt::CEvent::Type eventType;
		std::string eventName;
		int baseObjectType = -1;

		FunctionCallback callback;
		CallbackGetter getter;
	};

	struct Event
	{
		alt::CEvent::Type eventType;
		std::string eventName{ "" };

		int baseObjectType = -1;

		FunctionCallback PushFunctionArguments = nullptr;
		CallbackGetter GetFunctionReferences = nullptr;

		bool IsBaseObjectEvent(void) { return this->baseObjectType != -1; }
		bool IsResourceEvent(void) { return !this->eventName.empty(); }
	};

	alt::CEvent::Type GetEventTypeFromName(const std::string& eventName);
	std::string GetEventNameFromType(alt::CEvent::Type eventType);
	alt::CEvent::Type GetEventTypeFromBaseObject(alt::IBaseObject* baseObject);

	Event* GetEventByType(alt::CEvent::Type eventType);
	Event* GetEventByName(const std::string& eventName);

	inline void RegisterHandler(Handler* handler) { this->handlers.push_back(handler); }
	inline std::vector<Handler*>& GetAllHandlers(void) { return this->handlers; }

	void RegisterEvent(alt::CEvent::Type eventType, const std::string& eventName, FunctionCallback callback, CallbackGetter getter = nullptr);
	void RegisterBaseObjectEvent(alt::CEvent::Type eventType, int baseObjectType, FunctionCallback callback, CallbackGetter getter = nullptr);

	void Emit(const std::string& eventName, alt::MValueArgs& args);

	static EventManager& Instance()
	{
		static EventManager _Instance;
		return _Instance;
	}

private:
	EventManager() { };
	~EventManager() { };

	typedef std::map<alt::CEvent::Type, Event*> EventMap;
	EventMap eventDatas;

	std::vector<Handler*> handlers;

	void RegisterBaseObject(alt::CEvent::Type eventType, int baseObjectType);
};

class ResourceEventManager
{
public:
	/*struct FunctionRef
	{
		int reference;
		bool isLocal = true;
	};*/

	ResourceEventManager(LuaResourceImpl* resourceImpl);

	//bool SubscribeEvent(const std::string& eventName, int functionReference);
	bool SubscribeEvent(alt::IBaseObject* baseObject, const std::string& eventName, int functionReference);
	bool SubscribeLocalEvent(std::string& eventName, int functionReference);
	bool SubscribeRemoteEvent(std::string& eventName, int functionReference);

	bool UnsubscribeLocalEvent(std::string& eventName, int functionReference);
	bool UnsubscribeRemoteEvent(std::string& eventName, int functionReference);

	bool UnsubscribeEvent(const std::string& eventName, int functionReference);
	bool UnsubscribeEvent(alt::IBaseObject* baseObject, const std::string& eventName, int functionReference);

	std::vector<int> GetFunctionReferences(alt::CEvent::Type eventType);
	std::vector<int> GetFunctionReferences(alt::CEvent::Type eventType, std::string& eventName);
	std::vector<int> GetFunctionReferences(alt::IBaseObject* baseObject, std::string& eventName);

	std::vector<int> GetLocalFunctionReferences(std::string& eventName);
	std::vector<int> GetRemoteFunctionReferences(std::string& eventName);

	void Emit(const std::string& eventName, alt::MValueArgs& args);

	bool ProcessEvents(const alt::CEvent* ev);

private:
	EventManager* manager;
	LuaResourceImpl* resourceImpl;

	typedef std::vector<int> FunctionReferences;
	typedef std::map<std::string, FunctionReferences> EventsMap;

	typedef std::map<alt::CEvent::Type, EventsMap> ResourceEvents;
	ResourceEvents resourceEvents;

	typedef std::map<alt::CEvent::Type, std::map<alt::IBaseObject*, EventsMap>> BaseObjectEvents;
	BaseObjectEvents baseObjectEvents;
};
#include <Main.h>

EventManager::Handler::Handler(alt::CEvent::Type eventType, const std::string& eventName, FunctionCallback callback, CallbackGetter getter) :
	eventType(eventType),
	eventName(eventName),
	callback(callback),
	getter(getter),
	eventManager(&EventManager::Instance())
{
	this->eventManager->RegisterHandler(this);
}

EventManager::Handler::Handler(alt::CEvent::Type eventType, const std::string& eventName, alt::IBaseObject::Type baseObjectType, FunctionCallback callback, CallbackGetter getter) :
	eventType(eventType),
	eventName(eventName),
	baseObjectType((int)baseObjectType),
	callback(callback),
	getter(getter),
	eventManager(&EventManager::Instance())
{
	this->eventManager->RegisterHandler(this);
}

void EventManager::Handler::Invoke()
{
	if(this->baseObjectType == -1)
		this->eventManager->RegisterEvent(this->eventType, this->eventName, this->callback, this->getter);
	else
		this->eventManager->RegisterBaseObjectEvent(this->eventType, this->baseObjectType, this->callback, this->getter);
}

void EventManager::RegisterEvent(alt::CEvent::Type eventType, const std::string& eventName, FunctionCallback callback, CallbackGetter getter)
{
	if (this->eventDatas.find(eventType) != this->eventDatas.end())
	{
		Core->LogError(eventName + " was already registered in the EventManager!");
		return;
	}

	Event* event = new Event();
	event->eventName = eventName;
	event->eventType = eventType;

	if (getter == nullptr)
		event->GetFunctionReferences = [](LuaResourceImpl* resourceImpl, const alt::CEvent* ev) -> std::vector<int>
		{
			return resourceImpl->GetResourceEventManager()->GetFunctionReferences(ev->GetType());
		};
	else
		event->GetFunctionReferences = getter;

	event->PushFunctionArguments = callback;

	DEBUG_INFO("Registered event: " + eventName);

	this->eventDatas[eventType] = event;
}

void EventManager::RegisterBaseObjectEvent(alt::CEvent::Type eventType, int baseObjectType, FunctionCallback callback, CallbackGetter getter)
{
	RegisterEvent(eventType, "", callback, getter);
	RegisterBaseObject(eventType, baseObjectType);
}

void EventManager::RegisterBaseObject(alt::CEvent::Type eventType, int baseObjectType)
{
	EventMap::iterator it = this->eventDatas.find(eventType);
	if (it == this->eventDatas.end())
		return;

	it->second->baseObjectType = baseObjectType;
}

void EventManager::Emit(const std::string& eventName, alt::MValueArgs& args)
{
	for each (alt::IResource* resource in Core->GetAllResources())
	{
		LuaResourceImpl* resourceImpl = dynamic_cast<LuaResourceImpl*>(resource->GetImpl());
		resourceImpl->GetResourceEventManager()->Emit(eventName, args);
	}
}

alt::CEvent::Type EventManager::GetEventTypeFromName(const std::string& eventName)
{
	EventMap::iterator it = std::find_if(this->eventDatas.begin(), this->eventDatas.end(), [&](const std::pair<alt::CEvent::Type, Event*> &pair)
		{
			return pair.second->eventName == eventName;
		});

	return (it != this->eventDatas.end()) ? it->first : alt::CEvent::Type::NONE;
}

std::string EventManager::GetEventNameFromType(alt::CEvent::Type eventType)
{
	EventMap::iterator it = this->eventDatas.find(eventType);
	return (it != this->eventDatas.end()) ? it->second->eventName : "";
}

alt::CEvent::Type EventManager::GetEventTypeFromBaseObject(alt::IBaseObject* baseObject)
{
	EventMap::iterator it = std::find_if(this->eventDatas.begin(), this->eventDatas.end(), [&](const std::pair<alt::CEvent::Type, Event*>& pair)
		{
			return pair.second->baseObjectType == (int)baseObject->GetType();
		});

	return (it != this->eventDatas.end()) ? it->first : alt::CEvent::Type::NONE;
}

EventManager::Event* EventManager::GetEventByType(alt::CEvent::Type eventType)
{
	EventMap::iterator it = this->eventDatas.find(eventType);
	
	return (it != this->eventDatas.end()) ? it->second : nullptr;
}

EventManager::Event* EventManager::GetEventByName(const std::string& eventName)
{
	EventMap::iterator it = std::find_if(this->eventDatas.begin(), this->eventDatas.end(), [&](const std::pair<alt::CEvent::Type, Event*>& pair)
		{
			return pair.second->eventName == eventName;
		});

	return (it != this->eventDatas.end()) ? it->second : nullptr;
}



ResourceEventManager::ResourceEventManager(LuaResourceImpl* resourceImpl)
	: resourceImpl(resourceImpl)
{
	this->manager = LuaScriptRuntime::Instance().GetEventManager();
}

bool ResourceEventManager::SubscribeEvent(alt::IBaseObject* baseObject, const std::string& eventName, int functionReference)
{
	alt::CEvent::Type eventType = this->manager->GetEventTypeFromBaseObject(baseObject);
	if (eventType == alt::CEvent::Type::NONE)
		return false;

	this->baseObjectEvents[eventType][baseObject][eventName].push_back(functionReference);
	return true;
}

bool ResourceEventManager::SubscribeLocalEvent(std::string& eventName, int functionReference)
{
	alt::CEvent::Type eventType = this->manager->GetEventTypeFromName(eventName);
	if (eventType == alt::CEvent::Type::NONE)
#ifdef ALT_SERVER_API
		eventType = alt::CEvent::Type::SERVER_SCRIPT_EVENT;
#else
		eventType = alt::CEvent::Type::CLIENT_SCRIPT_EVENT;
#endif

	DEBUG_INFO("SubscribeLocalEvent: " + std::to_string((int)eventType) + " - " + eventName);

	this->resourceEvents[eventType][eventName].push_back(functionReference);
	return true;
}

bool ResourceEventManager::SubscribeRemoteEvent(std::string& eventName, int functionReference)
{
#ifdef ALT_SERVER_API
	const alt::CEvent::Type remoteEvent = alt::CEvent::Type::CLIENT_SCRIPT_EVENT;
#else
	const alt::CEvent::Type remoteEvent = alt::CEvent::Type::SERVER_SCRIPT_EVENT;
#endif

	this->resourceEvents[remoteEvent][eventName].push_back(functionReference);
	return true;
}

bool ResourceEventManager::UnsubscribeLocalEvent(std::string& eventName, int functionReference)
{
#ifdef ALT_SERVER_API
	const alt::CEvent::Type localEvent = alt::CEvent::Type::SERVER_SCRIPT_EVENT;
#else
	const alt::CEvent::Type localEvent = alt::CEvent::Type::CLIENT_SCRIPT_EVENT;
#endif

	std::vector<int>& references = this->resourceEvents[localEvent][eventName];
	std::vector<int>::iterator it = std::find(references.begin(), references.end(), functionReference);

	if (it == references.end())
		return false;

	references.erase(it);
	return true;
}

bool ResourceEventManager::UnsubscribeRemoteEvent(std::string& eventName, int functionReference)
{
#ifdef ALT_SERVER_API
	const alt::CEvent::Type remoteEvent = alt::CEvent::Type::CLIENT_SCRIPT_EVENT;
#else
	const alt::CEvent::Type remoteEvent = alt::CEvent::Type::SERVER_SCRIPT_EVENT;
#endif

	std::vector<int>& references = this->resourceEvents[remoteEvent][eventName];
	std::vector<int>::iterator it = std::find(references.begin(), references.end(), functionReference);

	if (it == references.end())
		return false;

	references.erase(it);
	return true;
}

bool ResourceEventManager::UnsubscribeEvent(const std::string& eventName, int functionReference)
{
	alt::CEvent::Type eventType = this->manager->GetEventTypeFromName(eventName);
	if (eventType == alt::CEvent::Type::NONE)
#ifdef ALT_SERVER_API
		eventType = alt::CEvent::Type::SERVER_SCRIPT_EVENT;
#else
		eventType = alt::CEvent::Type::CLIENT_SCRIPT_EVENT;
#endif

	std::vector<int> &references = this->resourceEvents[eventType][eventName];
	std::vector<int>::iterator it = std::find(references.begin(), references.end(), functionReference);

	if (it == references.end())
		return false;

	references.erase(it);
	return true;
}

bool ResourceEventManager::UnsubscribeEvent(alt::IBaseObject* baseObject, const std::string& eventName, int functionReference)
{
	alt::CEvent::Type eventType = this->manager->GetEventTypeFromBaseObject(baseObject);
	if (eventType == alt::CEvent::Type::NONE)
		return false;

	std::vector<int>& references = this->baseObjectEvents[eventType][baseObject][eventName];
	std::vector<int>::iterator it = std::find(references.begin(), references.end(), functionReference);

	if (it == references.end())
		return false;

	references.erase(it);
	return true;
}

ResourceEventManager::FunctionReferences ResourceEventManager::GetFunctionReferences(alt::CEvent::Type eventType)
{
	ResourceEvents::iterator it = this->resourceEvents.find(eventType);
	if (it == this->resourceEvents.end())
		return std::vector<int>();

	std::string eventName = this->manager->GetEventNameFromType(eventType);
	return it->second[eventName];
}

ResourceEventManager::FunctionReferences ResourceEventManager::GetFunctionReferences(alt::CEvent::Type eventType, std::string& eventName)
{
	ResourceEvents::iterator it = this->resourceEvents.find(eventType);
	if (it == this->resourceEvents.end())
		return std::vector<int>();

	return it->second[eventName];
}

std::vector<int> ResourceEventManager::GetFunctionReferences(alt::IBaseObject* baseObject, std::string& eventName)
{
	if (baseObject == nullptr)
		return std::vector<int>();

	alt::CEvent::Type eventType = this->manager->GetEventTypeFromBaseObject(baseObject);
	if (eventType == alt::CEvent::Type::NONE)
		return std::vector<int>();

	EventsMap& baseObjectContainer = this->baseObjectEvents[eventType][baseObject];
	return baseObjectContainer[eventName];
}

std::vector<int> ResourceEventManager::GetLocalFunctionReferences(std::string& eventName)
{
#ifdef ALT_SERVER_API
	return this->resourceEvents[alt::CEvent::Type::SERVER_SCRIPT_EVENT][eventName];
#else
	return this->resourceEvents[alt::CEvent::Type::CLIENT_SCRIPT_EVENT][eventName];
#endif
}

std::vector<int> ResourceEventManager::GetRemoteFunctionReferences(std::string& eventName)
{
#ifdef ALT_SERVER_API
	return this->resourceEvents[alt::CEvent::Type::CLIENT_SCRIPT_EVENT][eventName];
#else
	return this->resourceEvents[alt::CEvent::Type::SERVER_SCRIPT_EVENT][eventName];
#endif
}

void ResourceEventManager::Emit(const std::string& eventName, alt::MValueArgs& args)
{
#ifdef ALT_SERVER_API
	EventsMap &references = this->resourceEvents[alt::CEvent::Type::SERVER_SCRIPT_EVENT];
#else
	EventsMap& references = this->resourceEvents[alt::CEvent::Type::CLIENT_SCRIPT_EVENT];
#endif
	if (references.size() == 0)
		return;

	FunctionReferences &functionRefs = references[eventName];
	if (functionRefs.size() == 0)
		return;

	lua_State* L = this->resourceImpl->GetLuaState();
	for (auto& functionRef : functionRefs)
	{
		//Get function reference from registry
		lua_rawgeti(L, LUA_REGISTRYINDEX, functionRef);

		//Push MValues
		lua_pushmvalueargs(L, args);

		//Try to call the function with the arguments
		if (lua_pcall(L, args.GetSize(), 0, 0) != 0)
		{
			//Sadly far from perfect
			Core->LogError(" Unable to execute1 \"" + eventName + "\"");

			//Get the error from the top of the stack
			if (lua_isstring(L, -1))
				Core->LogError(" Error: " + alt::String(luaL_checkstring(L, -1)));

			//Core->LogInfo("Error running function: %s" + alt::String(lua_tostring(this->resourceState, -1)));
		}
	}
}

bool ResourceEventManager::ProcessEvents(const alt::CEvent* ev)
{
	LuaScriptRuntime* runtime = &LuaScriptRuntime::Instance();
	EventManager* eventManager = runtime->GetEventManager();

	EventManager::Event* event = eventManager->GetEventByType(ev->GetType());
	if (event == nullptr)
	{
		DEBUG_WARNING("Internally unhandled event. alt::CEvent::Type::" + std::to_string((int)ev->GetType()));
		return true;
	}

	if (
		event->GetFunctionReferences == nullptr ||
		event->PushFunctionArguments == nullptr)
	{
		Core->LogError("GetFunctionReferences or PushFunctionArguments function not found for event: " + event->eventName);
		Core->LogError("GetFunctionReferences nullptr: " + std::to_string(event->GetFunctionReferences == nullptr));
		Core->LogError("PushFunctionArguments nullptr: " + std::to_string(event->PushFunctionArguments == nullptr));
		return false;
	}

	FunctionReferences functionReferences = event->GetFunctionReferences(this->resourceImpl, ev);
	if (functionReferences.empty())
		return false;

	lua_State* L = this->resourceImpl->GetLuaState();
	for (int functionReference : functionReferences)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, functionReference);
		int argumentsSize = event->PushFunctionArguments(this->resourceImpl, ev);

		if (lua_pcall(L, argumentsSize, 1, 0) != 0)
		{
			//Sadly far from perfect
			Core->LogError(" Unable to execute \"" + event->eventName + "\"");

			//Get the error from the top of the stack
			if (lua_isstring(L, -1))
				Core->LogError(" Error: " + alt::String(luaL_checkstring(L, -1)));
		}

		if (lua_isboolean(L, -1))
		{
			if (!lua_toboolean(L, -1))
			{
				ev->Cancel();
				DEBUG_INFO(std::string("LuaResourceImpl::OnEvent::") + event->eventName + std::string("::Cancelled"));
			}
		}
	}

	return true;
}
#include <Main.h>
#include <fstream>

//#include <events/CRenderEvent.h>
#include <events/CWebSocketClientEvent.h>
#include <events/CAudioEvent.h>

LuaScriptRuntime::LuaScriptRuntime()
{
	this->eventManager = &EventManager::Instance();

	//Register all events
	for(EventManager::Handler* handler : this->eventManager->GetAllHandlers())
	{
		handler->Invoke();
	}

#ifndef NDEBUG
	Core->LogInfo("LuaScriptRuntime::LuaScriptRuntime");
#endif

#ifdef ALT_SERVER_API
	VehicleModels::Instance(); //instance class once for further usage
#endif

#ifdef ALT_SERVER_API
	std::string serverConfigPath{ Core->GetRootDirectory() + p_s + "server.cfg" };
	this->serverConfigDict = this->ParseConfig(serverConfigPath);

	//Core->SubscribeEvent(alt::CEvent::Type::RESOURCE_START, LuaScriptRuntime::OnResourceStart, this);
	//Core->SubscribeEvent(alt::CEvent::Type::RESOURCE_STOP, LuaScriptRuntime::OnResourceStop, this);
#endif

	this->moduleStartedTime = this->GetTime();
}

#ifdef ALT_SERVER_API
bool LuaScriptRuntime::OnResourceStart(const alt::CEvent* e, void* userData)
{
	LuaScriptRuntime *runtime = (LuaScriptRuntime*)userData;
	auto event = (alt::CResourceStartEvent*)e;

	if (event->GetResource()->GetType() == "lua")
		return true;

	std::string resourceConfigPath{ event->GetResource()->GetPath() + p_s + "resource.cfg" };
	auto resourceNode = runtime->ParseConfig(resourceConfigPath);

	runtime->resourceNodeDictMap[event->GetResource()] = resourceNode;
	return true;
}

bool LuaScriptRuntime::OnResourceStop(const alt::CEvent* e, void* userData)
{
	LuaScriptRuntime* runtime = (LuaScriptRuntime*)userData;
	auto event = (alt::CResourceStartEvent*)e;

	runtime->resourceNodeDictMap.erase(event->GetResource());

	return true;
}
#endif

alt::IResource::Impl* LuaScriptRuntime::CreateImpl(alt::IResource* resource)
{

	DEBUG_INFO("Before::LuaScriptRuntime::CreateImpl");

	LuaResourceImpl* resourceImpl = new LuaResourceImpl{ this, resource };

	DEBUG_INFO("After::LuaScriptRuntime::CreateImpl: " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));

	return resourceImpl;
}

void LuaScriptRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
	LuaResourceImpl* resourceImpl = dynamic_cast<LuaResourceImpl*>(impl);

	if (resourceImpl != nullptr)
	{
		this->resources.erase(resourceImpl->GetLuaState());
	}

#ifndef NDEBUG
	Core->LogInfo("LuaScriptRuntime::DestroyImpl: " + std::to_string(reinterpret_cast<intptr_t>(impl)) + " - " + std::to_string(reinterpret_cast<intptr_t>(resourceImpl->GetLuaState())));
#endif

	delete impl;

}

alt::config::Node::Dict LuaScriptRuntime::ParseConfig(std::string path)
{
	std::ifstream file(path);
	std::string str;
	std::string file_contents;

	while (std::getline(file, str))
	{
		file_contents += str;
		file_contents.push_back('\n');
	}

	alt::config::Parser parser(file_contents.c_str(), file_contents.size());
	auto node = parser.Parse();

	if (!node.IsDict())
	{
		Core->LogError("Unable to parse config file: " + path);
		return {};
	}

	return node.ToDict();
}

LuaResourceImpl* LuaScriptRuntime::GetResourceImplFromState(lua_State* L)
{
	auto it = this->resources.find(L);
	if (it != this->resources.end())
		return it->second;

	return nullptr;
}

void LuaScriptRuntime::AddResource(lua_State* L, LuaResourceImpl* resource)
{
	this->resources.insert({ L, resource });
}

const std::string LuaScriptRuntime::GetBaseObjectType(alt::IBaseObject* baseObject)
{
	return this->entityTypes.at(static_cast<int>(baseObject->GetType()));
}

const std::string LuaScriptRuntime::GetBaseObjectType(alt::IBaseObject::Type baseType)
{
	return this->entityTypes.at(static_cast<int>(baseType));
}
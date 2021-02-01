#include <Main.h>

#ifdef _WIN32
#include <filesystem>
#else
#include <dirent.h>
#endif

CLuaResourceImpl::CLuaResourceImpl(CLuaScriptRuntime* runtime, alt::IResource* resource) :
	runtime(runtime),
	resource(resource),
	exportFunction(Core->CreateMValueDict())
{

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl1");

	//Create new Lua state
	this->resourceState = luaL_newstate();

	//Add resource to runtime
	runtime->AddResource(this->resourceState, this);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl2");

	this->workingPath.append(resource->GetPath().CStr());
	this->workingPath.append(preferred_separator);
	this->workingPath.append(resource->GetMain().CStr());
	this->workingPath = this->workingPath.substr(0, this->workingPath.find_last_of("\\/") + 1);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl3");

	//Import default libraries into the state
	luaL_openlibs(this->resourceState);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl4");

#ifdef ALT_SERVER_API
	//luaL_openlibs load jit by default
	//luaopen_jit(this->resourceState);

	//Pop LuaJIT information
	//lua_pop(this->resourceState, 4);
#else
	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl5");
	//Disable some libraries
	lua_disablelib(this->resourceState, LUA_IOLIBNAME);
	lua_disablelib(this->resourceState, LUA_OSLIBNAME);
	lua_disablelib(this->resourceState, LUA_FFILIBNAME);
	lua_disablelib(this->resourceState, LUA_LOADLIBNAME);
	lua_disablelib(this->resourceState, LUA_DBLIBNAME);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl6");

	lua_disablefunction(this->resourceState, "dofile");
	lua_disablefunction(this->resourceState, "load");
	lua_disablefunction(this->resourceState, "loadfile");
	lua_disablefunction(this->resourceState, "loadstring");
	lua_disablefunction(this->resourceState, "require");
	lua_disablefunction(this->resourceState, "loadlib");
	lua_disablefunction(this->resourceState, "setfenv");
	lua_disablefunction(this->resourceState, "getfenv");
	lua_disablefunction(this->resourceState, "newproxy");

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl7");
#endif

	//Init "es" and "e_mt" table
	lua_initclass(this->resourceState);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl8");

#ifdef ALT_SERVER_API
	//Set up working path
	lua_setpath(this->resourceState, (this->workingPath + "?.lua").c_str());
	lua_setpath(this->resourceState, (resource->GetPath().ToString() + std::string(preferred_separator) + std::string("?.lua")).c_str());

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl9");

	alt::String modulePath = Core->GetRootDirectory() + p_s + "modules" + p_s + MODULE_NAME + p_s + ADDITIONAL_MODULE_FOLDER + p_s;

	this->IncludePath(modulePath.CStr());
	lua_setpath(this->resourceState, (modulePath + "?.lua").CStr());
#endif

	lua_pushstring(this->resourceState, ADDITIONAL_MODULE_FOLDER);
	lua_setglobal(this->resourceState, "MODULE_FOLDER");

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl10");

#ifdef ALT_SERVER_API
	//Parse the resource config here as well because RESOURCE_START event is called after the script is executed
	{
		alt::String resourceConfigPath = this->resource->GetPath() + p_s + "resource.cfg";
		auto resourceNode = runtime->ParseConfig(resourceConfigPath.CStr());
		runtime->resourceNodeDictMap[this->resource] = resourceNode;
	}
#endif

	//Init functions
	CLuaVector2Defs::Init(this->resourceState);
	CLuaVector3Defs::Init(this->resourceState);
	CLuaConfigDefs::Init(this->resourceState);
	CLuaAltFuncDefs::Init(this->resourceState);
	CLuaResourceFuncDefs::Init(this->resourceState);
	CLuaBaseObjectDefs::Init(this->resourceState);
	CLuaWorldObjectDefs::Init(this->resourceState);
	CLuaEntityDefs::Init(this->resourceState);
	CLuaRGBADefs::Init(this->resourceState);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl11");

#ifdef ALT_CLIENT_API
	CLuaNativeDefs::Init(this->resourceState);
	CLuaHandlingDataDefs::Init(this->resourceState);
	CLuaMapDataDefs::Init(this->resourceState);
	CLuaDiscordManagerDefs::Init(this->resourceState);
	CLuaWebSocketDefs::Init(this->resourceState);
	CLuaWebViewDefs::Init(this->resourceState);
	CLuaVoiceDefs::Init(this->resourceState);
#endif

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl12");

	CLuaPlayerDefs::Init(this->resourceState);
	CLuaVehicleDefs::Init(this->resourceState);
	CLuaBlipDefs::Init(this->resourceState);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl13");

#ifdef ALT_SERVER_API
	CLuaCheckpointDefs::Init(this->resourceState);
	CLuaColShapeDefs::Init(this->resourceState);
	CLuaVoiceChannelDefs::Init(this->resourceState);
#endif

	CLuaMiscScripts::Init(this->resourceState);

	DEBUG_INFO("CLuaResourceImpl::CLuaResourceImpl");
}

CLuaResourceImpl::~CLuaResourceImpl()
{

	for (auto entity : this->entities)
	{
		Core->DestroyBaseObject(entity);
	}

	this->entities.clear();

	DEBUG_INFO("CLuaResourceImpl::~CLuaResourceImpl");
}

void CLuaResourceImpl::IncludePath(const char* path)
{
	alt::String modulePath(path);

#ifdef _WIN32
	std::filesystem::path directory(modulePath.CStr());

	if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
	{
		std::filesystem::directory_iterator begin(directory);
		std::filesystem::directory_iterator end;

		while (begin != end)
		{
			if (!std::filesystem::is_directory(*begin))
			{
				++begin;
				continue;
			}

			std::string moduleDir((*begin).path().string() + p_s.ToString() + std::string("?.lua"));
			lua_setpath(this->resourceState, moduleDir.c_str());

			++begin;
		}
	}
#else
	DIR* directory = opendir(modulePath.CStr());
	dirent* ent;

	if(directory != NULL)
	{
		while ((ent = readdir(directory)) != NULL)
		{
			if (ent->d_type != DT_DIR)
				continue;

			if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
				continue;

			std::string moduleDir(modulePath.ToString() + ent->d_name + p_s.ToString() + std::string("?.lua"));
			lua_setpath(this->resourceState, moduleDir.c_str());
		}

		closedir(directory);
	}
#endif
}

bool CLuaResourceImpl::Start()
{
	DEBUG_INFO("CLuaResourceImpl::Start");

#ifdef ALT_SERVER_API
	//Add path separator to the end
	alt::String workingDir(alt::String(resource->GetPath()) + alt::String(preferred_separator));
	alt::String mainFile = workingDir + resource->GetMain();

	DEBUG_INFO(alt::String("CLuaResourceImpl::CLuaResourceImpl::") + resource->GetMain());
	DEBUG_INFO(alt::String("ResourcePath: ") + workingDir);
	DEBUG_INFO(alt::String("MainFile: ") + mainFile);

	//Try to load file for testing purposes
	if (luaL_dofile(this->resourceState, mainFile.CStr()))
	{
		//Sadly far from perfect
		Core->LogError(" Unable to load \"" + mainFile + "\"");

		//Get the error from the top of the stack
		if (lua_isstring(this->resourceState, -1))
			Core->LogError(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

		return false;
	}

#else
	this->resource->EnableNatives();
	auto scope = this->resource->PushNativesScope();

	alt::String mainFile = resource->GetMain();
	alt::String script{this->GetScript(mainFile)};

	if (luaL_dostring(this->resourceState, script.CStr()))
	{
		//Sadly far from perfect
		Core->LogError(" Unable to load \"" + mainFile + "\"");

		//Get the error from the top of the stack
		if (lua_isstring(this->resourceState, -1))
			Core->LogError(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

		return false;
	}

#endif

	this->TriggerResourceLocalEvent("resourceStart", {});

	resource->SetExports(this->exportFunction);

	return true;
}

bool CLuaResourceImpl::Stop()
{
	DEBUG_INFO("CLuaResourceImpl::Stop");

	this->TriggerResourceLocalEvent("resourceStop", {});

	lua_close(this->resourceState);

	return true;
}

bool CLuaResourceImpl::OnEvent(const alt::CEvent* ev)
{
	//DEBUG_INFO(alt::String("CLuaResourceImpl::OnEvent::") + runtime->GetEventType(ev));
#ifdef ALT_CLIENT_API
	auto scope = this->resource->PushNativesScope();
#endif

	auto runtime = &CLuaScriptRuntime::Instance();
	if (!runtime->IsEventExists(ev))
	{
		DEBUG_WARNING("Internally unhandled event \"" + runtime->GetEventType(ev) + "\"");
		return true;
	}

	auto references = this->runtime->GetEventGetter(ev->GetType())(this, ev);
	auto eventFunc = this->runtime->GetEventCallback(runtime->GetEventType(ev->GetType()));

	for (auto &functionReference : (*references))
	{
		lua_rawgeti(this->resourceState, LUA_REGISTRYINDEX, functionReference);
		auto arguments = eventFunc(this, ev);

		if (lua_pcall(this->resourceState, arguments, 1, 0) != 0)
		{
			//Sadly far from perfect
			Core->LogError(" Unable to execute \"" + this->runtime->GetEventType(ev) + "\"");

			//Get the error from the top of the stack
			if (lua_isstring(this->resourceState, -1))
				Core->LogError(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

			//Core->LogInfo("Error running function: %s" + alt::String(lua_tostring(this->resourceState, -1)));
		}

		if (lua_isboolean(this->resourceState, -1))
		{
			if (!lua_toboolean(this->resourceState, -1))
			{
				ev->Cancel();
				DEBUG_INFO(std::string("CLuaResourceImpl::OnEvent::") + runtime->GetEventType(ev) + std::string("::Cancelled"));
			}
		}
	}

	return true;
}

void CLuaResourceImpl::OnTick()
{

	this->TriggerResourceLocalEvent("tick", {});

	for (auto& timer : this->timerReferences)
	{
		uint64_t timeNow = GetTime();
		if ((timeNow - timer.second.lastTime) > timer.second.interval)
		{
			lua_rawgeti(this->resourceState, LUA_REGISTRYINDEX, timer.second.functionIndex);

			if (lua_pcall(this->resourceState, 0, 0, 0) != 0)
			{
				//Sadly far from perfect
				Core->LogError(" Unable to execute timer function at index \"" + std::to_string(timer.first) + "\"");

				//Get the error from the top of the stack
				if (lua_isstring(this->resourceState, -1))
					Core->LogError(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));
			}

			timer.second.lastTime = timeNow;

			if (!timer.second.repeat)
				this->timerReferences.erase(timer.first);
		}
	}

#ifndef NDEBUG
	//this->_core->LogInfo("CLuaResourceImpl::OnTick");
#endif

}

void CLuaResourceImpl::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{
	DEBUG_INFO(this->resource->GetName() + alt::String(":CLuaResourceImpl::OnCreateBaseObject: ") + std::to_string(static_cast<int>(object->GetType())));
}

void CLuaResourceImpl::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{

	this->RemoveEntity(object.Get());

	DEBUG_INFO("CLuaResourceImpl::OnRemoveBaseObject");
}

void CLuaResourceImpl::TriggerResourceLocalEvent(std::string eventName, alt::MValueArgs args)
{
	auto references = &this->GetLocalEventReferences(eventName);

	for (auto& functionReference : (*references))
	{
		lua_rawgeti(this->resourceState, LUA_REGISTRYINDEX, functionReference);

		lua_pushmvalueargs(this->resourceState, args);

		if (lua_pcall(this->resourceState, args.GetSize(), 0, 0) != 0)
		{
			//Sadly far from perfect
			Core->LogError(" Unable to execute \"" + eventName + "\"");

			//Get the error from the top of the stack
			if (lua_isstring(this->resourceState, -1))
				Core->LogError(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

			//Core->LogInfo("Error running function: %s" + alt::String(lua_tostring(this->resourceState, -1)));
		}
	}
}

bool CLuaResourceImpl::RegisterLocalEvent(std::string eventName, int functionReference)
{
	auto& event = this->localEventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);
	
	DEBUG_INFO("RegisterLocalEvent: " + eventName + " - " + std::to_string(functionReference));

	if (it != event.end())
	{
		return false;
	}

	event.push_back(functionReference);
	return true;
}

bool CLuaResourceImpl::RegisterRemoteEvent(std::string eventName, int functionReference)
{
	auto& event = this->remoteEventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	DEBUG_INFO("RegisterRemoteEvent: " + eventName + " - " + std::to_string(functionReference));

	if (it != event.end())
	{
		return false;
	}

	event.push_back(functionReference);
	return true;
}

#ifdef ALT_CLIENT_API
bool CLuaResourceImpl::RegisterWebEvent(alt::IWebView* webView, std::string eventName, int functionReference)
{
	auto& event = this->webEventsReferences[webView][eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	DEBUG_INFO("RegisterWebEvent: " + eventName + " - " + std::to_string(functionReference));

	if (it != event.end())
	{
		return false;
	}

	event.push_back(functionReference);
	return true;
}

bool CLuaResourceImpl::RemoveWebEvent(alt::IWebView* webView, std::string eventName, int functionReference)
{
	auto& event = this->webEventsReferences[webView][eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}

bool CLuaResourceImpl::RegisterWebSocketEvent(alt::IWebSocketClient* webSocket, std::string eventName, int functionReference)
{
	auto& event = this->webSocketEventsReferences[webSocket][eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	DEBUG_INFO("RegisterWebEvent: " + eventName + " - " + std::to_string(functionReference));

	if (it != event.end())
	{
		return false;
	}

	event.push_back(functionReference);
	return true;
}

bool CLuaResourceImpl::RemoveWebSocketEvent(alt::IWebSocketClient* webSocket, std::string eventName, int functionReference)
{
	auto& event = this->webSocketEventsReferences[webSocket][eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}
#endif

bool CLuaResourceImpl::RemoveLocalEvent(std::string eventName, int functionReference)
{
	auto &event = this->localEventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}

bool CLuaResourceImpl::RemoveRemoteEvent(std::string eventName, int functionReference)
{
	auto& event = this->remoteEventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}

uint32_t CLuaResourceImpl::CreateTimer(uint32_t functionIndex, uint32_t interval, bool repeat)
{
	this->timerIndex++;
	this->timerReferences[timerIndex] = LuaTimer{functionIndex, interval, repeat, GetTime()};
	
	return timerIndex;
}

#ifdef ALT_SERVER_API
bool CLuaResourceImpl::MakeClient(alt::IResource::CreationInfo* info, alt::Array<alt::String> files)
{
	//info->type = "js";
	return true;
}
#endif

alt::MValue CLuaResourceImpl::LuaFunction::Call(alt::MValueArgs args) const
{
	lua_State* L = this->resource->GetLuaState();
	lua_rawgeti(L, LUA_REGISTRYINDEX, this->functionRef);

	lua_pushmvalueargs(L, args);

	lua_call(L, args.GetSize(), 1);

	return lua_tomvalue(L, -1)->Clone();
}
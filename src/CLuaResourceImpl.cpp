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

	//Create new Lua state
	this->resourceState = luaL_newstate();

	//Add resource to runtime
	runtime->AddResource(this->resourceState, this);

	this->workingPath.append(resource->GetPath().CStr());
	this->workingPath.append(preferred_separator);
	this->workingPath.append(resource->GetMain().CStr());
	this->workingPath = this->workingPath.substr(0, this->workingPath.find_last_of("\\/") + 1);

	//Import default libraries into the state
	luaL_openlibs(this->resourceState);

#ifdef ALT_SERVER_API
	luaopen_jit(this->resourceState);

	//Pop LuaJIT information
	lua_pop(this->resourceState, 4);
#else
	//Disable some libraries
	lua_pushnil(this->resourceState);
	lua_setglobal(this->resourceState, LUA_IOLIBNAME);
	
	lua_pushnil(this->resourceState);
	lua_setglobal(this->resourceState, LUA_OSLIBNAME);

	lua_pushnil(this->resourceState);
	lua_setglobal(this->resourceState, LUA_JITLIBNAME);

	lua_register(this->resourceState, "dofile", CLuaFunctionDefs::DisabledFunction);
	lua_register(this->resourceState, "loadfile", CLuaFunctionDefs::DisabledFunction);
	lua_register(this->resourceState, "require", CLuaFunctionDefs::DisabledFunction);
	lua_register(this->resourceState, "loadlib", CLuaFunctionDefs::DisabledFunction);
	lua_register(this->resourceState, "getfenv", CLuaFunctionDefs::DisabledFunction);
	lua_register(this->resourceState, "newproxy", CLuaFunctionDefs::DisabledFunction);
#endif

	//Init "es" and "e_mt" table
	lua_initclass(this->resourceState);

	//Set up working path
	lua_setpath(this->resourceState, (this->workingPath + "?.lua").c_str());
	lua_setpath(this->resourceState, (resource->GetPath().ToString() + std::string(preferred_separator) + std::string("?.lua")).c_str());

#ifdef ALT_SERVER_API
	alt::String modulePath = Core->GetRootDirectory() + p_s + "modules" + p_s + MODULE_NAME + p_s + ADDITIONAL_MODULE_FOLDER + p_s;

	this->IncludePath(modulePath.CStr());
	lua_setpath(this->resourceState, (modulePath + "?.lua").CStr());
#endif

	lua_pushstring(this->resourceState, ADDITIONAL_MODULE_FOLDER);
	lua_setglobal(this->resourceState, "MODULE_FOLDER");

	//Parse the resource config here as well because RESOURCE_START event is called after the script is executed
	{
		alt::String resourceConfigPath = this->resource->GetPath() + p_s + "resource.cfg";
		auto resourceNode = runtime->ParseConfig(resourceConfigPath.CStr());
		runtime->resourceNodeDictMap[this->resource] = resourceNode;
	}

	//Init functions
	CLuaVector3Defs::Init(this->resourceState);
	CLuaConfigDefs::Init(this->resourceState);
	CLuaAltFuncDefs::Init(this->resourceState);
	CLuaResourceFuncDefs::Init(this->resourceState);
	CLuaBaseObjectDefs::Init(this->resourceState);
	CLuaWorldObjectDefs::Init(this->resourceState);
	CLuaEntityDefs::Init(this->resourceState);
	CLuaHandlingDataDefs::Init(this->resourceState);
	CLuaPlayerDefs::Init(this->resourceState);
	CLuaVehicleDefs::Init(this->resourceState);

#ifdef ALT_SERVER_API
	CLuaBlipDefs::Init(this->resourceState);
	CLuaCheckpointDefs::Init(this->resourceState);
	CLuaColShapeDefs::Init(this->resourceState);
	CLuaVoiceChannelDefs::Init(this->resourceState);
#endif

	CLuaMiscScripts::Init(this->resourceState);

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::CLuaResourceImpl");
#endif

}

CLuaResourceImpl::~CLuaResourceImpl()
{

	for (auto entity : this->entities)
	{
		Core->DestroyBaseObject(entity);
	}

	this->entities.clear();

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::~CLuaResourceImpl");
#endif

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

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::Start");
#endif

	//Add path separator to the end
	alt::String workingDir(alt::String(resource->GetPath()) + alt::String(preferred_separator));
	alt::String mainFile = workingDir + resource->GetMain();

#ifndef NDEBUG
	Core->LogInfo(alt::String("CLuaResourceImpl::CLuaResourceImpl::") + resource->GetMain());
	Core->LogInfo(alt::String("ResourcePath: ") + workingDir);
	Core->LogInfo(alt::String("MainFile: ") + mainFile);
#endif

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

	this->TriggerResourceLocalEvent("resourceStart", {});

	resource->SetExports(this->exportFunction);

	return true;
}

bool CLuaResourceImpl::Stop()
{

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::Stop");
#endif

	this->TriggerResourceLocalEvent("resourceStop", {});

	lua_close(this->resourceState);

	return true;
}

bool CLuaResourceImpl::OnEvent(const alt::CEvent* ev)
{

#ifndef NDEBUG
	Core->LogInfo(alt::String("CLuaResourceImpl::OnEvent::") + runtime->GetEventType(ev));
#endif

	auto runtime = &CLuaScriptRuntime::Instance();
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

#ifndef NDEBUG
				Core->LogInfo(std::string("CLuaResourceImpl::OnEvent::") + runtime->GetEventType(ev) + std::string("::Cancelled"));
#endif

			}
		}
	}

	return true;
}

void CLuaResourceImpl::OnTick()
{

	this->TriggerResourceLocalEvent("tick", {});

#ifndef NDEBUG
	//this->_core->LogInfo("CLuaResourceImpl::OnTick");
#endif

}

void CLuaResourceImpl::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifndef NDEBUG
	Core->LogInfo(this->resource->GetName() + alt::String(":CLuaResourceImpl::OnCreateBaseObject: ") + std::to_string(static_cast<int>(object->GetType())));
#endif

}

void CLuaResourceImpl::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{

	this->RemoveEntity(object.Get());

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::OnRemoveBaseObject");
#endif

}

void CLuaResourceImpl::TriggerResourceLocalEvent(std::string eventName, alt::MValueArgs args)
{
	auto references = &this->GetEventReferences(eventName);

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

bool CLuaResourceImpl::RegisterEvent(std::string eventName, int functionReference)
{
	auto& event = this->eventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

#ifndef NDEBUG
	Core->LogInfo("RegisterEvent: " + eventName + " - " + std::to_string(functionReference));
#endif

	if (it != event.end())
	{
		return false;
	}

	event.push_back(functionReference);
	return true;
}

bool CLuaResourceImpl::RegisterClientEvent(std::string eventName, int functionReference)
{
	auto& event = this->clientEventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

#ifndef NDEBUG
	Core->LogInfo("RegisterClientEvent: " + eventName + " - " + std::to_string(functionReference));
#endif

	if (it != event.end())
	{
		return false;
	}

	event.push_back(functionReference);
	return true;
}

bool CLuaResourceImpl::RemoveEvent(std::string eventName, int functionReference)
{
	auto &event = this->eventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}

bool CLuaResourceImpl::RemoveClientEvent(std::string eventName, int functionReference)
{
	auto& event = this->clientEventsReferences[eventName];
	auto it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}

#ifdef ALT_SERVER_API
bool CLuaResourceImpl::MakeClient(alt::IResource::CreationInfo* info, alt::Array<alt::String> files)
{
	info->type = "js";
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
#include <Main.h>

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
	luaopen_jit(this->resourceState);

	//Pop LuaJIT information
	lua_pop(this->resourceState, 4);

	//Init "es" and "e_mt" table
	lua_initclass(this->resourceState);

	//Set up working path
	lua_setpath(this->resourceState, (this->workingPath + "?.lua").c_str());

	//Init functions
	CLuaVector3Defs::Init(this->resourceState);
	CLuaAltFuncDefs::Init(this->resourceState);
	CLuaResourceFuncDefs::Init(this->resourceState);
	CLuaBaseObjectDefs::Init(this->resourceState);
	CLuaWorldObjectDefs::Init(this->resourceState);
	CLuaEntityDefs::Init(this->resourceState);
	CLuaPlayerDefs::Init(this->resourceState);
	CLuaVehicleDefs::Init(this->resourceState);
	CLuaBlipDefs::Init(this->resourceState);
	CLuaMiscScripts::Init(this->resourceState);

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::CLuaResourceImpl");
#endif

}

CLuaResourceImpl::~CLuaResourceImpl()
{

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::~CLuaResourceImpl");
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

		//Close virtual machine and point to null pointer
		lua_close(this->resourceState);
		this->resourceState = nullptr;

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

		if (lua_pcall(this->resourceState, arguments, 0, 0) != 0)
		{
			//Sadly far from perfect
			Core->LogError(" Unable to execute \"" + this->runtime->GetEventType(ev) + "\"");

			//Get the error from the top of the stack
			if (lua_isstring(this->resourceState, -1))
				Core->LogError(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

			//Core->LogInfo("Error running function: %s" + alt::String(lua_tostring(this->resourceState, -1)));
		}
	}

	return true;
}

void CLuaResourceImpl::OnTick()
{

#ifndef NDEBUG
	//this->_core->LogInfo("CLuaResourceImpl::OnTick");
#endif

}

void CLuaResourceImpl::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::OnCreateBaseObject: " + std::to_string(static_cast<int>(object->GetType())));
#endif

}

void CLuaResourceImpl::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{

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

bool CLuaResourceImpl::MakeClient(alt::IResource::CreationInfo* info, alt::Array<alt::String> files)
{
	info->type = "js";
	return true;
}

alt::MValue CLuaResourceImpl::LuaFunction::Call(alt::MValueArgs args) const
{
	lua_State* L = this->resource->GetLuaState();
	lua_rawgeti(L, LUA_REGISTRYINDEX, this->functionRef);

	lua_pushmvalueargs(L, args);

	lua_call(L, args.GetSize(), 1);

	return lua_tomvalue(L, -1)->Clone();
}
#include <Main.h>

CLuaResourceImpl::CLuaResourceImpl(CLuaScriptRuntime* runtime, alt::IResource* resource) :
	runtime(runtime),
	resource(resource)
{
	//Create new Lua state
	this->resourceState = luaL_newstate();

	//Import default libraries into the state
	luaL_openlibs(this->resourceState);
	luaopen_jit(this->resourceState);

	//Pop LuaJIT information
	lua_pop(this->resourceState, 4);

	//Init "es" and "e_mt" table
	lua_initclass(this->resourceState);

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

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::Start");
#endif

	//lua_initclass(this->resourceState);

	//Initialize alt functions in the state
	/*CLuaAltFuncDefs::init(this->resourceState);
	CLuaVector3Defs::init(this->resourceState);
	CLuaEntityDefs::init(this->resourceState);
	CLuaVehicleDefs::init(this->resourceState);*/

	//Add path separator to the end
	alt::String workingDir(alt::String(resource->GetPath()) + alt::String(preferred_separator));
	alt::String mainFile = workingDir + resource->GetMain();

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::CLuaResourceImpl::" + resource->GetMain());
	Core->LogInfo("ResourcePath: " + workingDir);
	Core->LogInfo("MainFile: " + mainFile);
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

	return true;
}

bool CLuaResourceImpl::Stop()
{

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::Stop");
#endif

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

#ifdef _DEBUG
	//this->_core->LogInfo("CLuaResourceImpl::OnTick");
#endif

}

void CLuaResourceImpl::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::OnCreateBaseObject: " + std::to_string(static_cast<int>(object->GetType())));
#endif

	//object->AddRef();

	//Core->LogInfo("Ref count: " + std::to_string(object->GetRefCount()));

}

void CLuaResourceImpl::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifndef NDEBUG
	Core->LogInfo("CLuaResourceImpl::OnRemoveBaseObject");
#endif

}

bool CLuaResourceImpl::RegisterEvent(std::string eventName, int functionReference)
{
	auto& event = this->eventsReferences[eventName];
	auto& it = std::find(event.begin(), event.end(), functionReference);

	Core->LogInfo("RegisterEvent: " + eventName + " - " + std::to_string(functionReference));

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
	auto &it = std::find(event.begin(), event.end(), functionReference);

	if (it != event.end())
	{
		event.erase(it);

		return true;
	}

	return false;
}
#include <Main.h>

CLuaResourceImpl::CLuaResourceImpl(alt::IResource* resource) :
	resource(resource)
{

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::CLuaResourceImpl");
#endif

}

CLuaResourceImpl::~CLuaResourceImpl()
{

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::~CLuaResourceImpl");
#endif

}

bool CLuaResourceImpl::Start()
{

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::Start");
#endif

	//Create new Lua state
	this->resourceState = luaL_newstate();

	//Import default libraries into the state
	luaL_openlibs(this->resourceState);
	luaopen_jit(this->resourceState);

	lua_pop(this->resourceState, 4);

	lua_initclass(this->resourceState);

	/*lua_State* L = this->resourceState;

	lua_beginclass(L, "Vehicle");

	lua_globalfunction(L, "createVehicle", CLuaVehicleDefs::CreateVehicle);

	lua_endclass(L);*/

	CLuaVector3Defs::Init(this->resourceState);
	CLuaAltFuncDefs::Init(this->resourceState);
	CLuaBaseObjectDefs::Init(this->resourceState);
	CLuaEntityDefs::Init(this->resourceState);
	CLuaVehicleDefs::Init(this->resourceState);

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
		Core->LogInfo(" Unable to load \"" + mainFile + "\"");

		//Get the error from the top of the stack
		if (lua_isstring(this->resourceState, -1))
			Core->LogInfo(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

		//Close virtual machine and point to null pointer
		lua_close(this->resourceState);
		this->resourceState = nullptr;
	}

	return true;
}

bool CLuaResourceImpl::Stop()
{

#ifdef _DEBUG2
	Core->LogInfo("CLuaResourceImpl::Stop");
#endif

	return true;
}

bool CLuaResourceImpl::OnEvent(const alt::CEvent* ev)
{

	if (ev->GetType() == alt::CEvent::Type::RESOURCE_START)
	{
		auto vehicle = Core->CreateVehicle(3078201489, alt::Position(0, 1, 2), alt::Rotation(3, 4, 5));
		if (vehicle.Get() != nullptr)
		{
			auto a = Core->GetVehicles();
			for (auto b : a)
			{
				Core->LogInfo("Vehicle");
			}
		}
	}

#ifdef _DEBUG2
	std::list<std::string>::const_iterator it = this->eventTypes.begin();
	std::advance(it, static_cast<int>(ev->GetType()));

	Core->LogInfo(alt::String("CLuaResourceImpl::OnEvent::") + (*it));
#endif

	return true;
}

void CLuaResourceImpl::OnTick()
{

#ifdef _DEBUG2
	//this->_core->LogInfo("CLuaResourceImpl::OnTick");
#endif

}

void CLuaResourceImpl::OnCreateBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifdef _DEBUG2
	Core->LogInfo("CLuaResourceImpl::OnCreateBaseObject: " + std::to_string(static_cast<int>(object->GetType())));
#endif

	//object->AddRef();

	Core->LogInfo("Ref count: " + std::to_string(object->GetRefCount()));

}

void CLuaResourceImpl::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifdef _DEBUG2
	Core->LogInfo("CLuaResourceImpl::OnRemoveBaseObject");
#endif

}
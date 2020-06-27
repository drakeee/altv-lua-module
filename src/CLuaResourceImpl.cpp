#include "CLuaResourceImpl.h"

CLuaResourceImpl::CLuaResourceImpl(alt::IResource* resource) :
	resource(resource)
{

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::CLuaResourceImpl");
#endif

	//Create new Lua state
	this->resourceState = luaL_newstate();

	//Import default libraries into the state
	luaL_openlibs(this->resourceState);
	lua_initclass(this->resourceState);

	//Initialize alt functions in the state
	CLuaAltFuncDefs::init(this->resourceState);

	//Add path separator to the end
	alt::String workingDir = resource->GetPath() + std::filesystem::path::preferred_separator;
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
		Core->LogInfo(" Unable to load \""+ mainFile +"\"");

		//Get the error from the top of the stack
		if (lua_isstring(this->resourceState, -1))
			Core->LogInfo(" Error: " + alt::String(luaL_checkstring(resourceState, -1)));

		//Close virtual machine and point to null pointer
		lua_close(this->resourceState);
		this->resourceState = nullptr;
	}
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

#ifdef _DEBUG
	std::list<std::string>::const_iterator it = this->eventTypes.begin();
	std::advance(it, static_cast<int>(ev->GetType()));

	Core->LogInfo(alt::String("CLuaResourceImpl::OnEvent::") + (*it));
#endif

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

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::OnCreateBaseObject");
#endif

}

void CLuaResourceImpl::OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object)
{

#ifdef _DEBUG
	Core->LogInfo("CLuaResourceImpl::OnRemoveBaseObject");
#endif

}
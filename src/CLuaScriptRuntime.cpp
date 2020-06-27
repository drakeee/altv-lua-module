#include "CLuaScriptRuntime.h"

alt::IResource::Impl* CLuaScriptRuntime::CreateImpl(alt::IResource* resource)
{

#ifdef _DEBUG
	Core->LogInfo("CLuaScriptRuntime::CreateImpl");
#endif

	return new CLuaResourceImpl(resource);
}

void CLuaScriptRuntime::DestroyImpl(alt::IResource::Impl* impl)
{
	
}
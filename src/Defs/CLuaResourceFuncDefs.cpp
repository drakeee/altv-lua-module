#include <Main.h>

const char* CLuaResourceFuncDefs::ClassName = "Resource";
void CLuaResourceFuncDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "import", GetResourceFromName);
	lua_globalfunction(L, "getResourceFromName", GetResourceFromName);
	lua_globalfunction(L, "isResourceStarted", IsStarted);
	lua_globalfunction(L, "getResourceType", GetType);
	lua_globalfunction(L, "getResourceName", GetName);
	lua_globalfunction(L, "getResourcePath", GetPath);
	lua_globalfunction(L, "getResourceMain", GetMain);
	lua_globalfunction(L, "getResourceExports", GetExports);
	lua_globalfunction(L, "getResourceDependencies", GetDependencies);
	lua_globalfunction(L, "getResourceDependants", GetDependants);

	lua_beginclass(L, ClassName);
	{
		lua_classmeta(L, "__tostring", tostring);
		lua_classmeta(L, "__index", ResourceIndex, true);

		lua_classfunction(L, "getFromName", GetResourceFromName);
		lua_classfunction(L, "isStarted", IsStarted);
		lua_classfunction(L, "getType", GetType);
		lua_classfunction(L, "getName", GetName);
		lua_classfunction(L, "getPath", GetPath);
		lua_classfunction(L, "getMain", GetMain);
		lua_classfunction(L, "getExports", GetExports);
		lua_classfunction(L, "getDependencies", GetDependencies);
		lua_classfunction(L, "getDependants", GetDependants);

		lua_classvariable(L, "started", nullptr, "isStarted");
		lua_classvariable(L, "type", nullptr, "getType");
		lua_classvariable(L, "name", nullptr, "getName");
		lua_classvariable(L, "path", nullptr, "getPath");
		lua_classvariable(L, "main", nullptr, "getMain");
		lua_classvariable(L, "exports", nullptr, "getExports");
		lua_classvariable(L, "dependencies", nullptr, "getDependencies");
		lua_classvariable(L, "dependants", nullptr, "getDependants");
	}
	lua_endclass(L);

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);
	lua_pushresource(L, resource->GetResource());
	lua_setglobal(L, "localResource");
}

int CLuaResourceFuncDefs::Call(lua_State* L)
{
	alt::String functionName(lua_tostring(L, lua_upvalueindex(1)));
	alt::IResource* resource;
	alt::MValueArgs args;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);
	argReader.ReadArguments(args);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto exportedFunctions = resource->GetExports()->Clone().As<alt::IMValueDict>();
	auto function = exportedFunctions->Get(functionName);

	if (function->GetType() != alt::IMValue::Type::FUNCTION)
	{
		Core->LogError("Unable to execute \""+functionName+"\" function from \""+resource->GetName()+"\" resource.");

		lua_pushnil(L);

		return 1;
	}

	auto returnValue = function.As<alt::IMValueFunction>()->Call(args);
	lua_pushmvalue(L, alt::MValueConst(returnValue));

	return 1;
}

int CLuaResourceFuncDefs::ResourceIndex(lua_State* L)
{
	//Route all index accessing to the default handler
	int results = CLuaFunctionDefs::Index(L);
	if (!lua_isnil(L, -1))
	{
		//return results
		return results;
	}

	//pop nil
	lua_pop(L, 1);

	//string expected on top of the stack
	L_ASSERT(lua_isstring(L, -1), "String expected");

	//Store function name in upvalue
	lua_pushcclosure(L, Call, 1);

	//Redirect function
	return 1;
}

int CLuaResourceFuncDefs::tostring(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	alt::StringView type(alt::String("userdata:Resource:") + resource->GetName());
	lua_pushstring(L, type.CStr());

	return 1;
}

int CLuaResourceFuncDefs::GetResourceFromName(lua_State* L)
{
	std::string resourceName;

	CArgReader argReader(L);
	argReader.ReadString(resourceName);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	alt::IResource* resource = Core->GetResource(resourceName);

	if (resource != nullptr)
		lua_pushresource(L, resource);
	else
		lua_pushnil(L);

	return 1;
}

int CLuaResourceFuncDefs::IsStarted(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, resource->IsStarted());

	return 1;
}

int CLuaResourceFuncDefs::GetType(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, resource->GetType().CStr());

	return 1;
}

int CLuaResourceFuncDefs::GetName(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, resource->GetName().CStr());

	return 1;
}

int CLuaResourceFuncDefs::GetPath(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	alt::String p_s(preferred_separator);
	lua_pushstring(L, (resource->GetPath() + p_s).CStr());

	return 1;
}

int CLuaResourceFuncDefs::GetMain(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, resource->GetMain().CStr());

	return 1;
}

int CLuaResourceFuncDefs::GetExports(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_newtable(L);
	int index = 1;

	for (auto it = resource->GetExports()->Begin(); it; it = resource->GetExports()->Next())
	{
		lua_pushnumber(L, index);
		lua_pushstring(L, it->GetKey().CStr());
		lua_rawset(L, -3);

		index++;
	}

	return 1;
}

int CLuaResourceFuncDefs::GetDependencies(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstringarray(L, const_cast<alt::Array<alt::StringView>&&>(resource->GetDependencies()));

	return 1;
}

int CLuaResourceFuncDefs::GetDependants(lua_State* L)
{
	alt::IResource* resource;

	CArgReader argReader(L);
	argReader.ReadUserData(resource);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstringarray(L, const_cast<alt::Array<alt::StringView>&&>(resource->GetDependants()));

	return 1;
}
#include <Main.h>

namespace lua::Class
{
	const char* Resource::ClassName = "Resource";
	void Resource::Init(lua_State* L)
	{
		DEBUG_INFO("Resource::Init");

		lua_globalfunction(L, "import", GetResourceByName);
		lua_globalfunction(L, "getResourceByName", GetResourceByName);
		lua_globalfunction(L, "isResourceStarted", IsStarted);
#ifdef ALT_SERVER_API
		lua_globalfunction(L, "getResourceConfig", GetConfig);
#endif
		lua_globalfunction(L, "getResourceType", GetType);
		lua_globalfunction(L, "getResourceName", GetName);
		lua_globalfunction(L, "getResourcePath", GetPath);
		lua_globalfunction(L, "getResourceMain", GetMain);
		lua_globalfunction(L, "getResourceExports", GetExports);
		lua_globalfunction(L, "getResourceDependencies", GetDependencies);
		lua_globalfunction(L, "getResourceDependants", GetDependants);
		lua_globalfunction(L, "getResourceRequiredPermissions", GetRequiredPermissions);
		lua_globalfunction(L, "getResourceOptionalPermissions", GetOptionalPermissions);

		lua_beginclass(L, ClassName);
		{
			lua_classmeta(L, "__tostring", tostring);
			lua_classmeta(L, "__index", ResourceIndex, true);
			lua_classmeta(L, "__pairs", pairs);
			lua_classmeta(L, "__ipairs", ipairs);

			lua_classfunction(L, "getByName", GetResourceByName);
			lua_classfunction(L, "isStarted", IsStarted);
#ifdef ALT_SERVER_API
			lua_classfunction(L, "getConfig", GetConfig);
#endif
			lua_classfunction(L, "getType", GetType);
			lua_classfunction(L, "getName", GetName);
			lua_classfunction(L, "getPath", GetPath);
			lua_classfunction(L, "getMain", GetMain);
			lua_classfunction(L, "getExports", GetExports);
			lua_classfunction(L, "getDependencies", GetDependencies);
			lua_classfunction(L, "getDependants", GetDependants);
			lua_classfunction(L, "getRequiredPermissions", GetRequiredPermissions);
			lua_classfunction(L, "getOptionalPermissions", GetOptionalPermissions);

			lua_classvariable(L, "started", nullptr, "isStarted");
#ifdef ALT_SERVER_API
			lua_classvariable(L, "config", nullptr, "getConfig");
#endif
			lua_classvariable(L, "type", nullptr, "getType");
			lua_classvariable(L, "name", nullptr, "getName");
			lua_classvariable(L, "path", nullptr, "getPath");
			lua_classvariable(L, "main", nullptr, "getMain");
			lua_classvariable(L, "exports", nullptr, "getExports");
			lua_classvariable(L, "dependencies", nullptr, "getDependencies");
			lua_classvariable(L, "dependants", nullptr, "getDependants");
			lua_classvariable(L, "requiredPermissions", nullptr, "getRequiredPermissions");
			lua_classvariable(L, "optionalPermissions", nullptr, "getOptionalPermissions");
		}
		lua_endclass(L);

		auto runtime = &CLuaScriptRuntime::Instance();
		auto resource = runtime->GetResourceImplFromState(L);
		lua_pushresource(L, resource->GetResource());
		lua_setglobal(L, "localResource");

		DEBUG_INFO("Resource::Init ...done");
	}

	int Resource::Call(lua_State* L)
	{
		alt::String functionName(lua_tostring(L, lua_upvalueindex(1)));
		alt::IResource* resource;
		alt::MValueArgs args;

		ArgumentReader argReader(L);
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
			Core->LogError("Unable to execute \"" + functionName + "\" function from \"" + resource->GetName() + "\" resource.");

			lua_pushnil(L);

			return 1;
		}

		auto returnValue = function.As<alt::IMValueFunction>()->Call(args);
		lua_pushmvalue(L, alt::MValueConst(returnValue));

		return 1;
	}

	int Resource::ResourceIndex(lua_State* L)
	{
		luaL_dostring(L, lua_meta_script);
		lua_getfield(L, -1, "__index");

		if (lua_isfunction(L, -1))
		{
			lua_pushvalue(L, 1);
			lua_pushvalue(L, 2);

			int stack = lua_gettop(L) - 1;
			lua_call(L, 2, LUA_MULTRET);

			if (!lua_isnil(L, -1))
				return (stack - lua_gettop(L));
		}

		//Pop result and metatable from the stack
		lua_pop(L, 2);

		L_ASSERT(lua_isstring(L, -1), "String expected");

		//Store function name in upvalue
		lua_pushcclosure(L, Call, 1);

		//Redirect function
		return 1;
	}

	int Resource::pairs(lua_State* L)
	{
		return 0;
	}

	int Resource::ipairs(lua_State* L)
	{
		lua_newtable(L);
		auto allResources = alt::ICore::Instance().GetAllResources();

		for (size_t i = 0; i < allResources.size(); i++)
		{
			lua_pushnumber(L, (int)(i + 1));
			lua_pushresource(L, allResources[i]);
			lua_rawset(L, -3);
		}

		return 1;
	}

	int Resource::tostring(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
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

	int Resource::GetResourceByName(lua_State* L)
	{
		std::string resourceName;

		ArgumentReader argReader(L);
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

	int Resource::IsStarted(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, resource->IsStarted());

		return 1;
	}

#ifdef ALT_SERVER_API
	int Resource::GetConfig(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushconfig(L, &CLuaScriptRuntime::Instance().GetResourceConfig(resource));

		return 1;
	}
#endif

	int Resource::GetType(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, resource->GetType().CStr());

		return 1;
	}

	int Resource::GetName(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, resource->GetName().CStr());

		return 1;
	}

	int Resource::GetPath(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
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

	int Resource::GetMain(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, resource->GetMain().CStr());

		return 1;
	}

	int Resource::GetExports(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
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

	int Resource::GetDependencies(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstringarray(L, const_cast<alt::Array<alt::StringView>&&>(resource->GetDependencies()));

		return 1;
	}

	int Resource::GetDependants(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstringarray(L, const_cast<alt::Array<alt::StringView>&&>(resource->GetDependants()));

		return 1;
	}

	int Resource::GetRequiredPermissions(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto requiredPermissions = resource->GetRequiredPermissions();
		lua_newtable(L);

		unsigned short index = 1;
		for (auto& perm : requiredPermissions)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, static_cast<int>(perm));
			lua_rawset(L, -3);

			index++;
		}

		return 1;
	}

	int Resource::GetOptionalPermissions(lua_State* L)
	{
		alt::IResource* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto optionalPermissions = resource->GetOptionalPermissions();
		lua_newtable(L);

		unsigned short index = 1;
		for (auto& perm : optionalPermissions)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, static_cast<int>(perm));
			lua_rawset(L, -3);

			index++;
		}

		return 1;
	}
}
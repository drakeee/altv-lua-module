#include <Main.h>

void lua_initclass(lua_State* L)
{
	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "es"); //entity storage -> this will store all the entities reference

	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "e_mt"); //entity metatable -> this will store all entities functions, metaevents, etc

#ifdef ALT_CLIENT_API
	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "_LOADED_PACKAGE");
#endif
}

void lua_globalfunction(lua_State* L, const char* functionName, lua_CFunction func)
{
	lua_register(L, functionName, func);
}

void lua_mergetable(lua_State* L, int fromTable, int toTable)
{
	lua_pushnil(L);
	while (lua_next(L, fromTable - 1))
	{
		lua_pushvalue(L, -2);
		lua_insert(L, -3);

		lua_rawset(L, toTable - 3);
	}
}

void lua_removedata(lua_State* L, alt::IBaseObject* baseObject)
{
	lua_pushbaseobject(L, baseObject);
	lua_getmetatable(L, -1);

	lua_getfield(L, -1, "__data");
	lua_pushbaseobject(L, baseObject);
	lua_pushnil(L);
	lua_rawset(L, -3);

	lua_pop(L, 3);
}

void lua_disablelib(lua_State* L, const char* libName)
{
	lua_pushnil(L);
	lua_setglobal(L, libName);
}

void lua_disablefunction(lua_State* L, const char* functionName)
{
	lua_register(L, functionName, CLuaFunctionDefs::DisabledFunction);
}

int lua_setpath(lua_State* L, const char* path)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
	cur_path.append(";"); // do your path magic here
	cur_path.append(path);
	lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(L, cur_path.c_str()); // push the new one
	lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(L, 1); // get rid of package table from top of stack
	return 0; // all done!
}

void lua_beginclass(lua_State* L, const char* className, const char* baseClass)
{
	//lua_getfield(L, LUA_REGISTRYINDEX, "e_mt");
	lua_pushstring(L, "e_mt");
	lua_rawget(L, LUA_REGISTRYINDEX);

	lua_pushstring(L, className);
	lua_newtable(L);

	lua_pushstring(L, "__name");
	lua_pushstring(L, className);
	lua_rawset(L, -3);

	lua_pushstring(L, "__class");
	lua_newtable(L);
	lua_rawset(L, -3);

	lua_pushstring(L, "__set");
	lua_newtable(L);
	lua_rawset(L, -3);

	lua_pushstring(L, "__get");
	lua_newtable(L);
	lua_rawset(L, -3);

	lua_pushstring(L, "__data");
	lua_newtable(L);
	lua_rawset(L, -3);

	lua_pushstring(L, "__base");
	if (baseClass == nullptr)
		lua_pushboolean(L, false);
	else
	{
		lua_getclass(L, baseClass);
		L_ASSERT(lua_istable(L, -1), "lua_beginclass: Implementing \"" + alt::String(className) + "\" class. Error: base class \"" + alt::String(baseClass) + "\" not found.");

		lua_getfield(L, -1, "__get");
		lua_getfield(L, -4, "__get");
		lua_mergetable(L, -2, -1);
		lua_pop(L, 2);

		lua_getfield(L, -1, "__set");
		lua_getfield(L, -4, "__set");
		lua_mergetable(L, -2, -1);
		lua_pop(L, 2);

		lua_getfield(L, -1, "__class");
		lua_getfield(L, -4, "__class");
		lua_mergetable(L, -2, -1);
		lua_pop(L, 2);

		lua_pop(L, 1);
		lua_pushstring(L, baseClass);
	}

	lua_rawset(L, -3);
}

const char* lua_meta_script = R"(
local metaTable = {}
metaTable.__index = function(t, k)
	local meta = getmetatable(t)
	if meta.__class[k] then
		return meta.__class[k]
	end

	if meta.__get[k] then
		return meta.__get[k](t)
	end

	if meta.__data[t] == nil then
		return nil
	end

	return meta.__data[t][k]
end

metaTable.__newindex = function(t, k, v)
	local meta = getmetatable(t)
	if meta.__set[k] then
		meta.__set[k](t, v)
		return
	end

	if meta.__data[t] == nil then
		meta.__data[t] = {}
	end

	meta.__data[t][k] = v
end

return metaTable
)";

void lua_endclass(lua_State* L)
{
	lua_classmeta(L, "__call", CLuaFunctionDefs::Call);
	
	luaL_dostring(L, lua_meta_script);
	lua_getfield(L, -2, "__index");
	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_getfield(L, -1, "__index");
		lua_setfield(L, -3, "__index");
	} else
		lua_pop(L, 1);

	lua_getfield(L, -2, "__newindex");
	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_getfield(L, -1, "__newindex");
		lua_setfield(L, -3, "__newindex");
	}
	else
		lua_pop(L, 1);

	/*lua_getfield(L, -1, "__index");
	lua_setfield(L, -3, "__index");
	lua_getfield(L, -1, "__newindex");
	lua_setfield(L, -3, "__newindex");*/
	lua_pop(L, 1);

	//lua_classmeta(L, "__index", CLuaFunctionDefs::Index, true);
	//lua_classmeta(L, "__newindex", CLuaFunctionDefs::NewIndex, true);

	lua_newtable(L);
	lua_pushvalue(L, -2);
	lua_setmetatable(L, -2);
	L_ASSERT(lua_isstring(L, -3), "lua_endclass: String not found at position -3");
	lua_setglobal(L, luaL_checkstring(L, -3));

	lua_rawset(L, -3);
	lua_pop(L, 1);
}

void lua_getclass(lua_State* L, const char* className)
{
	lua_pushstring(L, "e_mt");
	lua_rawget(L, LUA_REGISTRYINDEX);

#ifdef _DEBUG
	//lua_stacktrace(L, "lua_getclass1");
#endif

	assert(lua_istable(L, -1));

	lua_pushstring(L, className);
	lua_rawget(L, -2);

	lua_remove(L, -2);

#ifdef _DEBUG
	//lua_stacktrace(L, "lua_getclass2");
#endif
}

void lua_getclassmt(lua_State* L, const char* className)
{
	lua_getclass(L, className);

	//lua_stacktrace(L, "lua_getclassmt");
}

void lua_classfunction(lua_State* L, const char* functionName, const char* globalFuncName)
{
	//lua_getfield(L, -1, "__class");
	lua_pushstring(L, "__class");
	lua_rawget(L, -2);
	
	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__class\" table not found");
	
	lua_pushstring(L, functionName);
	lua_getglobal(L, globalFuncName);

	L_ASSERT(lua_isfunction(L, -1), "lua_classfunction: \"" + alt::String(globalFuncName) + "\" global function not found");

	lua_rawset(L, -3);

	//lua_stacktrace(L, "lua_classfunction");

	lua_pop(L, 1);
}

void lua_classfunction(lua_State* L, const char* functionName, lua_CFunction function)
{
	//lua_getfield(L, -1, "__class"); //__class table, class meta
	lua_pushstring(L, "__class");
	lua_rawget(L, -2);

	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__class\" table not found");

	lua_pushstring(L, functionName); //function name, __class table, class meta
	lua_pushcfunction(L, function); //cfunction, function name, __class table, class meta
	lua_rawset(L, -3); //----------------------------------------------^

	lua_pop(L, 1);
	//lua_stacktrace(L, "lua_classfunction::CFunction");
}

void lua_classnative(lua_State* L, const char* functionName, lua_CFunction function, void* native)
{
	//lua_getfield(L, -1, "__class"); //__class table, class meta
	lua_pushstring(L, "__class");
	lua_rawget(L, -2);

	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__class\" table not found");

	lua_pushstring(L, functionName);
	lua_pushlightuserdata(L, native);
	lua_pushcclosure(L, function, 1);

	//lua_pushstring(L, functionName); //function name, __class table, class meta
	//lua_pushcfunction(L, function); //cfunction, function name, __class table, class meta
	lua_rawset(L, -3); //----------------------------------------------^

	lua_pop(L, 1);
	//lua_stacktrace(L, "lua_classfunction::CFunction");
}

void lua_classmeta(lua_State* L, const char* metaName, lua_CFunction metaFunction, bool useClosure)
{
	//lua_getfield(L, -1, "__meta");

	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__meta\" table not found");

	lua_pushstring(L, metaName);
	lua_rawget(L, -2);

	//check if metafield exists
	if (!lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		return;
	}

	lua_pop(L, 1);

	lua_pushstring(L, metaName);
	if (useClosure)
	{
		lua_pushvalue(L, -2); //1
		lua_getfield(L, -1, "__set"); //2
		lua_getfield(L, -2, "__get"); //3
		lua_getfield(L, -3, "__class"); //4
		lua_getfield(L, -4, "__data"); //5
		lua_pushcclosure(L, metaFunction, 5);
	} else
		lua_pushcfunction(L, metaFunction);

	lua_rawset(L, -3);

	//lua_stacktrace(L, "lua_classmeta");

	//lua_pop(L, 1);
}

void lua_classvariable(lua_State* L, const char* variableName, lua_CFunction setFunction, lua_CFunction getFunction)
{
	lua_pushstring(L, "__class");
	lua_rawget(L, -2);
	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__class\" table not found");

	if (setFunction != nullptr)
	{
		//lua_getfield(L, -2, "__set"); //__set, __class, class meta
		lua_pushstring(L, "__set");
		lua_rawget(L, -3);

		lua_pushstring(L, variableName); //variable name, __set, __class, class meta
		lua_pushcfunction(L, setFunction);

		lua_rawset(L, -3); //__set, __class, class meta
		lua_pop(L, 1); //__class, class meta
	}

	if (getFunction != nullptr)
	{
		//lua_getfield(L, -2, "__get"); //__get, __class, class meta
		lua_pushstring(L, "__get");
		lua_rawget(L, -3);

		lua_pushstring(L, variableName); //variable name, __get, __class, class meta
		lua_pushcfunction(L, getFunction);

		lua_rawset(L, -3); //__get, __class, class meta
		lua_pop(L, 1); //__class, class meta
	}

	lua_pop(L, 1); //class meta
}

void lua_classvariable(lua_State* L, const char* variableName, const char* setFunction, const char* getFunction)
{
	//class meta
	//lua_getfield(L, -1, "__class"); //__class, class meta
	lua_pushstring(L, "__class");
	lua_rawget(L, -2);
	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__class\" table not found");

	if (setFunction != nullptr)
	{
		//lua_getfield(L, -2, "__set"); //__set, __class, class meta
		lua_pushstring(L, "__set");
		lua_rawget(L, -3);

		lua_pushstring(L, variableName); //variable name, __set, __class, class meta
		//lua_getfield(L, -3, setFunction); //-------------------------^ | function, variable name, __set, __class, class meta
		lua_pushstring(L, setFunction);
		lua_rawget(L, -4);

		L_ASSERT(lua_isfunction(L, -1), "lua_classvariable::set: Could not find \"" + alt::String(setFunction) + "\" function in \"" + alt::String(luaL_checkstring(L, 2)) + "\" class");

		lua_rawset(L, -3); //__set, __class, class meta
		lua_pop(L, 1); //__class, class meta
	}

	if (getFunction != nullptr)
	{
		//lua_getfield(L, -2, "__get"); //__get, __class, class meta
		lua_pushstring(L, "__get");
		lua_rawget(L, -3);

		lua_pushstring(L, variableName); //variable name, __get, __class, class meta
		//lua_getfield(L, -3, getFunction); //-------------------------^ | function, variable name, __set, __class, class meta
		lua_pushstring(L, getFunction);
		lua_rawget(L, -4);

		L_ASSERT(lua_isfunction(L, -1), "lua_classvariable::get: Could not find \"" + alt::String(getFunction) + "\" function in \"" + alt::String(luaL_checkstring(L, 2)) + "\" class");

		lua_rawset(L, -3); //__get, __class, class meta
		lua_pop(L, 1); //__class, class meta
	}

	lua_pop(L, 1); //class meta
}

void lua_pushuserdata(lua_State* L, const char* className, void* pObject, bool refUserData)
{
	if (refUserData)
	{
		lua_pushstring(L, "es");
		lua_rawget(L, LUA_REGISTRYINDEX);
		//lua_getfield(L, LUA_REGISTRYINDEX, "es"); //es table
		L_ASSERT(lua_istable(L, -1), "lua_pushuserdata: \"es\" not found in Lua registry");

		lua_pushlightuserdata(L, pObject); //object pointer, es table
		lua_rawget(L, -2); //-----------------------------------^

		if (lua_isnil(L, -1))
		{
			//nil, es table
			lua_pop(L, 1); //pop nil results on top of the stack - es table

			void** tempUserData = reinterpret_cast<void**>(lua_newuserdata(L, sizeof(void*))); //userdata, es table
			*tempUserData = pObject;

			lua_pushlightuserdata(L, pObject); //pointer, userdata, es table
			lua_pushvalue(L, -2); //userdata, pointer, userdata, es table
			lua_rawset(L, -4); //-----------------------------------^

			//userdata, es table
		}
		else
		{
			//if userdata already exist we don't need to apply metatable
			lua_remove(L, -2);
			return;
		}

		lua_remove(L, -2); //userdata
	}
	else
	{
		void** tempUserData = reinterpret_cast<void**>(lua_newuserdata(L, sizeof(void*)));
		*tempUserData = pObject;
	}

	lua_getclassmt(L, className); //class meta, userdata
	L_ASSERT(lua_istable(L, -1), "lua_pushuserdata: Couldn't find \"" + alt::String(className) + "\" class");

	lua_setmetatable(L, -2); //apply metatable to userdata
}

//void lua_pushvector(lua_State* L, Vector3fp& vector, bool refUserData)
//{
//	Vector3fp* vec = new Vector3fp(vector);
//	lua_pushuserdata(L, CLuaVector3Defs::ClassName, vec, refUserData);
//}

void lua_pushbaseobject(lua_State* L, alt::IBaseObject* baseObject, bool refUserData)
{
	if (baseObject == nullptr)
		lua_pushnil(L);
	else
	{
		CLuaScriptRuntime* runtime = &CLuaScriptRuntime::Instance();
		lua_pushuserdata(L, runtime->GetBaseObjectType(baseObject->GetType()).c_str(), baseObject, refUserData);
	}
}

void lua_pushbaseobject(lua_State* L, alt::Ref<alt::IBaseObject> baseObject, bool refUserData)
{
	lua_pushbaseobject(L, baseObject.Get(), refUserData);
}

#ifdef ALT_CLIENT_API
void lua_pushmapdata(lua_State* L, alt::IMapData* mapData, bool refUserData)
{
	lua_pushuserdata(L, CLuaMapDataDefs::ClassName, mapData, refUserData);
}

void lua_pushmapdata(lua_State* L, alt::Ref<alt::IMapData> mapData, bool refUserData)
{
	lua_pushmapdata(L, mapData.Get(), refUserData);
}

void lua_pushhandlingdata(lua_State* L, alt::Ref<alt::IHandlingData> handlingData, bool refUserData)
{
	lua_pushhandlingdata(L, handlingData.Get(), refUserData);
}

void lua_pushhandlingdata(lua_State* L, alt::IHandlingData* handlingData, bool refUserData)
{
	lua_pushuserdata(L, CLuaHandlingDataDefs::ClassName, handlingData, refUserData);
}

void lua_pushwebview(lua_State* L, alt::IWebView* webView, bool refUserData)
{
	lua_pushuserdata(L, CLuaWebViewDefs::ClassName, webView, refUserData);
}
#endif

void lua_pushconfig(lua_State* L, alt::config::Node::Dict* nodeDict, bool refUserData)
{
	lua_pushuserdata(L, CLuaConfigDefs::ClassName, nodeDict, refUserData);
}

void lua_pushstring(lua_State* L, alt::String& str)
{
	lua_pushstring(L, str.CStr());
}

void lua_pushstring(lua_State* L, alt::StringView& str)
{
	lua_pushstring(L, str.CStr());
}

void lua_pushvector2(lua_State* L, Vector2fp* vector, bool refUserData)
{
	lua_pushuserdata(L, CLuaVector2Defs::ClassName, vector, refUserData);
}

void lua_pushvector2(lua_State* L, const Vector2fp& vector, bool refUserData)
{
	Vector2fp* vec = new Vector2fp(vector);
	lua_pushvector2(L, vec, refUserData);
}

void lua_pushvector3(lua_State* L, Vector3fp* vector, bool refUserData)
{
	lua_pushuserdata(L, CLuaVector3Defs::ClassName, vector, refUserData);
}

void lua_pushvector3(lua_State* L, const Vector3fp& vector, bool refUserData)
{
	Vector3fp* vec = new Vector3fp(vector);
	lua_pushvector3(L, vec, refUserData);
}

void lua_pushrgba(lua_State* L, const alt::RGBA& color, bool refUserData)
{
	alt::RGBA* tempColor = new alt::RGBA(color);
	lua_pushuserdata(L, CLuaRGBADefs::ClassName, tempColor, refUserData);
}

void lua_pushmvalue(lua_State* L, const alt::MValueConst &mValue)
{
	switch (mValue->GetType())
	{
	case alt::IMValue::Type::NIL:
	case alt::IMValue::Type::NONE:
		lua_pushnil(L);
		break;
	case alt::IMValue::Type::BOOL:
		lua_pushboolean(L, mValue.As<alt::IMValueBool>()->Value());
		break;
	case alt::IMValue::Type::INT:
		lua_pushnumber(L, static_cast<int32_t>(mValue.As<alt::IMValueInt>()->Value()));
		break;
	case alt::IMValue::Type::UINT:
		lua_pushnumber(L, static_cast<uint32_t>(mValue.As<alt::IMValueUInt>()->Value()));
		break;
	case alt::IMValue::Type::DOUBLE:
		lua_pushnumber(L, mValue.As<alt::IMValueDouble>()->Value());
		break;
	case alt::IMValue::Type::STRING:
		lua_pushstring(L, mValue.As<alt::IMValueString>()->Value().CStr());
		break;
	case alt::IMValue::Type::BASE_OBJECT:
		lua_pushbaseobject(L, mValue.As<alt::IMValueBaseObject>()->Value().Get());
		break;
	case alt::IMValue::Type::LIST:
	{
		auto list = mValue.As<alt::IMValueList>();

		lua_newtable(L);
		for (uint32_t i = 0; i < list->GetSize(); ++i)
		{
			lua_pushnumber(L, i + 1);
			lua_pushmvalue(L, list->Get(i));
			lua_rawset(L, -3);
		}

		break;
	}
	case alt::IMValue::Type::DICT:
	{
		auto dict = mValue.As<alt::IMValueDict>();

		lua_newtable(L);
		for (auto it = dict->Begin(); it; it = dict->Next())
		{
			lua_pushstring(L, it->GetKey().CStr());
			lua_pushmvalue(L, it->GetValue());
			lua_rawset(L, -3);
		}

		break;
	}
	case alt::IMValue::Type::FUNCTION:
	{
		lua_newtable(L);
		lua_newtable(L);
		lua_pushlightuserdata(L, (void*)mValue.As<alt::IMValueFunction>().Get());
		lua_pushcclosure(L, CLuaFunctionDefs::FunctionCallback, 1);
		lua_setfield(L, -2, "__call");
		lua_setmetatable(L, -2);

		break;
	}
	default:
		Core->LogError("lua_pushmvalue: Unhandled IMValue type: " + std::to_string(static_cast<int>(mValue->GetType())));
		break;
	}
}

void lua_pushnode(lua_State* L, alt::config::Node& node)
{
	switch (node.GetType())
	{
	case alt::config::Node::Type::DICT:
	{
		auto dict = node.ToDict();

		lua_newtable(L);
		for (auto it = dict.begin(); it != dict.end(); ++it)
		{
			lua_pushstring(L, it->first.c_str());
			lua_pushnode(L, it->second);
			lua_rawset(L, -3);
		}

		break;
	}
	case alt::config::Node::Type::LIST:
	{
		alt::config::Node::List list;
		try
		{
			list = node.ToList();
		}
		catch (alt::config::Error exception)
		{
			Core->LogError(" Unable to convert config node to list!");
		}

		lua_newtable(L);
		for (uint32_t i = 0; i < list.size(); ++i)
		{
			lua_pushnumber(L, i + 1);
			lua_pushnode(L, list[i]);
			lua_rawset(L, -3);
		}

		break;
	}
	case alt::config::Node::Type::SCALAR:
	{
		lua_pushstring(L, node.ToString().c_str());

		break;
	}
	default:
	{
		break;
	}
	}
}

void lua_pushmvalueargs(lua_State* L, alt::MValueArgs& args)
{
	for (auto arg : args)
	{
		lua_pushmvalue(L, arg);
	}
}

void lua_pushstringarray(lua_State* L, const alt::Array<alt::StringView>& array)
{
	lua_newtable(L);
	uint32_t index = 1;
	for (auto item : array)
	{
		lua_pushnumber(L, index);
		lua_pushstring(L, item.CStr());
		lua_rawset(L, -3);

		index++;
	}
}

void lua_pushresource(lua_State* L, alt::IResource* resource, bool refUserData)
{
	if (resource == nullptr)
		lua_pushnil(L);
	else
		lua_pushuserdata(L, CLuaResourceFuncDefs::ClassName, resource, refUserData);
}

int lua_functionref(lua_State* L, int idx)
{
	if (!lua_isfunction(L, idx))
		return LUA_NOREF;

	lua_pushvalue(L, idx);
	const void* ptr = lua_topointer(L, -1);

	auto runtime = &CLuaScriptRuntime::Instance();
	auto resource = runtime->GetResourceImplFromState(L);
	int ref = resource->GetFunctionRef(ptr);

	if (ref == LUA_NOREF)
	{
		ref = luaL_ref(L, LUA_REGISTRYINDEX);
		resource->AddFunctionRef(ptr, ref);
	}
	
	return ref;
}

//void lua_pushentity(lua_State* L, alt::IEntity* entity)
//{
//	switch (entity->GetType())
//	{
//	case alt::IBaseObject::Type::PLAYER:
//		lua_pushbaseobject(L, entity);
//		break;
//	}
//}

alt::IBaseObject* lua_tobaseobject(lua_State* L, int idx)
{
	return reinterpret_cast<alt::IBaseObject*>(*((void**)lua_touserdata(L, idx)));
}


int lua_isinteger(lua_State* L, int index)
{
	int32_t x = (int32_t)lua_tointeger(L, index);
	lua_Number n = lua_tonumber(L, index);
	return ((lua_Number)x == n);
}

alt::MValue lua_tomvalue(lua_State* L, int idx)
{
	alt::MValue mValue;

	int argType = lua_type(L, idx);
	switch (argType)
	{
	case LUA_TNUMBER:
		if (lua_isinteger(L, idx))
			mValue = Core->CreateMValueInt(lua_tointeger(L, idx));
		else
			mValue = Core->CreateMValueDouble(lua_tonumber(L, idx));
		break;
	case LUA_TBOOLEAN:
		mValue = Core->CreateMValueBool(lua_toboolean(L, idx));
		break;
	case LUA_TSTRING:
		mValue = Core->CreateMValueString(lua_tostring(L, idx));
		break;
	case LUA_TUSERDATA:
		mValue = Core->CreateMValueBaseObject(lua_tobaseobject(L, idx));
		break;
	case LUA_TTABLE:
	{
		auto tempDict = Core->CreateMValueDict();
		auto tempList = Core->CreateMValueList();

		lua_pushvalue(L, idx);
		lua_pushnil(L);

		while (lua_next(L, -2))
		{
			lua_pushvalue(L, -2);
			
			const char* key = lua_tostring(L, -1);
			auto value = lua_tomvalue(L, -2);

			tempDict->Set(key, value.Get()->Clone());

			if (lua_isnumber(L, -1))
			{
				tempList->Push(value.Get()->Clone());
			}

			lua_pop(L, 2);
		}

		lua_pop(L, 1);

		if (tempList->GetSize() == tempDict->GetSize())
		{
			mValue = tempList.Get()->Clone();
		}
		else
		{
			mValue = tempDict.Get()->Clone();
		}

		break;
	}
	case LUA_TFUNCTION:
	{
		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		auto functionRef = lua_functionref(L, idx);
		mValue = Core->CreateMValueFunction(new CLuaResourceImpl::LuaFunction(resourceImpl, functionRef));

		break;
	}
	case LUA_TNIL:
		mValue = Core->CreateMValueNil();
		break;
	default:
		Core->LogError("ReadMValue: Unexpected Lua type: " + alt::String(lua_typename(L, argType)));
		break;
	}

	return mValue;
}

void lua_todict(lua_State* L, int idx)
{
	lua_pushvalue(L, idx);
	lua_pushnil(L);

	while (lua_next(L, -2))
	{
		lua_pushvalue(L, -2);
		// stack now contains: -1 => key; -2 => value; -3 => key; -4 => table



		//const char* key = lua_tostring(L, -1);
		//const char* value = lua_tostring(L, -2);
		//printf("%s => %s\n", key, value);
		// pop value + copy of key, leaving original key
		lua_pop(L, 2);
	}
}

void lua_stacktrace(lua_State* L, const char* stackName)
{
	int stackTop = lua_gettop(L);

	Core->LogInfo(" --------- Stack Begins: " + alt::String(stackName) + "---------");
	for (int i = stackTop; i >= 1; i--)
	{
		int valueType = lua_type(L, i);
		int relativePosition = ((i - stackTop) - 1);

		switch (valueType)
		{
		case LUA_TSTRING:
			Core->LogInfo("\tAbsolute: " + std::to_string(i) + " ~~ Relative: " + std::to_string(relativePosition) + " ~~\t Value: '" + luaL_checkstring(L, i) + "'");
			break;
		case LUA_TBOOLEAN:
			Core->LogInfo("\tAbsolute: " + std::to_string(i) + " ~~ Relative: " + std::to_string(relativePosition) + " ~~\t Value: '" + (lua_toboolean(L, i) ? ("true") : ("false")) + "'");
			break;
		case LUA_TNUMBER:
			Core->LogInfo("\tAbsolute: " + std::to_string(i) + " ~~ Relative: " + std::to_string(relativePosition) + " ~~\t Value: '" + std::to_string(luaL_checknumber(L, i)) + "'");
			break;
		case LUA_TTABLE:
			Core->LogInfo("\tAbsolute: " + std::to_string(i) + " ~~ Relative: " + std::to_string(relativePosition) + " ~~\t Value '" + lua_typename(L, valueType) + "'");
			Core->LogInfo("\t{");

			lua_dumptable(L, i, 2);

			Core->LogInfo("\t}");
			/*lua_pushnil(L);
			while (lua_next(L, i) != 0)
			{
			Core->LogInfo("%s => %s", lua_tostring(L, -2), lua_tostring(L, -1));
			lua_pop(L, 1);
			}*/

			break;
		default:
			Core->LogInfo("\tAbsolute: " + std::to_string(i) + " ~~ Relative: " + std::to_string(relativePosition) + " ~~\t Value type: " + lua_typename(L, valueType) + "");
			break;
		}
	}
	Core->LogInfo(" --------- Stack Ends: " + alt::String(stackName) + " ---------");
}

void lua_dumptable(lua_State* L, int idx, int level)
{
	std::string levelTab;
	levelTab.insert(0, level, '\t');

	lua_pushnil(L);  /* first key */
	while (lua_next(L, idx) != 0)
	{
		//we need to copy the key and value so lua_tostring will not convert it to other type
		lua_pushvalue(L, -2);

		//check if value is table
		if (lua_istable(L, -2))
		{
			//make it beautifully aligned
			Core->LogInfo(levelTab + luaL_tolstring(L, -1, NULL) + " => Table");
			Core->LogInfo(levelTab + "{");

			lua_pop(L, 1);

			//for some reason we need to pass the original table and not the referenced one (recursive call)
			lua_dumptable(L, -3, level + 1);

			//make it beautifuly aligned
			Core->LogInfo(levelTab + "}");
		}
		else
		{
			//note: lua_tostring will crash if userdata doesn't have any __tostring metaevent implemented
			std::string stackKey(lua_isstring(L, -1) ? lua_tostring(L, -1) : lua_typename(L, lua_type(L, -1)));
			std::string stackValue(lua_isstring(L, -2) ? lua_tostring(L, -2) : lua_typename(L, lua_type(L, -2)));
			Core->LogInfo(levelTab + stackKey + " => " + stackValue + ",");
		}

		lua_pop(L, 2);
	}
}

void lua_getdebuginfo(lua_State* L, lua_Debug& debugInfo)
{
	//lua_Debug debugInfo;
	const char* nameTemp = nullptr;

	for (int level = 0; level <= 4; level++)
	{
		//get info about interpreter stack
		int stackInfo = lua_getstack(L, level, &debugInfo);

		//if there is no information then stop loop
		if (stackInfo == 0)
			break;

		//get info about function
		lua_getinfo(L, "nSl", &debugInfo);

		//if we got a function name then store it
		if (debugInfo.name != nullptr)
		{
			nameTemp = debugInfo.name;
		}

		//if we don't have the currentline then it means we need to go deeper
		if (debugInfo.currentline == -1)
			continue;
		else
		{
			//load the stored function name into the struct
			debugInfo.name = nameTemp;
			break;
		}
	}
}

const char* luaL_tolstring(lua_State* L, int idx, size_t* len)
{
	if (luaL_callmeta(L, idx, "__tostring"))
	{
		if (!lua_isstring(L, -1))
			luaL_error(L, "'__tostring' must return a string");
	}
	else {
		switch (lua_type(L, idx)) {
		case LUA_TNUMBER: {
			if (lua_isinteger(L, idx))
				lua_pushfstring(L, "%d", lua_tointeger(L, idx));
			else
				lua_pushfstring(L, "%f", lua_tonumber(L, idx));
			break;
		}
		case LUA_TSTRING:
			lua_pushvalue(L, idx);
			break;
		case LUA_TBOOLEAN:
			lua_pushstring(L, (lua_toboolean(L, idx) ? "true" : "false"));
			break;
		case LUA_TNIL:
			lua_pushliteral(L, "nil");
			break;
		default: {
			int tt = luaL_getmetafield(L, idx, "__name");  /* try name */
			const char* kind = (tt == LUA_TSTRING) ? lua_tostring(L, -1) :
				luaL_typename(L, idx);
			lua_pushfstring(L, "%s: %p", kind, lua_topointer(L, idx));
			if (tt != LUA_TNIL)
				lua_remove(L, -2);  /* remove '__name' */
			break;
		}
		}
	}

	return lua_tolstring(L, -1, len);
}
#include <Main.h>

void lua_initclass(lua_State* L)
{
	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "es"); //entity storage -> this will store all the entities reference

	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "e_mt"); //entity metatable -> this will store all entities functions, metaevents, etc
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

	lua_pushstring(L, "__base");
	if (baseClass == nullptr)
		lua_pushboolean(L, false);
	else
	{
		lua_getclass(L, baseClass);

		L_ASSERT(lua_istable(L, -1), "lua_beginclass: Implementing \"" + alt::String(className) + "\" class. Error: base class \"" + alt::String(baseClass) + "\" not found.");
	}
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

	//lua_stacktrace(L, "lua_beginclass");
}

void lua_endclass(lua_State* L)
{
	//assert(lua_istable(L, -1));
	//assert(lua_isstring(L, -2));

	//lua_pushstring(L, "e_mt");
	//lua_rawget(L, LUA_REGISTRYINDEX); //e_mt, class table, class name

	//lua_pushvalue(L, -3); //class name, e_mt, class table, class name
	//lua_pushvalue(L, -3); //class table, class name, e_mt, class table, class name
	//lua_rawset(L, -3); //e_mt, class table, class name

	//lua_pop(L, 3); //empty

	lua_classmeta(L, "__call", CLuaFunctionDefs::Call);
	lua_classmeta(L, "__index", CLuaFunctionDefs::Index, true);
	lua_classmeta(L, "__newindex", CLuaFunctionDefs::NewIndex, true);

	lua_newtable(L);
	lua_pushvalue(L, -2);
	lua_setmetatable(L, -2);
	L_ASSERT(lua_isstring(L, -3), "lua_endclass: String not found at position -3");
	lua_setglobal(L, luaL_checkstring(L, -3));

	lua_rawset(L, -3);
	lua_pop(L, 1);

	/*lua_newtable(L);
	lua_getfield(L, -2, "__meta");
	lua_setmetatable(L, -2);
	L_ASSERT(lua_isstring(L, -3), "lua_endclass: String not found at position -3");
	lua_setglobal(L, lua_tostring(L, -3));*/

	/*lua_newtable(L); //this will be the metatable
	lua_newtable(L); //table for storing metaevents
	{
		lua_pushstring(L, "__call");
		lua_pushcfunction(L, CLuaFunctionDefs::Call);
		lua_rawset(L, -3);

		lua_pushstring(L, "__newindex");
		lua_pushcfunction(L, CLuaFunctionDefs::NewIndex);
		lua_rawset(L, -3);

		lua_pushstring(L, "__index");
		lua_pushcfunction(L, CLuaFunctionDefs::Index);
		lua_rawset(L, -3);
	}
	lua_setmetatable(L, -2); //set metatable

	L_ASSERT(lua_isstring(L, -3), "lua_endclass: String not found at position -3");
	lua_setglobal(L, lua_tostring(L, -3));*/

	//lua_rawset(L, -3);

	//lua_pop(L, 3);
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

void lua_classmeta(lua_State* L, const char* metaName, lua_CFunction metaFunction, bool isClosure)
{
	//lua_getfield(L, -1, "__meta");

	L_ASSERT(lua_istable(L, -1), "lua_classfunction: \"__meta\" table not found");

	lua_pushstring(L, metaName);
	//lua_stacktrace(L, "lua_classmeta");
	if (isClosure)
	{
		lua_pushvalue(L, -2);
		lua_pushcclosure(L, metaFunction, 1);
	} else
		lua_pushcfunction(L, metaFunction);

	lua_rawset(L, -3);

	//lua_stacktrace(L, "lua_classmeta");

	//lua_pop(L, 1);
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

void lua_pushmvalue(lua_State* L, alt::MValueConst mValue)
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
			Core->LogInfo(levelTab + lua_tostring(L, -1) + " => Table");
			Core->LogInfo(levelTab + "{");

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
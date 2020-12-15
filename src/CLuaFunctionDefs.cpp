#include "Main.h"

int CLuaFunctionDefs::Index(lua_State* L)
{
	lua_pushvalue(L, lua_upvalueindex(1));

	//Search for function or variable in own metatable
	{
		//Search for function
		{
			lua_pushstring(L, "__class");
			lua_rawget(L, -2);

			L_ASSERT(lua_istable(L, -1), "CLuaFunctionDefs::Index: \"__class\" table not found in metatable");
			L_ASSERT(lua_isstring(L, -3), "CLuaFunctionDefs::Index: Property name not found at index -2");

			lua_pushvalue(L, -3);
			lua_rawget(L, -2);
			//lua_getfield(L, -1, luaL_checkstring(L, -3));

			if (lua_isfunction(L, -1))
			{	
				return 1;
			}
		}

		lua_pop(L, 2);

		//Search for get variable
		{
			lua_pushstring(L, "__get");
			lua_rawget(L, -2);

			L_ASSERT(lua_istable(L, -1), "CLuaFunctionDefs::Index: \"__get\" table not found in metatable");
			L_ASSERT(lua_isstring(L, -3), "CLuaFunctionDefs::Index: Property name not found at index -2");

			lua_pushvalue(L, -3);
			lua_rawget(L, -2);

			if (lua_isfunction(L, -1))
			{
				lua_pushvalue(L, 1);

				lua_call(L, 1, 1);

				lua_remove(L, -2);

				return 1;
			}
		}
	}

	lua_pop(L, 2);

	/*
	//Search in base class
	{
		lua_pushstring(L, "__base");
		lua_rawget(L, -2);

		if (lua_istable(L, -1))
		{
			lua_pushstring(L, "__index");
			lua_rawget(L, -2);

			if (lua_isfunction(L, -1))
			{
				lua_pushvalue(L, 1);
				lua_pushvalue(L, 2);

				lua_call(L, 2, 1);

				return 1;
			}
		}

		lua_pop(L, 1);
	}
	*/

	//Search in data container
	{
		lua_pushstring(L, "__data");
		lua_rawget(L, -2);

		if (lua_istable(L, -1))
		{
			lua_pushvalue(L, 1);
			lua_rawget(L, -2);

			if (lua_istable(L, -1))
			{
				lua_pushvalue(L, 2);
				lua_rawget(L, -2);

				return 1;
			}
		}

		lua_pop(L, 1);
	}

#ifndef NDEBUG
	//lua_stacktrace(L, "CLuaFunctionDefs::Index2");
#endif

	lua_pop(L, 2);
	lua_pushnil(L);

	//lua_stacktrace(L, "CLuaFunctionDefs::Index::end");

	return 1;
}

int CLuaFunctionDefs::StaticIndex(lua_State* L)
{
	Core->LogInfo("CLuaFunctionDefs::StaticIndex");

	return 0;
}

int CLuaFunctionDefs::NewIndex(lua_State* L)
{

#ifndef NDEBUG
	Core->LogInfo("CLuaFunctionDefs::NewIndex");
#endif

	lua_pushvalue(L, lua_upvalueindex(1)); //meta table, value, variable, userdata

	//Search for __set variable in meta table
	{
		lua_pushstring(L, "__set"); //meta table, value, variable, userdata
		lua_rawget(L, -2);

		lua_pushvalue(L, 2);
		lua_rawget(L, -2);

		if (lua_isfunction(L, -1))
		{
			lua_pushvalue(L, 1);
			//lua_pushvalue(L, 2); //dont need this
			lua_pushvalue(L, 3);

			lua_call(L, 2, 0);

			lua_pop(L, 1);

			return 0;
		}

		lua_pop(L, 2);
	}

	/*
	//Search for __base functions
	{
		lua_pushstring(L, "__base");
		lua_rawget(L, -2);

		if (lua_istable(L, -1))
		{
			//lua_stacktrace(L, "CLuaFunctionDefs::NewIndex2");

			lua_pushstring(L, "__newindex");
			lua_rawget(L, -2);

			if (lua_isfunction(L, -1))
			{
				//lua_stacktrace(L, "CLuaFunctionDefs::NewIndex3");

				lua_pushvalue(L, 1);
				lua_pushvalue(L, 2);
				lua_pushvalue(L, 3);

				//lua_stacktrace(L, "CLuaFunctionDefs::NewIndex4");

				//Core->LogInfo("Call base shit");
				//lua_stacktrace(L, "CLuaFunctionDefs::NewIndex5");

				lua_call(L, 3, 0);

				lua_pop(L, 2);

				return 0;
			}
		}

		lua_pop(L, 1);
	}*/

	//Set custom data for userdata
	{
		lua_pushstring(L, "__data");
		lua_rawget(L, -2);

		if (lua_istable(L, -1))
		{
			lua_pushvalue(L, 1);
			lua_rawget(L, -2);

			if (!lua_istable(L, -1))
			{
				lua_pop(L, 1);
				lua_pushvalue(L, 1);
				lua_newtable(L);
				lua_rawset(L, -3);

				lua_pushvalue(L, 1);
				lua_rawget(L, -2);
			}

			lua_pushvalue(L, 2);
			lua_pushvalue(L, 3);
			lua_rawset(L, -3);

			lua_pop(L, 1);

			return 0;
		}
	}

	//Core->LogInfo("CLuaFunctionDefs::NewIndex2");
	
	return 0;
}

int CLuaFunctionDefs::Call(lua_State* L)
{
	//Core->LogInfo("CLuaFunctionDefs::Call");

	int tempStack = lua_gettop(L);
	
	lua_getmetatable(L, 1);
	L_ASSERT(lua_istable(L, -1), "CLuaFunctionDefs::Call: Metatable not found");

	lua_pushstring(L, "__class");
	lua_rawget(L, -2);
	//lua_getfield(L, -1, "__class");
	L_ASSERT(lua_istable(L, -1), "CLuaFunctionDefs::Call: \"__class\" not found");

	lua_pushstring(L, "new");
	lua_rawget(L, -2);
	//lua_getfield(L, -1, "new");

	if (lua_isfunction(L, -1))
	{
		lua_replace(L, 1);

		lua_settop(L, tempStack);
		lua_call(L, tempStack - 1, 1);

		//return tempStack;
	}

#ifdef _DEBUG
	//lua_stacktrace(L, "CLuaFunctionDefs::Call");
#endif
	
	//Core->LogInfo("Stack number: " + std::to_string(lua_gettop(L)));

	return 1;
}

/*int CLuaDefs::Index(lua_State *L)
{
	//get the classname
	lua_getmetatable(L, -2);
	lua_getfield(L, -1, "__classname");
	const char* className = luaL_checkstring(L, -1);
	lua_pop(L, 2);

	//lua_getclass(L, className);
	//lua_getfield(L, -1, "__function");
	//lua_getfield(L, -1, luaL_checkstring(L, -3));
	lua_getclassfield(L, className, { "__function", luaL_checkstring(L, -1) });

	//lua_stacktrace(L, "Indexhahaha1");

	if (lua_isfunction(L, -1))
	{
		//lua_pop(L, -1);
		//Core->LogInfo("Got function!");
		return 1;
	}

	lua_pop(L, 1);

	lua_getclassfield(L, className, { "__get", luaL_checkstring(L, -1) });

	if (lua_isfunction(L, -1))
	{
		//lua_pop(L, -1);
		//Core->LogInfo("Got function!");

		lua_pushvalue(L, 1);

		lua_call(L, 1, 1);

		lua_replace(L, 1);
		lua_settop(L, 1);

		//lua_stacktrace(L, "Indexhahaha2");

		return 1;
	}

	//lua_remove(L, -2);
	//lua_pushstring()

	//sampgdk::logprintf("classname: %s", className);
	return 0;
}

int CLuaDefs::NewIndex(lua_State *L)
{
	lua_getmetatable(L, -3);
	lua_getfield(L, -1, "__classname");
	const char* className = luaL_checkstring(L, -1);
	lua_pop(L, 2);

	const char* setFunctionName = luaL_checkstring(L, -2);
	lua_getclassfield(L, className, { "__set", setFunctionName });

	//lua_stacktrace(L, "CLuaDefs::NewIndex1");

	if(lua_iscfunction(L, -1))
	{
		lua_pushvalue(L, 1); //copy Vehicle pointer to top of the stack
		lua_pushvalue(L, 3); //copy new poisitions to top of the stack

		//lua_stacktrace(L, "CLuaDefs::NewIndex3");

		lua_call(L, 2, 1); //call function from stack

		lua_replace(L, 1); //move result to the first place
		lua_settop(L, 1); //set result to be at the top of the stack

		//lua_stacktrace(L, "CLuaDefs::NewIndex2");
		
		return 1;
	}

	Core->LogInfo("Name: " + alt::String(className) + " | " + alt::String(setFunctionName));
	//lua_stacktrace(L, "CLuaDefs::NewIndex2");

	return 1;
}

int CLuaDefs::Call(lua_State *L)
{
	if (!lua_istable(L, 1))
		return 0;

	int stackTop = lua_gettop(L);

	lua_getmetatable(L, 1);
	lua_getfield(L, -1, "__classname");
	const char* className = luaL_checkstring(L, -1);

	lua_pop(L, 1);

	//lua_getclass(L, className);
	//lua_getfield(L, -1, "__function");
	//lua_getfield(L, -1, "new");
	//lua_getclassfield(L, className, { "__function", "new" });
	lua_getclassfield(L, className, { "__function", "new" });

	if (lua_isfunction(L, -1))
	{
		for (int i = 2; i <= stackTop; i++)
		{
			//sampgdk::logprintf("pushvalue");
			lua_pushvalue(L, i);
		}

		//lua_settop(L, -3);

		lua_call(L, stackTop - 1, LUA_MULTRET);

		return lua_gettop(L) - stackTop - 1;
	}

	//if function not found delete the stack
	lua_settop(L, 0);

	//lua_stacktrace(L, "CLuaDefs::Call");

	return 0;
}

int CLuaDefs::GarbageCollect(lua_State* L)
{
	Core->LogInfo("GarbageCollect called");

	lua_stacktrace(L, "CLuaDefs::GarbageCollect");

	return 0;
}*/
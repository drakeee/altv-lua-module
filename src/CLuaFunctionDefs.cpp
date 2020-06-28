#include "Main.h"

int CLuaDefs::Index(lua_State *L)
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
}
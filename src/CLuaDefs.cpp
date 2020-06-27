#include "Main.h"
//#include "CLuaFunctionDefs.h"

/**
 * @brief Print the exact state of stack
 * 
 * @param L - Lua state
 * @param stackName - Name the trace for easily readability
 */
void lua_stacktrace(lua_State* L, const char* stackName)
{
	int stackTop = lua_gettop(L);

	Core->LogInfo(" --------- Stack Begins: " + alt::String(stackName) + "---------");
	for (size_t i = stackTop; i >= 1; i--)
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
			Core->LogInfo("\tAbsolute: " + std::to_string(i) + " ~~ Relative: " + std::to_string((i - stackTop) - 1) + " ~~\t Value type: " + lua_typename(L, valueType) + "");
			break;
		}
	}
	Core->LogInfo(" --------- Stack Ends: " + alt::String(stackName) + " ---------");
}

/**
 * @brief Dump a Lua table's data into the console.
 * 
 * @param L - Lua state
 * @param idx - index of stack which holds table
 * @param level - how deep to look further
 */
void lua_dumptable(lua_State *L, int idx, int level)
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
			Core->LogInfo(levelTab + lua_tostring(L, -1) + " => Table\n" + levelTab + "{");

			//for some reason we need to pass the original table and not the referenced one (recursive call)
			lua_dumptable(L, -3, level + 1);

			//make it beautifuly aligned
			Core->LogInfo(levelTab + "}");
		}
		else
			Core->LogInfo(levelTab + lua_tostring(L, -1) + " => " + lua_tostring(L, -2) + ",");

		lua_pop(L, 2);
	}
}

/**
 * @brief Inserting to table with given key and value at idx of the stack
 * 
 * @param L - Lua state
 * @param idx - index of stack which holds table
 * @param key - self explanatory
 * @param value - self explanatory
 */
void lua_inserttable(lua_State *L, int idx, const char* key, const char* value)
{
	assert(lua_istable(L, idx));

	lua_pushstring(L, key);
	lua_pushstring(L, value);
	lua_settable(L, idx - 2);

	Core->LogInfo("Here lies table");
}

/**
 * @brief Init elements storage unit and elements metatable for storing data.
 * 
 * @param L - Lua state
 */

void lua_initclass(lua_State *L)
{
	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "ge"); //generic elements storage unit in registry

	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, "ge_mt"); //generic elements metatable
}

/**
 * @brief Create a new class in Lua state with given name
 * 
 * @param L - Lua state
 * @param className - Class name
 */
void lua_newclass(lua_State *L, const char* className)
{
	lua_getfield(L, LUA_REGISTRYINDEX, "ge_mt");
	if (!lua_istable(L, -1))
	{
		Core->LogInfo("[C_LUA] ge_mt does not exists!");
		return;
	}

	//create new table for metatable
	lua_pushstring(L, className);
	lua_newtable(L);
	{
		lua_pushstring(L, "__classname");
		//lua_pushboolean(L, 0);
		lua_pushstring(L, className);
		lua_rawset(L, -3);

		//Leave it be normal className
		lua_pushstring(L, "__name");
		//lua_pushboolean(L, 0);
		lua_pushstring(L, className);
		lua_rawset(L, -3);

		lua_pushstring(L, "__call");
		//lua_pushboolean(L, 0);
		lua_pushcfunction(L, CLuaDefs::Call);
		//TODO: create function for __calls
		lua_rawset(L, -3);

		lua_pushstring(L, "__index");
		//lua_pushnil(L);
		lua_pushcfunction(L, CLuaDefs::Index);
		lua_rawset(L, -3);

		lua_pushstring(L, "__newindex");
		//lua_pushnil(L);
		lua_pushcfunction(L, CLuaDefs::NewIndex);
		lua_rawset(L, -3);
	}

	//save the table under className in ge_mt table
	lua_rawset(L, -3);
	lua_pop(L, 1);



	//create the table for functions, variable, etc
	lua_getfield(L, LUA_REGISTRYINDEX, "ge");

	lua_pushstring(L, className);
	lua_newtable(L);
	{
		lua_pushstring(L, "__classname");
		lua_pushstring(L, className);
		lua_rawset(L, -3);

		lua_pushstring(L, "__function");
		//lua_pushboolean(L, 0);
		lua_newtable(L);
		lua_rawset(L, -3);

		lua_pushstring(L, "__set");
		lua_newtable(L);
		//TODO: create function for __calls
		lua_rawset(L, -3);

		lua_pushstring(L, "__get");
		//lua_pushnil(L);
		lua_newtable(L);
		lua_rawset(L, -3);

		lua_pushstring(L, "__object");
		//lua_pushnil(L);
		lua_newtable(L);
		lua_rawset(L, -3);
	}

	lua_rawset(L, -3);
	lua_pop(L, 1);

	lua_pushstring(L, className);
}

/**
 * @brief Register a meta function in class metatable
 * 
 * @param L - Lua state
 * @param metaName - Meta name i.e: __gc, __add, __mul, etc
 * @param func - C function to handle data
 */
void lua_classmetatable(lua_State *L, const char* metaName, lua_CFunction func)
{
	const char* className = luaL_checkstring(L, -1);
	lua_getclassmt(L, className);

	if(func)
	{
		lua_pushcfunction(L, func);
		lua_setfield(L, -2, metaName);

		lua_pop(L, 1);
	}
}

/**
 * @brief Push userdata at top of the stack. If the userdata doesn't exist in global registry we add it as reference.
 * 
 * @param L - Lua state
 * @param className - Which class to apply on the userdata
 * @param userdata - Pointer to userdata
 */
void lua_userdata(lua_State *L, const char* className, void* userdata)
{
	void **tempUserdata = reinterpret_cast<void **>(lua_newuserdata(L, sizeof(void*)));
	*tempUserdata = userdata;

	//Apply class metatable to userdata
	lua_getclassmt(L, className);
	lua_setmetatable(L, -2);

	//Check if it is referenced already in global registry
	lua_getclassfield(L, className, {"__object"});
	lua_pushvalue(L, -2);
	lua_rawget(L, -2);

	//If not then add it
	if(lua_isnil(L, -1))
	{
		lua_pop(L, 1); //pop nil result

		lua_pushvalue(L, -2); //push userdata at top of the stack
		lua_pushboolean(L, 1); //give some value to it doesn't matter what
		lua_rawset(L, -3); //add userdata to the table as reference

		lua_pop(L, 1); //pop the table from the stack
	}

	return;
}

/**
 * @brief Register set up class in registry. 
 * 
 * @param L - Lua state
 */
void lua_registerclass(lua_State *L)
{
	const char* className = luaL_checkstring(L, -1);

	lua_pop(L, 1);

	lua_newtable(L);
	lua_getclassmt(L, className);
	lua_setmetatable(L, -2);
	lua_setglobal(L, className);
}

/**
 * @brief Register C function with given function name in Lua state
 * 
 * @param L - Lua state
 * @param functionName - Function name to register C function to.
 * @param func - Actual C function
 */
void lua_registerfunction(lua_State *L, const char* functionName, lua_CFunction func, bool isGlobal)
{
	const char* className = luaL_checkstring(L, -1);
	
	lua_getclassfield(L, className, {"__function"});
	lua_getfield(L, -1, functionName);

	//check if function does not exists
	if (lua_isnil(L, -1))
	{
		//pop the nil value from the top
		lua_pop(L, 1);

		//push function to the stack, then set the table (ge.class["__function"][functionName] = func)
		lua_pushstring(L, functionName);
		lua_pushcfunction(L, func);
		lua_rawset(L, -3);

		if(isGlobal)
		{
			lua_getfield(L, -1, functionName);
			lua_setglobal(L, functionName);
		}

		//stack: ge.class table, ge.class["__function"] table
		lua_pop(L, 1); //after pop: ge.class table

		//Core->LogInfo("-lua_registerfunction: %s", functionName);
	}
}

/**
 * @brief Register OOP functionality to already existing function name.
 * 
 * @param L - Lua state
 * @param oopName - OOP name
 * @param functionName - Already existing Lua function name.
 */
void lua_registeroop(lua_State *L, const char* oopName, const char* functionName)
{
	const char* className = luaL_checkstring(L, -1);
	lua_getclassfield(L, className, { "__function", functionName });

	if (lua_isfunction(L, -1))
	{
		lua_getclassfield(L, className, { "__function" });
		lua_pushstring(L, oopName);
		lua_pushvalue(L, -3);

		lua_rawset(L, -3);

		lua_pop(L, 2);
	}
	else
	{
		Core->LogInfo("Unable to register function: " + alt::String(oopName) + ", Error: " + alt::String(functionName) + " function not found!");
		lua_pop(L, 1);
	}
}

/**
 * @brief Give variable functionality with setter and getter functions.
 * 
 * @param L - Lua state
 * @param variableName - Variable name
 * @param setFunction - Already existing set function
 * @param getFunction - Already existing get function
 */
void lua_registervariable(lua_State *L, const char* variableName, const char* setFunction, const char* getFunction)
{
	const char* className = luaL_checkstring(L, -1);

	//Register function for set variable
	lua_getclassfield(L, className, { "__set" });
	lua_getclassfield(L, className, { "__function", setFunction });

	if(lua_isfunction(L, -1))
	{
		lua_pushstring(L, variableName);
		lua_insert(L, -2);
		lua_rawset(L, -3);

		lua_pop(L, 1);
	}

	//Register function for get variable
	lua_getclassfield(L, className, { "__get" });
	lua_getclassfield(L, className, { "__function", getFunction });

	if (lua_isfunction(L, -1))
	{
		lua_pushstring(L, variableName);
		lua_insert(L, -2);
		lua_rawset(L, -3);

		lua_pop(L, 1);
	}
}

/**
 * @brief Get elements or elements metatable from registry and push to top of the stack
 * 
 * @param L - Lua state
 * @param mt - Is it the metatable (true) or regular elements storage unit (false)
 * @param className - Which class should retrieve
 */
void lua_getclass_helper(lua_State *L, bool mt, const char* className)
{
	//get metatables or storage unit (depending on "mt" variable) from lua registry
	lua_getfield(L, LUA_REGISTRYINDEX, (mt ? ("ge_mt") : ("ge"))); //stack: ge_mt (table?)

	//check if we have indeed a table for it
	if (!lua_istable(L, -1))
	{
		Core->LogInfo("Unable to retrieve generic elements metatable!");
		return;
	}

	//push which index we want to access then get it from the table
	lua_pushstring(L, className); //stack: ge_mt, className
	lua_rawget(L, -2); //ge_mt table, class (table?)

	//if there is no class metatable then inform about it
	if (!lua_istable(L, -1))
	{
		Core->LogInfo("Unable to retrieve \"" + alt::String(className) + "\" class metatable!");
		return;
	}

	//remove "ge_mt" metatable from the stack leaving only the requested class metatable
	lua_remove(L, -2); //class table
}

/**
 * @brief Check if userdata exists in Lua registry. The userdata must be top of the stack.
 * 
 * @param L - Lua state
 * @return true - Returns true if userdata exists in Lua registry
 * @return false - Returns false if userdata doesn't exist in Lua registry
 */
/*
bool lua_isudataexists(lua_State *L)
{
	lua_getmetatable(L, -1);
	lua_getfield(L, -1, "__classname");

	const char* className = luaL_checkstring(L, -1);
	lua_pop(L, 2); //pop the metatable and __classname;

	//lua_getfield(L, LUA_REGISTRYINDEX, "ge");
	lua_getclassfield(L, className, {"__object"});
	lua_pushvalue(L, -2);
	lua_rawget(L, -2);

	if(lua_isnil(L, -1))
	{
		lua_pop(L, 2);

		lua_stacktrace(L, "udataexists2");

		return false;
	}

	lua_pop(L, 2);
	lua_stacktrace(L, "udataexists1");

	return true;
}
*/

/*
void lua_addudatareference(lua_State *L)
{
	lua_getmetatable(L, -1);
	lua_getfield(L, -1, "__classname");

	const char* className = luaL_checkstring(L, -1);
	lua_pop(L, 2); //pop the metatable and __classname;

	lua_getclassfield(L, className, {"__object"});
	lua_pushvalue(L, -2);
	lua_pushboolean(L, 1);
	lua_rawset(L, -3);
	lua_pop(L, 1);
}
*/

/*void lua_getclass(lua_State *L, const char* className)
{
	lua_getfield(L, LUA_REGISTRYINDEX, "ge");
	if (!lua_istable(L, -1))
	{
		//lua_pop(L, 1);
		Core->LogInfo("Unable to retrieve generic elements storage unit!");
		return;
	}

	lua_pushstring(L, className);
	lua_rawget(L, -2);

	if (!lua_istable(L, -1))
	{
		lua_remove(L, -2);
		Core->LogInfo("Unable to retrieve \"%s\" class storage unit!", className);
		return;
	}

	lua_remove(L, -2);
}

void lua_getclassmt(lua_State *L, const char* className)
{
	//get metatables from lua registry
	lua_getfield(L, LUA_REGISTRYINDEX, "ge_mt"); //stack: ge_mt (table?)

	//check if we have indeed a table for it
	if (!lua_istable(L, -1))
	{
		Core->LogInfo("Unable to retrieve generic elements metatable!");
		return;
	}

	//push which index we want to access then get it from the table
	lua_pushstring(L, className); //stack: ge_mt, className
	lua_rawget(L, -2); //ge_mt table, class (table?)

	//if there is no class metatable then inform about it
	if (!lua_istable(L, -1))
	{
		Core->LogInfo("Unable to retrieve \"%s\" class metatable!", className);
		return;
	}

	//remove "ge_mt" metatable from the stack leaving only the requested class metatable
	lua_remove(L, -2); //class table
}*/

/**
 * @brief 
 * 
 * @param L - Lua state 
 * @param mt - Check if we want to get the metatable of the class or the storage unit
 * @param className - Self explanatory
 * @param values - Array of string values which index we want to get i.e: {"__function", "createVehicle"} => this will return createVehicle C function reference
 */
void lua_getclassfield_helper(lua_State *L, bool mt, const char* className, std::initializer_list<std::string> values)
{
	//check the stack size because we want to keep them
	int startStack = lua_gettop(L);

	//check if we need metatable or the storage unit
	if (!mt)
		lua_getclass(L, className);
	else
		lua_getclassmt(L, className);

	if (!lua_istable(L, -1))
	{
		//if we dont have matching table then push a nil on top
		lua_pushnil(L);
		return;
	}

	//count how many string we have been processed
	int numString = 0;

	//run through all the strings
	for(auto &value : values)
	{
		//count how many string we have been processed
		numString++;

		//convert string to const char
		const char* a = value.c_str();
		
		//get given key
		lua_getfield(L, -1, a);

		//check if the result is nil or not
		if (lua_isnil(L, -1))
			break;

		//if not and we have a table on top of the stack and we have more string then continue
		if (lua_istable(L, -1) && numString != values.size())
			continue;
	}

	//keep the started stack only + the result on top
	int stackNum = lua_gettop(L) - startStack - 1; //-1 means how many values we want to save
	for (int i = 1; i <= stackNum; i++)
		lua_remove(L, startStack + 1);
}

void lua_getdebuginfo(lua_State *L, lua_Debug &debugInfo)
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
#include "Main.h"

void CLuaVector3Defs::init(lua_State *L)
{
	CLuaVector3Defs::initVariables(L);
	CLuaVector3Defs::initClass(L);
}

void CLuaVector3Defs::initClass(lua_State *L)
{
	lua_newclass(L, "Vector3");

	lua_classmetatable(L, "__gc", CLuaVector3Defs::destroy);
	lua_classmetatable(L, "__tostring", CLuaVector3Defs::tostring);

	lua_registerfunction(L, "new", CLuaVector3Defs::create, false);

	lua_registerclass(L);
}

void CLuaVector3Defs::initVariables(lua_State *L)
{

}

int CLuaVector3Defs::create(lua_State *L)
{
	Vector3fp vector(0.0, 0.0, 0.0);

	CArgReader argReader(L);
	if(argReader.IsCurrentType(LUA_TTABLE))
	{
		//Syntax: Vector3({x = x, y = y, z = z})
		lua_pushstring(L, "x");
		lua_rawget(L, -2);

		if(lua_isnumber(L, -1))
		{
			vector.x = static_cast<float>(lua_tonumber(L, -1));
			lua_pop(L, 1);
		} else {
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 1);

			if(lua_isnumber(L, -1))
				vector.x = static_cast<float>(lua_tonumber(L, -1));
			
			lua_pop(L, 1);
		}


		lua_pushstring(L, "y");
		lua_rawget(L, -2);

		if(lua_isnumber(L, -1))
		{
			vector.y = static_cast<float>(lua_tonumber(L, -1));
			lua_pop(L, 1);
		} else {
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);

			if(lua_isnumber(L, -1))
				vector.y = static_cast<float>(lua_tonumber(L, -1));

			lua_pop(L, 1);
		}


		lua_pushstring(L, "z");
		lua_rawget(L, -2);

		if(lua_isnumber(L, -1))
		{
			vector.z = static_cast<float>(lua_tonumber(L, -1));
			lua_pop(L, 1);
		} else {
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 3);

			if(lua_isnumber(L, -1))
				vector.z = static_cast<float>(lua_tonumber(L, -1));  

			lua_pop(L, 1);
		}

		lua_pop(L, 1);
	}else if(argReader.IsCurrentType(LUA_TNUMBER))
	{
		argReader.ReadVector<float, 3, alt::PointLayout>(vector);
	}

#ifdef _DEBUG
	Core->LogInfo("Vector3: x = "+ std::to_string(vector.x) +", y = "+ std::to_string(vector.y) +", z = "+ std::to_string(vector.z) +"");
#endif

	Vector3fp*tempVector = new Vector3fp(vector);

	//sampgdk::logprintf("Vector3(2): x = %f, y = %f, z = %f", tempVector->x, tempVector->y, tempVector->z);
	lua_userdata(L, "Vector3", tempVector);

	//lua_stacktrace(L, "Vector32");

	return 1;
}

int CLuaVector3Defs::destroy(lua_State *L)
{
	Vector3fp *vector = nullptr;

	lua_stacktrace(L, "destroy");

	CArgReader argReader(L);
	argReader.ReadUserData(vector);

	if(!argReader.HasAnyError())
	{
		delete vector;

#ifdef _DEBUG
		Core->LogInfo("Vector garbage collected!");
#endif

		lua_pushboolean(L, true);
		return 1;
	}

	argReader.GetErrorMessages();

#ifdef _DEBUG
	Core->LogInfo("Vector failed to destroyed");
#endif

	lua_pushboolean(L, false);
	return 1;
}

int CLuaVector3Defs::tostring(lua_State *L)
{
	Vector3fp *vector = nullptr;
	//Vector3 vector;

	CArgReader argReader(L);
	argReader.ReadUserData(vector);
	//argReader.ReadVector3D(vector);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	char buffer[128];
	sprintf(buffer, "Vector3(%.3f, %.3f, %.3f)", vector->x, vector->y, vector->z);

	lua_pushstring(L, buffer);

	return 1;
}
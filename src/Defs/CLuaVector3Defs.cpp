#include "Main.h"

const char* CLuaVector3Defs::ClassName = "Vector3";
void CLuaVector3Defs::Init(lua_State *L)
{
	lua_beginclass(L, ClassName);
	{
		lua_classmeta(L, "__gc", CLuaVector3Defs::destroy);
		lua_classmeta(L, "__tostring", CLuaVector3Defs::tostring);
		lua_classmeta(L, "__add", CLuaVector3Defs::add);

		lua_classfunction(L, "new", CLuaVector3Defs::create);
	}
	lua_endclass(L);
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
		argReader.ReadVector(vector);
	}

#ifdef _DEBUG
	//Core->LogInfo("Vector3: x = "+ std::to_string(vector.x) +", y = "+ std::to_string(vector.y) +", z = "+ std::to_string(vector.z) +"");
#endif

	Vector3fp* tempVector = new Vector3fp(vector);

#ifdef _DEBUG
	/*printf("Create vector: %d\n", tempVector);*/
#endif

	// in this case we don't want to store any reference in the Lua registry
	// TODO (?): maybe store reference because we might need it (?) 

	lua_pushuserdata(L, "Vector3", tempVector, false);

	return 1;
}

int CLuaVector3Defs::destroy(lua_State *L)
{
	Vector3fp *vector = nullptr;

	//lua_stacktrace(L, "destroy");

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
	sprintf_s(buffer, "Vector3(%.3f, %.3f, %.3f)", vector->x, vector->y, vector->z);

	lua_pushstring(L, buffer);

	//lua_stacktrace(L, "tostring");

	return 1;
}

int CLuaVector3Defs::add(lua_State* L)
{
	//lua_stacktrace(L, "CLuaVector3Defs::add");

	Vector3fp *leftVector;
	Vector3fp *rightVector;

	CArgReader argReader(L);
	argReader.ReadUserData(leftVector);
	argReader.ReadUserData(rightVector);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();

		lua_pushnil(L);

		return 1;
	}

	Vector3fp *temp = new Vector3fp(*leftVector + *rightVector);

	//lua_userdata(L, "Vector3", temp, false);

	/*Core->LogInfo("LeftVector: " + std::to_string(leftVector->x));
	Core->LogInfo("RightVector: " + std::to_string(rightVector->x));*/

	return 1;
}
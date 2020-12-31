#include "Main.h"

const char* CLuaVector2Defs::ClassName = "Vector2";
void CLuaVector2Defs::Init(lua_State *L)
{
	lua_beginclass(L, ClassName);
	{
		lua_classmeta(L, "__gc", destroy);
		lua_classmeta(L, "__tostring", tostring);
		lua_classmeta(L, "__add", add);

		lua_classfunction(L, "new", create);
		lua_classfunction(L, "setX", SetX);
		lua_classfunction(L, "setY", SetY);
		lua_classfunction(L, "getX", GetX);
		lua_classfunction(L, "getY", GetY);

		lua_classvariable(L, "x", "setX", "getX");
		lua_classvariable(L, "y", "setY", "getY");
	}
	lua_endclass(L);
}

int CLuaVector2Defs::create(lua_State *L)
{
	Vector2fp vector(0.0, 0.0);

	CArgReader argReader(L);
	if(argReader.IsCurrentType(LUA_TTABLE))
	{
		//Syntax: Vector3({x = x, y = y, z = z})
		lua_pushstring(L, "x");
		lua_rawget(L, -2);

		if(lua_isnumber(L, -1))
		{
			vector[0] = static_cast<float>(lua_tonumber(L, -1));
			lua_pop(L, 1);
		} else {
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 1);

			if(lua_isnumber(L, -1))
				vector[0] = static_cast<float>(lua_tonumber(L, -1));
			
			lua_pop(L, 1);
		}


		lua_pushstring(L, "y");
		lua_rawget(L, -2);

		if(lua_isnumber(L, -1))
		{
			vector[1] = static_cast<float>(lua_tonumber(L, -1));
			lua_pop(L, 1);
		} else {
			lua_pop(L, 1);
			lua_rawgeti(L, -1, 2);

			if(lua_isnumber(L, -1))
				vector[1] = static_cast<float>(lua_tonumber(L, -1));

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

	Vector2fp* tempVector = new Vector2fp(vector);

#ifdef _DEBUG
	/*printf("Create vector: %d\n", tempVector);*/
#endif

	// in this case we don't want to store any reference in the Lua registry
	// TODO (?): maybe store reference because we might need it (?) 

	lua_pushvector2(L, tempVector);

	return 1;
}

int CLuaVector2Defs::destroy(lua_State *L)
{
	Vector2fp *vector = nullptr;

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

int CLuaVector2Defs::tostring(lua_State *L)
{
	Vector2fp *vector = nullptr;
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
	sprintf_s(buffer, "Vector2(%.3f, %.3f)", (*vector)[0], (*vector)[1]);

	lua_pushstring(L, buffer);

	//lua_stacktrace(L, "tostring");

	return 1;
}

int CLuaVector2Defs::add(lua_State* L)
{
	//lua_stacktrace(L, "CLuaVector2Defs::add");

	Vector2fp *leftVector;
	Vector2fp *rightVector;

	CArgReader argReader(L);
	argReader.ReadUserData(leftVector);
	argReader.ReadUserData(rightVector);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();

		lua_pushnil(L);

		return 1;
	}

	Vector2fp *temp = new Vector2fp(
		(*leftVector)[0] + (*rightVector)[0],
		(*leftVector)[1] + (*rightVector)[1]
	);

	//lua_userdata(L, "Vector3", temp, false);

	/*Core->LogInfo("LeftVector: " + std::to_string(leftVector->x));
	Core->LogInfo("RightVector: " + std::to_string(rightVector->x));*/

	return 1;
}

int CLuaVector2Defs::SetX(lua_State* L)
{
	Vector2fp* vector;
	float x;

	CArgReader argReader(L);
	argReader.ReadUserData(vector);
	argReader.ReadNumber(x);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	(*vector)[0] = x;

	return 0;
}

int CLuaVector2Defs::SetY(lua_State* L)
{
	Vector2fp* vector;
	float y;

	CArgReader argReader(L);
	argReader.ReadUserData(vector);
	argReader.ReadNumber(y);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	(*vector)[1] = y;

	return 0;
}

int CLuaVector2Defs::GetX(lua_State* L)
{
	Vector2fp* vector;

	CArgReader argReader(L);
	argReader.ReadUserData(vector);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, (*vector)[0]);

	return 1;
}

int CLuaVector2Defs::GetY(lua_State* L)
{
	Vector2fp* vector;

	CArgReader argReader(L);
	argReader.ReadUserData(vector);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, (*vector)[1]);

	return 1;
}
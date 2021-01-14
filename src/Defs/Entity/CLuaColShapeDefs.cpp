#include <Main.h>

#ifdef ALT_SERVER_API
const char* CLuaColShapeDefs::ClassName = "ColShape";
void CLuaColShapeDefs::Init(lua_State* L)
{
	DEBUG_INFO("CLuaColShapeDefs::Init");

	lua_globalfunction(L, "createColShapeCircle", CreateCircle);
	lua_globalfunction(L, "createColShapeCube", CreateCube);
	lua_globalfunction(L, "createColShapeCylinder", CreateCylinder);
	lua_globalfunction(L, "createColShapeRectangle", CreateRectangle);
	lua_globalfunction(L, "createColShapeSphere", CreateSphere);

	lua_globalfunction(L, "GetColShapeType", GetColshapeType);

	lua_globalfunction(L, "isEntityInColshape", IsEntityIn);
	lua_globalfunction(L, "isPointInColshape", IsPointIn);

	lua_beginclass(L, ClassName, CLuaWorldObjectDefs::ClassName);
	{
		lua_classfunction(L, "Circle", CreateCircle);
		lua_classfunction(L, "Cube", CreateCube);
		lua_classfunction(L, "Cylinder", CreateCylinder);
		lua_classfunction(L, "Rectangle", CreateRectangle);
		lua_classfunction(L, "Sphere", CreateSphere);

		lua_classfunction(L, "getColShapeType", GetColshapeType);
		lua_classfunction(L, "isEntityIn", IsEntityIn);
		lua_classfunction(L, "isPointIn", IsPointIn);

		lua_classvariable(L, "colshapeType", nullptr, "getColShapeType");
	}
	lua_endclass(L);

	DEBUG_INFO("CLuaColShapeDefs::Init ...done");
}

int CLuaColShapeDefs::CreateCircle(lua_State* L)
{
	alt::Position position;
	float radius;

	CArgReader argReader(L);
	argReader.ReadVector(position);
	argReader.ReadNumber(radius);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto colshape = Core->CreateColShapeCircle(position, radius);
	if (colshape)
		lua_pushbaseobject(L, colshape.Get());
	else
		lua_pushnil(L);

	return 1;
}

int CLuaColShapeDefs::CreateCube(lua_State* L)
{
	alt::Position position;
	alt::Position position2;

	CArgReader argReader(L);
	argReader.ReadVector(position);
	argReader.ReadVector(position2);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto colshape = Core->CreateColShapeCube(position, position2);
	if (colshape)
	{
		lua_pushbaseobject(L, colshape.Get());

		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(colshape.Get());
	}
	else
		lua_pushnil(L);

	return 1;
}

int CLuaColShapeDefs::CreateCylinder(lua_State* L)
{
	alt::Position position;
	float radius;
	float height;

	CArgReader argReader(L);
	argReader.ReadVector(position);
	argReader.ReadNumber(radius);
	argReader.ReadNumber(height);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto colshape = Core->CreateColShapeCylinder(position, radius, height);
	if (colshape)
	{
		lua_pushbaseobject(L, colshape.Get());

		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(colshape.Get());
	}
	else
		lua_pushnil(L);

	return 1;
}

int CLuaColShapeDefs::CreateRectangle(lua_State* L)
{
	float x1, y1;
	float x2, y2;
	float z;

	CArgReader argReader(L);
	argReader.ReadNumber(x1);
	argReader.ReadNumber(y1);
	argReader.ReadNumber(x2);
	argReader.ReadNumber(y2);
	argReader.ReadNumber(z);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto colshape = Core->CreateColShapeRectangle(x1, y1, x2, y2, z);
	if (colshape)
	{
		lua_pushbaseobject(L, colshape.Get());

		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(colshape.Get());
	}
	else
		lua_pushnil(L);

	return 1;
}

int CLuaColShapeDefs::CreateSphere(lua_State* L)
{
	alt::Position position;
	float radius;

	CArgReader argReader(L);
	argReader.ReadVector(position);
	argReader.ReadNumber(radius);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	auto colshape = Core->CreateColShapeSphere(position, radius);
	if (colshape)
	{
		lua_pushbaseobject(L, colshape.Get());

		auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->AddEntity(colshape.Get());
	}
	else
		lua_pushnil(L);

	return 1;
}

int CLuaColShapeDefs::GetColshapeType(lua_State* L)
{
	alt::IColShape* colshape;

	CArgReader argReader(L);
	argReader.ReadBaseObject(colshape);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushnumber(L, static_cast<int>(colshape->GetColshapeType()));

	return 1;
}

int CLuaColShapeDefs::IsEntityIn(lua_State* L)
{
	alt::IColShape* colshape;
	alt::IEntity* entity;

	CArgReader argReader(L);
	argReader.ReadBaseObject(colshape);
	argReader.ReadBaseObject(entity);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, colshape->IsEntityIn(entity));

	return 1;
}

int CLuaColShapeDefs::IsPointIn(lua_State* L)
{
	alt::IColShape* colshape;
	alt::Position position;

	CArgReader argReader(L);
	argReader.ReadBaseObject(colshape);
	argReader.ReadVector(position);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, colshape->IsPointIn(position));

	return 1;
}
#endif
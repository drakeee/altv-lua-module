#include <Main.h>

namespace lua::Class
{
	const char* WorldObject::ClassName = "WorldObject";
	void WorldObject::Init(lua_State* L)
	{
		DEBUG_INFO("WorldObject::Init");

		lua_beginclass(L, ClassName, BaseObject::ClassName);
		{
			lua_classfunction(L, "setPosition", SetPosition);
			lua_classfunction(L, "getPosition", GetPosition);
			lua_classfunction(L, "setDimension", SetDimension);
			lua_classfunction(L, "getDimension", GetDimension);

			lua_classvariable(L, "pos", SetPosition, GetPosition);
			lua_classvariable(L, "position", SetPosition, GetPosition);
			lua_classvariable(L, "dimension", SetDimension, GetDimension);
		}
		lua_endclass(L);

		DEBUG_INFO("WorldObject::Init ...done");
	}

	int WorldObject::SetPosition(lua_State* L)
	{
		alt::IWorldObject* worldObject;
		alt::Position position;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(worldObject);
		argReader.ReadVector(position);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		//Core->LogInfo("WorldObject::SetPosition: x = " + std::to_string(position.x));
		//Core->LogInfo("WorldObject::SetPosition: y = " + std::to_string(position.y));
		//Core->LogInfo("WorldObject::SetPosition: z = " + std::to_string(position.z));

		worldObject->SetPosition(position);

		return 0;
	}

	int WorldObject::GetPosition(lua_State* L)
	{
		alt::IWorldObject* worldObject;

		//Core->LogInfo("WorldObject::GetPosition");

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(worldObject);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		//Core->LogInfo("WorldObject::GetPosition: " + std::to_string(worldObject->GetPosition().x));

		lua_pushvector3(L, worldObject->GetPosition());

		return 1;
	}

	int WorldObject::SetDimension(lua_State* L)
	{
		alt::IWorldObject* worldObject;
		int dimension;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(worldObject);
		argReader.ReadNumber(dimension);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		worldObject->SetDimension(dimension);

		return 0;
	}

	int WorldObject::GetDimension(lua_State* L)
	{
		alt::IWorldObject* worldObject;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(worldObject);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, worldObject->GetDimension());

		return 1;
	}
}
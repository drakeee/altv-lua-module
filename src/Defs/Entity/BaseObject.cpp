#include <Main.h>

namespace lua::Class
{
	const char* BaseObject::ClassName = "BaseObject";
	void BaseObject::Init(lua_State* L)
	{
		DEBUG_INFO("BaseObject::Init");

		lua_beginclass(L, ClassName);
		{
			lua_classfunction(L, "getType", GetType);
			lua_classfunction(L, "hasMetaData", HasMetaData);
			lua_classfunction(L, "getMetaData", GetMetaData);
			lua_classfunction(L, "setMetaData", SetMetaData);
			lua_classfunction(L, "deleteMetaData", DeleteMetaData);
			lua_classfunction(L, "destroy", Destroy);

			lua_classvariable(L, "type", nullptr, GetType);
		}
		lua_endclass(L);

		DEBUG_INFO("BaseObject::Init ...done");
	}

	int BaseObject::Destroy(lua_State* L)
	{
		alt::IBaseObject* baseObject;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(baseObject);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_removedata(L, baseObject);

		auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		resourceImpl->RemoveEntity(baseObject);
		Core->DestroyBaseObject(baseObject);

		lua_pushboolean(L, true);

		return 1;
	}

	/**
	 * @luafunc BaseObject::getType()
	 *
	 * @brief Gets a BaseObject's type.
	 */
	int BaseObject::GetType(lua_State* L)
	{
		alt::IBaseObject* baseObject;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(baseObject);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto type = LuaScriptRuntime::Instance().GetBaseObjectType(baseObject->GetType());
		lua_pushstring(L, type.c_str());

		return 1;
	}

	int BaseObject::HasMetaData(lua_State* L)
	{
		alt::IBaseObject* baseObject;
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(baseObject);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, baseObject->HasMetaData(key));

		return 1;
	}

	int BaseObject::GetMetaData(lua_State* L)
	{
		alt::IBaseObject* baseObject;
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(baseObject);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushmvalue(L, baseObject->GetMetaData(key));

		return 1;
	}

	int BaseObject::SetMetaData(lua_State* L)
	{
		alt::IBaseObject* baseObject;
		std::string key;
		alt::MValue value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(baseObject);
		argReader.ReadString(key);
		argReader.ReadMValue(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		baseObject->SetMetaData(key, value);

		return 0;
	}

	int BaseObject::DeleteMetaData(lua_State* L)
	{
		alt::IBaseObject* baseObject;
		std::string key;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(baseObject);
		argReader.ReadString(key);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		baseObject->DeleteMetaData(key);

		return 0;
	}
}
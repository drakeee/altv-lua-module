#include <Main.h>

#ifdef ALT_CLIENT_API
#include <list>

const char* CLuaNativeDefs::ClassName = "native";
void CLuaNativeDefs::Init(lua_State* L)
{
	lua_beginclass(L, CLuaNativeDefs::ClassName);
	{
		for (auto native : Core->GetAllNatives())
		{
			lua_classnative(L, native->GetName().CStr(), InvokeNative, native);
		}
	}
	lua_endclass(L);

	lua_beginclass(L, "game", CLuaNativeDefs::ClassName);
	lua_endclass(L);
}

struct Ptr {
	void* ptr;
	alt::INative::Type ptrType;
};

std::list<Ptr> pointers;

template<typename T>
T* CreatePtr(T value, alt::INative::Type argType, size_t additionalSize = 1)
{
	T* ptr = static_cast<T*>(malloc(additionalSize * sizeof(T)));
	*ptr = value;

	pointers.push_back({ ptr, argType });

	return ptr;
}

static char* SaveString(const char* str)
{
	static char* stringValues[256] = { 0 };
	static int nextString = 0;

	if (stringValues[nextString])
		free(stringValues[nextString]);

	char* _str = _strdup(str);
	stringValues[nextString] = _str;
	nextString = (nextString + 1) % 256;

	return _str;
}

void PushArg(alt::Ref<alt::INative::Context> ctx, alt::INative::Type argType, alt::MValueConst &value)
{
	switch (argType)
	{
	case alt::INative::Type::ARG_BOOL:
	{
		ctx->Push((int32_t)value.As<alt::IMValueBool>()->Value());
		break;
	}
	case alt::INative::Type::ARG_BOOL_PTR:
		ctx->Push(CreatePtr((int32_t)value.As<alt::IMValueBool>()->Value(), argType));
		break;
	case alt::INative::Type::ARG_INT32:
	{
		if (value->GetType() == alt::IMValue::Type::BASE_OBJECT)
		{
			auto baseObject = value.As<alt::IMValueBaseObject>()->Value().Get();
			if (
				baseObject->GetType() == alt::IBaseObject::Type::PLAYER ||
				baseObject->GetType() == alt::IBaseObject::Type::VEHICLE
				) {
				ctx->Push((dynamic_cast<alt::IEntity*>(baseObject)->GetScriptGuid()));
			}
		}
		else {
			ctx->Push((int32_t)value.As<alt::IMValueInt>()->Value());
		}

		break;
	}
	case alt::INative::Type::ARG_INT32_PTR:
		ctx->Push(CreatePtr((int32_t)value.As<alt::IMValueInt>()->Value(), argType));
		break;
	case alt::INative::Type::ARG_UINT32:
	{
		ctx->Push((uint32_t)value.As<alt::IMValueInt>()->Value()); //numbers are either converted to IMValueInt or IMValueDouble
		break;
	}
	case alt::INative::Type::ARG_UINT32_PTR:
		ctx->Push(CreatePtr((uint32_t)value.As<alt::IMValueInt>()->Value(), argType)); //numbers are either converted to IMValueInt or IMValueDouble
		break;
	case alt::INative::Type::ARG_FLOAT:
	{
		if(value->GetType() == alt::IMValue::Type::INT)
			ctx->Push((float)value.As<alt::IMValueInt>()->Value());
		else if(value->GetType() == alt::IMValue::Type::DOUBLE)
			ctx->Push((float)value.As<alt::IMValueDouble>()->Value());
		//ctx->Push((float)value.As<alt::IMValueDouble>()->Value());
		break;
	}
	case alt::INative::Type::ARG_FLOAT_PTR:
		ctx->Push(CreatePtr((float)value.As<alt::IMValueDouble>()->Value(), argType));
		break;
	case alt::INative::Type::ARG_VECTOR3_PTR:
		ctx->Push(CreatePtr(alt::INative::Vector3{}, argType));
		break;
	case alt::INative::Type::ARG_STRING:
	{
		//ctx->Push(SaveString(value.As<alt::IMValueString>()->Value().ToString().data()));
		//auto stringPtr = *CreatePtr(_strdup(value.As<alt::IMValueString>()->Value().ToString().data()), argType);
		auto stringPtr = SaveString(value.As<alt::IMValueString>()->Value().CStr());
		ctx->Push(stringPtr);

		break;
	}
	case alt::INative::Type::ARG_STRUCT:
		Core->LogInfo("TODO: Native->PushArg(Struct)");
		break;
	default:
		Core->LogError("Unknown native arg type" + std::to_string((int)argType));
		break;
	}
}

void GetReturn(lua_State* L, alt::INative::Context* ctx, alt::INative::Type returnType)
{
	switch (returnType)
	{
	case alt::INative::Type::ARG_BOOL:
		lua_pushboolean(L, ctx->ResultBool());
		break;
	case alt::INative::Type::ARG_INT32:
		lua_pushnumber(L, ctx->ResultInt());
		break;
	case alt::INative::Type::ARG_UINT32:
	{
		lua_pushnumber(L, (lua_Number)ctx->ResultUint());
		break;
	}
	case alt::INative::Type::ARG_FLOAT:
		lua_pushnumber(L, ctx->ResultFloat());
		break;
	case alt::INative::Type::ARG_VECTOR3:
	{
		auto vector = ctx->ResultVector3();
		lua_pushvector3(L, alt::Vector3f(vector.x, vector.y, vector.z));
		break;
	}
	case alt::INative::Type::ARG_STRING:
		if (!ctx->ResultString())
			lua_pushnil(L);
		else
			lua_pushstring(L, ctx->ResultString());
		break;
	case alt::INative::Type::ARG_VOID:
		//lua_pushnil(L);
		break;
	default:
		Core->LogError("Unknown native return type" + std::to_string((int)returnType));
		lua_pushnil(L);
		break;
	}
}

bool GetPtrReturn(lua_State* L, alt::INative::Type returnType, void* ptr)
{
	bool ret = true;

	switch (returnType)
	{
	case alt::INative::Type::ARG_BOOL_PTR:
		lua_pushboolean(L, *static_cast<int32_t*>(ptr));
		break;
	case alt::INative::Type::ARG_INT32_PTR:
		lua_pushnumber(L, *static_cast<int32_t*>(ptr));
		break;
	case alt::INative::Type::ARG_UINT32_PTR:
		lua_pushnumber(L, *static_cast<uint32_t*>(ptr));
		break;
	case alt::INative::Type::ARG_FLOAT_PTR:
		lua_pushnumber(L, *static_cast<float*>(ptr));
		break;
	case alt::INative::Type::ARG_VECTOR3_PTR:
	{
		auto vector = static_cast<alt::INative::Vector3*>(ptr);
		lua_pushvector3(L, alt::Vector3f(vector->x, vector->y, vector->z));
		break;
	}
	default:
		ret = false;
		break;
	}

	return ret;
}

int CLuaNativeDefs::InvokeNative(lua_State* L)
{
	auto native = static_cast<alt::INative*>(lua_touserdata(L, lua_upvalueindex(1)));
	if (!native->IsValid())
	{
		lua_pushboolean(L, false);
		return 1;
	}

	alt::MValueArgs arguments;

	CArgReader argReader(L);
	argReader.ReadArguments(arguments);

	static auto nativeCtx = Core->CreateNativesContext();

	auto args = native->GetArgTypes();
	auto argsCount = args.GetSize();

	nativeCtx->Reset();

	if (arguments.GetSize() != argsCount)
	{
		Core->LogError("[Lua] Error when invoking native \"" + native->GetName() + "\": argument count doesn't match.");

		lua_pushboolean(L, false);
		return 1;
	}

	for (int i = 0; i < argsCount; i++)
		PushArg(nativeCtx, args[i], arguments[i]);

	if (!native->Invoke(nativeCtx))
	{
		Core->LogError("[Lua] Native call failed");

		lua_pushboolean(L, false);
		return 1;
	}

	GetReturn(L, nativeCtx.Get(), native->GetRetnType());

	uint16_t ptrCount = 0;
	if (pointers.size() > 0)
	{
		for (auto&& pointer : pointers)
			if (GetPtrReturn(L, pointer.ptrType, pointer.ptr))
				ptrCount++;
	}

	//Delete pointers we allocated
	{
		for (auto&& pointer : pointers)
			free(pointer.ptr);

		pointers.clear();
	}

	return ((uint8_t)(native->GetRetnType() != alt::INative::Type::ARG_VOID)) + ptrCount;
}
#endif
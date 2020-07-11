#pragma once

#include "Main.h"

class CArgReader
{
public:
	CArgReader(lua_State *L)
	{
		m_luaVM = L;
		m_stackIndex = 1;
		m_errorOccured = false;
		pendingFunctionRefOut = nullptr;
		pendingFunctionRef = -1;
	}

	~CArgReader()
	{

	}

	bool IsNextType(int type)
	{
		return ((lua_type(m_luaVM, m_stackIndex + 1)) == type);
	}

	bool IsCurrentType(int type)
	{
		return ((lua_type(m_luaVM, m_stackIndex)) == type);
	}

	int GetCurrentType(void)
	{
		return lua_type(m_luaVM, m_stackIndex);
	}

	void ReadBool(bool& state)
	{
		//check if argument is number
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TBOOLEAN || argType == LUA_TSTRING)
		{
			//read if it is
			lua_Number readNumber = lua_toboolean(m_luaVM, m_stackIndex);

			//fill the variable and increase argindex
			state = static_cast<bool>(readNumber);
			m_stackIndex++;

			return;
		}

		AddErrorMessage("bool");

		state = false;
		m_stackIndex++;
	}

	template <typename T>
	T ReadNumber(void)
	{
		T tempNumber;
		ReadNumber(tempNumber);

		return tempNumber;
	}

	template <typename T>
	void ReadNumber(T &number)
	{
		//check if argument is number
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
		{
			if (!lua_isnumber(m_luaVM, m_stackIndex))
				return;

			//read if it is
			lua_Number readNumber = lua_tonumber(m_luaVM, m_stackIndex);

			//fill the variable and increase argindex
			number = static_cast<T>(readNumber);
			m_stackIndex++;

			return;
		}

		AddErrorMessage("number");

		number = 0;
		m_stackIndex++;
	}

	void ReadMValue(alt::MValue& mValue)
	{
		int argType = lua_type(m_luaVM, m_stackIndex);
		switch (argType)
		{
		case LUA_TNUMBER:
			mValue = Core->CreateMValueInt(ReadNumber<int32_t>());
			break;
		case LUA_TBOOLEAN:
			mValue = Core->CreateMValueBool(ReadNumber<bool>());
			break;
		case LUA_TSTRING:
			mValue = Core->CreateMValueString(ReadString<std::string>().c_str());
			break;
		case LUA_TTABLE:
			//Core->LogInfo("Save table");

			//lua_todict(m_luaVM, m_stackIndex);

			//mValue = Core->CreateMValueBool(true);
			Core->LogError("Error: Table save not yet implemented.");
			luaL_error(m_luaVM, "Table save not yet implemented.");
			mValue = Core->CreateMValueNil();
			break;
		case LUA_TFUNCTION:
			//Core->CreateMValueFunction()
			//auto dict = Core->CreateMValueDict();
			
			Core->LogError("Error: Function save not yet implemented.");
			luaL_error(m_luaVM, "Function save not yet implemented.");
			mValue = Core->CreateMValueNil();
			break;
		default:
			Core->LogError("Error happened at ReadMValue");
			break;
		}

		m_stackIndex++;
	}

	template <typename T>
	T ReadString(void)
	{
		T tempString;
		ReadString(tempString);

		return tempString;
	}

	void ReadString(std::string &stringValue, const char* defaultValue = NULL, bool useDefaultValue = true)
	{
		//check if argument is string
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TSTRING)
		{
			//check if it is indeed a string
			if (!lua_isstring(m_luaVM, m_stackIndex))
				return;

			//read if it is
			stringValue.append(luaL_checkstring(m_luaVM, m_stackIndex));

			//fill the variable and increase argindex
			m_stackIndex++;
			return;
		}

		if(!useDefaultValue)
			AddErrorMessage("string");

		stringValue.append(defaultValue);
		m_stackIndex++;
	}

	#define TEST(x) #x

	template <class T>
	void ReadBaseObject(T*& baseObject)
	{
		alt::IBaseObject* tempObject;

		ReadUserData(tempObject);
		baseObject = dynamic_cast<T*>(tempObject);
	}

	template <class T>
	void ReadUserData(T* &userdata)
	{
		//check if argument is number or string
		int argType = lua_type(m_luaVM, m_stackIndex);

		if (argType == LUA_TUSERDATA)
		{
			if (!lua_isuserdata(m_luaVM, m_stackIndex))
				return;

			userdata = reinterpret_cast<T*>(*((void**)lua_touserdata(m_luaVM, m_stackIndex)));
			m_stackIndex++;

			return;
		}

		//if(!useDefaultValue)
		AddErrorMessage(TEST(T));

		userdata = nullptr;
		m_stackIndex++;

		return;
	}

	/*void ReadPosition(alt::Position& number)
	{
		this->ReadVector<float, 3, alt::PointLayout>(number);
	}

	void ReadRotation(alt::Rotation& number)
	{
		this->ReadVector<float, 3, alt::RotationLayout>(number);
	}*/

	void ReadRGBA(alt::RGBA& color)
	{
		//check if argument is number
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
		{
			int number[4];
			for (size_t i = 0; i < 4; i++)
			{
				ReadNumber(number[i]);
			}

			color.r = number[0];
			color.g = number[1];
			color.b = number[2];
			color.a = number[3];

			return;
		}
		else if (argType == LUA_TUSERDATA)
		{
			alt::RGBA* tempColor = nullptr;
			ReadUserData(tempColor);

			if (tempColor)
			{
				color = *tempColor;
				return;
			}
		}

		AddErrorMessage("RGBA");

		color = alt::RGBA();
		m_stackIndex += 4; //Skip 3 values because of Vector
	}

	template<class type, std::size_t size, class _Layout = alt::VectorLayout<type, size>>
	void ReadVector(alt::Vector<type, size, _Layout> &number)
	{
		//check if argument is number
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
		{
			/*if (!lua_isnumber(m_luaVM, m_stackIndex))
				return;

			//read if it is
			lua_Number readNumber = lua_tonumber(m_luaVM, m_stackIndex);

			//fill the variable and increase argindex
			number = static_cast<T>(readNumber);
			m_stackIndex++;*/

			for (size_t i = 0; i < size; i++)
			{
				ReadNumber(number[i]);
			}

			/*ReadNumber(number.x);
			ReadNumber(number.y);
			ReadNumber(number.z);*/

			return;
		}
		else if(argType == LUA_TUSERDATA)
		{
			alt::Vector3<float> *tempVector = nullptr;
			ReadUserData(tempVector);

			if(tempVector)
			{
				number = *tempVector;
				return;
			}
		}

		//TODO: Handle Vector3 object

		AddErrorMessage("Vector3");

		number = alt::Vector<type, size, _Layout>();
		m_stackIndex += 3; //Skip 3 values because of Vector
	}

	void ReadFunction(int& intVariable)
	{
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TFUNCTION)
		{
			intVariable = lua_functionref(m_luaVM, m_stackIndex);

			m_stackIndex++;

			return;
		}

		AddErrorMessage("function");

		intVariable = LUA_NOREF;
		m_stackIndex++;
	}

	//void ReadFunction(int& intVariable)
	//{
	//	int argType = lua_type(m_luaVM, m_stackIndex);
	//	if (argType == LUA_TFUNCTION)
	//	{
	//		//lua_pushvalue(lua_VM, -1);
	//		//intVariable = luaL_ref(lua_VM, LUA_REGISTRYINDEX);
	//		pendingFunctionRefOut = &intVariable; //thanks to MTA
	//		pendingFunctionRef = m_stackIndex;
	//	}

	//	m_stackIndex++;
	//}

	//void ReadFunctionComplete(void)
	//{
	//	if (pendingFunctionRef == -1)
	//	{
	//		Core->LogError("CArgReader::ReadFunctionComplete called before CArgReader::ReadFunction.");
	//		return;
	//	}

	//	lua_stacktrace(m_luaVM, "before settop");

	//	//const void* a = lua_topointer(m_luaVM, -1);
	//	//Core->LogInfo("Pointer1: " + std::to_string(reinterpret_cast<int>(a)));
	//	Core->LogInfo("Pointer2: " + std::to_string((int)lua_objlen(m_luaVM, -1)));

	//	lua_settop(m_luaVM, pendingFunctionRef);
	//	int ref = luaL_ref(m_luaVM, LUA_REGISTRYINDEX);

	//	lua_stacktrace(m_luaVM, "after settop");

	//	Core->LogInfo("Ref shit: " + std::to_string(ref));

	//	*pendingFunctionRefOut = ref;
	//	pendingFunctionRef = -1;
	//}

	//void ReadVector4D(Vector4 &number, Vector4 defaultValue = Vector4(0.0f, 0.0f, 0.0f, 0.0f), bool useDefaultValue = true)
	//{
	//	//check if argument is number
	//	int argType = lua_type(m_luaVM, m_stackIndex);
	//	if (argType == LUA_TNUMBER || argType == LUA_TSTRING)
	//	{
	//		/*if (!lua_isnumber(m_luaVM, m_stackIndex))
	//			return;

	//		//read if it is
	//		lua_Number readNumber = lua_tonumber(m_luaVM, m_stackIndex);

	//		//fill the variable and increase argindex
	//		number = static_cast<T>(readNumber);
	//		m_stackIndex++;*/

	//		ReadNumber(number.x);
	//		ReadNumber(number.y);
	//		ReadNumber(number.z);
	//		ReadNumber(number.w);
	//		
	//		return;
	//	}

	//	//TODO: Handle Vector4 object

	//	if(!useDefaultValue)
	//		AddErrorMessage("vector4");

	//	number = defaultValue;
	//	m_stackIndex += 4; //Skip 4 values because of Vector
	//}

	void AddMessage(const std::string &errorMessage)
	{
		m_errorMessages.push_back(errorMessage);
	}

	void AddErrorMessage(const char* expectedType)
	{
		char buffer[128];

		lua_Debug debugInfo;
		lua_getdebuginfo(m_luaVM, debugInfo);

		int argType = lua_type(m_luaVM, m_stackIndex);

		sprintf_s(buffer, "Bad Argument (%s:%d) Expected argument at index %d: '%s', got '%s' instead.", debugInfo.name, debugInfo.currentline, m_stackIndex, expectedType, lua_typename(m_luaVM, argType));

		AddMessage(buffer);

		m_errorOccured = true;
	}

	bool HasAnyError(void)
	{
		return m_errorOccured;
	}

	void GetErrorMessages(void)
	{
		for (auto &message : m_errorMessages)
		{
			Core->LogError(message);
		}
	}

private:
	lua_State*	m_luaVM;
	int*		pendingFunctionRefOut;
	int			pendingFunctionRef;

	int			m_stackIndex;
	bool		m_errorOccured;

	std::vector<std::string> m_errorMessages;
};
#pragma once

#include "Main.h"

class CArgReader
{
public:
	CArgReader(lua_State *L)
	{
		m_luaVM = L;
		m_stackIndex = 1;
		m_stackNum = lua_gettop(L);
		m_errorOccured = false;
		pendingFunctionRefOut = nullptr;
		pendingFunctionRef = -1;
	}

	~CArgReader()
	{

	}

#define SET_DEFAULT(A, B) if(A != nullptr) (*A) = B

	const char* ToString()
	{
		return luaL_tolstring(m_luaVM, m_stackIndex++, NULL);
	}

	int GetArgNum()
	{
		return m_stackNum;
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

	bool ReadBool(void)
	{
		bool tempBool;

		ReadBool(tempBool);

		return tempBool;
	}

	void ReadBoolDefault(bool& state, bool defaultValue)
	{
		bool tempBool, isDefault;
		ReadBool(tempBool, &isDefault);

		state = isDefault ? defaultValue : tempBool;
	}

	void ReadBool(bool& state, bool* isDefault = nullptr)
	{
		//check if argument is number
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TBOOLEAN || argType == LUA_TSTRING)
		{
			//read if it is
			lua_Number readNumber = lua_toboolean(m_luaVM, m_stackIndex);

			//fill the variable and increase argindex
			state = static_cast<bool>(readNumber);
			
			SET_DEFAULT(isDefault, false);

			m_stackIndex++;

			return;
		}

		if(isDefault == nullptr)
			AddErrorMessage("bool");

		state = false;

		SET_DEFAULT(isDefault, true);

		m_stackIndex++;
	}

	template <typename T>
	void ReadNumber(T &number, bool* isDefault = nullptr)
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

			SET_DEFAULT(isDefault, false);

			return;
		}

		if(isDefault == nullptr)
			AddErrorMessage("number");

		SET_DEFAULT(isDefault, true);

		number = 0;
		m_stackIndex++;
	}

	template <typename T>
	T ReadNumber(void)
	{
		T tempNumber;
		ReadNumber(tempNumber);

		return tempNumber;
	}

	/*template <typename T>
	void ReadNumberDefault(T& number, T defaultValue)
	{
		T tempNumber;
		bool isDefault;
		ReadNumber(tempNumber, &isDefault);

		number = isDefault ? defaultValue : tempNumber;
	}*/

	void ReadMValue(alt::MValue& mValue)
	{
		mValue = lua_tomvalue(m_luaVM, m_stackIndex);
		m_stackIndex++;
	}

	template <typename T>
	T ReadString(void)
	{
		T tempString;
		ReadString(tempString);

		return tempString;
	}

	void ReadString(std::string &stringValue)
	{
		//check if argument is string
		int argType = lua_type(m_luaVM, m_stackIndex);
		if (argType == LUA_TSTRING || argType == LUA_TNUMBER)
		{
			//check if it is indeed a string
			//if (!lua_isstring(m_luaVM, m_stackIndex))
			//	return;

			//read if it is
			stringValue.append(luaL_checkstring(m_luaVM, m_stackIndex));

			//fill the variable and increase argindex
			m_stackIndex++;
			return;
		}

		AddErrorMessage("string");
		stringValue = "";

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

	template <class type, std::size_t size, class _Layout = alt::VectorLayout<type, size>>
	void ReadVectorDefault(alt::Vector<type, size, _Layout>& number, alt::Vector<type, size, _Layout> defaultValue)
	{
		alt::Vector<type, size, _Layout> tempNumber;
		bool isDefault;
		ReadVector(tempNumber, &isDefault);

		number = isDefault ? defaultValue : tempNumber;
	}

	template<class type, std::size_t size, class _Layout = alt::VectorLayout<type, size>>
	void ReadVector(alt::Vector<type, size, _Layout> &number, bool* isDefault = nullptr)
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

			SET_DEFAULT(isDefault, false);

			/*ReadNumber(number.x);
			ReadNumber(number.y);
			ReadNumber(number.z);*/

			return;
		}
		else if(argType == LUA_TUSERDATA)
		{
			alt::Vector<type, size, _Layout> *tempVector = nullptr;
			ReadUserData(tempVector);

			if(tempVector)
			{
				number = *tempVector;
				SET_DEFAULT(isDefault, false);
				return;
			}
		}

		//TODO: Handle Vector3 object

		if(isDefault == nullptr)
			AddErrorMessage("Vector");

		SET_DEFAULT(isDefault, true);

		number = alt::Vector<type, size, _Layout>();
		m_stackIndex += 1; //Skip 3 values because of Vector
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

	void ReadArguments(alt::MValueArgs& arguments)
	{
		int argSize = lua_gettop(m_luaVM);
		for (int argIndex = m_stackIndex; argIndex <= argSize; argIndex++)
		{
			arguments.Push(lua_tomvalue(m_luaVM, argIndex));

			m_stackIndex++;
		}
	}

	void SkipValue(void)
	{
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
	int			m_stackNum;
	bool		m_errorOccured;

	std::vector<std::string> m_errorMessages;
};
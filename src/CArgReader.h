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

	template <typename T>
	void ReadNumber(T &number, T defaultValue = 0, bool useDefaultValue = true)
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

		if(!useDefaultValue)
			AddErrorMessage("number");

		number = defaultValue;
		m_stackIndex++;
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

	template <typename T>
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

	void ReadPosition(alt::Position& number, alt::Position defaultValue = alt::Position(), bool useDefaultValue = true)
	{
		this->ReadVector<float, 3, alt::PointLayout>(number, defaultValue, useDefaultValue);
	}

	void ReadRotation(alt::Rotation& number, alt::Rotation defaultValue = alt::Rotation(), bool useDefaultValue = true)
	{
		this->ReadVector<float, 3, alt::RotationLayout>(number, defaultValue, useDefaultValue);
	}

	template<class type, std::size_t size, class _Layout = alt::VectorLayout<type, size>>
	void ReadVector(alt::Vector<type, size, _Layout> &number, alt::Vector<type, size, _Layout> defaultValue = alt::Vector<type, size, _Layout>(), bool useDefaultValue = true)
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

		if(!useDefaultValue)
			AddErrorMessage("vector3");

		number = defaultValue;
		m_stackIndex += 3; //Skip 3 values because of Vector
	}

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

		sprintf(buffer, "Bad Argument (%s:%d) Expected argument at index %d: '%s', got '%s' instead.", debugInfo.name, debugInfo.currentline, m_stackIndex, expectedType, lua_typename(m_luaVM, argType));

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
			Core->LogInfo(message);
		}
	}

private:
	lua_State *m_luaVM;

	int m_stackIndex;
	bool m_errorOccured;

	std::vector<std::string> m_errorMessages;
};
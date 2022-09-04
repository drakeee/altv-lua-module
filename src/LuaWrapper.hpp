#pragma once

#include <new>
#include <string>
#include <assert.h>
#include <type_traits>
#include <iostream>
#include <optional>

#include <lua.hpp>

namespace lua
{
	class State;

	template<typename x_Function>
	class FunctionHelper;

	template<typename x_Result, typename... x_Args>
	class FunctionHelper<x_Result(x_Args...)>
	{
	public:
		using arguments = ::std::tuple<x_Args...>;
		typedef std::optional<x_Result>(*function)(x_Args...);
	};

	template<typename Type, typename...>
	struct Function;

	template<typename Type, typename... Params>
	struct Function<Type(Params...)>
	{
	public:
		State* state = nullptr;

		int functionIndex;
		int functionArgumentsCount;
		std::optional<Type>(*function)(Function<Type(Params...)>*, Params...);

		std::optional<Type> operator()(Params... args)
		{
			return function(this, args...);
		}
	};

	class FunctionException : public std::exception {
	public:
		explicit FunctionException(std::string& e)
			: std::exception(e.c_str()) {}

		explicit FunctionException(const char* e)
			: std::exception(e) {}
	};

	class State
	{
	public:
		State(bool defaultLibs = true)
		{
			this->m_State = luaL_newstate();
			if (this->m_State == nullptr)
				throw std::bad_alloc();

			lua_atpanic(this->m_State, [](lua_State* L) -> int
				{
					const std::string errorMessage = lua_tostring(L, -1);
					printf("lua_atpanic: %s\n", errorMessage.c_str());

					lua_pop(L, 1);

					assert(false && "lua_atpanic triggered");

					return 0;
				});

			if(defaultLibs)
				luaL_openlibs(this->m_State);
		}

	public:

		lua_State* GetState() { return this->m_State; }
		constexpr lua_State* operator*() & noexcept
		{
			return this->m_State;
		}

	public:
		bool ExecuteCode(const char* code)
		{
			try
			{
				if (luaL_dostring(this->m_State, code) != LUA_OK)
				{
					//Get the error from the top of the stack
					if (lua_isstring(this->m_State, -1))
					{
						throw std::runtime_error(std::string() + "Error when executing code: " + std::string(luaL_checkstring(this->m_State, -1)));
						//printf("ExecuteCode throw error: %s\n", luaL_checkstring(this->m_State, -1));
						//throw std::runtime_error("Test");
					}

					return false;
				}
			}
			catch (const FunctionException& e)
			{
				printf("Function error: %s\n", e.what());
			}

			return true;
		}

		template<typename Type>
		std::optional<Type> ReadVariable(const char* variableName)
		{
			lua_getglobal(this->m_State, variableName);
			if (lua_isnil(this->m_State, -1))
			{
				lua_pop(this->m_State, 1);
				return std::nullopt;
			}

			auto result = Value<Type>::Read(this, -1);

			if(lua_type(this->m_State, -1) != LUA_TFUNCTION)
				lua_pop(this->m_State, 1);

			return result;
		}

		template<typename Type>
		void WriteVariable(const char* variableName, Type value)
		{
			Value<Type>::Write(this, value);
			lua_setglobal(this->m_State, variableName);
		}

		template<typename Type, typename... Params>
		std::optional<Function<Type>> ReadFunction(const char* functionName)
		{
			lua_getglobal(this->m_State, functionName);
			lua_stacktrace_ex(this->m_State, "ReadFunction2");

			if (lua_isnil(this->m_State, -1))
			{
				printf("Is nil!\n");

				lua_pop(this->m_State, 1);
				return std::nullopt;
			}

			assert(lua_type(this->m_State, -1) == LUA_TFUNCTION && "ReadFunction: Function expected at top");


			return Value<Type>::Read(this, -1);
		}

		template<typename Type, typename... Params>
		void WriteFunction(const char* functionName, std::optional<Type>(*value)(Params...))
		{
			Value<Type(Params...)>::Write(this, value);
			lua_setglobal(this->m_State, functionName);
		}

		template<typename Type>
		std::optional<Type> Read(int index)
		{
			return Value<Type>::Read(this, index);
		}

		template<typename Type>
		void Write(Type value)
		{
			Value<Type>::Write(this, value);
		}

		template<typename Type>
		void RegisterVariable(std::string& variableName, Type value)
		{
			Value<Type>::Write(this, value);
			lua_setglobal(this->m_State, variableName.c_str());
		}

		template<typename Type>
		void RegisterVariable(const char* variableName, Type value)
		{
			this->RegisterVariable(std::string(variableName), value);
		}

	private:
		lua_State* m_State;
	};

	template<typename T, typename = void, typename...>
	struct Value;

	template<typename ReturnType, typename... Params>
	struct Value<ReturnType(Params...)>
	{
	private:
		template<typename Type>
		static inline void WriteHelper(State* state, Type t)
		{
			Value<Type>::Write(state, t);
		}

		template<typename Type>
		static inline Type ReadHelper(State* state, int index)
		{
			return Value<Type>::Read(state, index);
		}

	public:
		static inline std::optional<Function<ReturnType(Params...)>> Read(State* state, int index)
		{
			Function<ReturnType(Params...)> returnFunc;
			returnFunc.state = state;
			returnFunc.functionIndex = lua_gettop(state->GetState());
			returnFunc.functionArgumentsCount = sizeof...(Params);
			returnFunc.function = [](Function<ReturnType(Params...)>* obj, Params... args) -> std::optional<ReturnType>
			{
				(WriteHelper(obj->state, args), ...);

				assert(lua_type(obj->state->GetState(), obj->functionIndex) == LUA_TFUNCTION && "Function expected");

				constexpr bool is_return_void = std::is_same<ReturnType, void>::value;

				if (lua_pcall(obj->state->GetState(), obj->functionArgumentsCount, !is_return_void, 0))
					throw FunctionException(std::string() + "Error when executing function: " + std::string(luaL_checkstring(obj->state->GetState(), -1)));;

				if (!is_return_void)
				{
					auto result = Value<ReturnType>::Read(obj->state, -1);
					lua_pop(obj->state->GetState(), 1);

					return result;
				}

				return std::nullopt;
			};

			return std::make_optional(std::move(returnFunc));
		}

		struct ProxyFunction
		{
			template<int N, typename... Ts>
			using NthTypeOf = typename std::tuple_element<N, std::tuple<Ts...>>::type;

			template <typename... Result, std::size_t... Indices>
			static inline auto args_to_tup_helper(State* state, std::index_sequence<Indices...> b) {

				size_t stackSize = lua_gettop(state->GetState());
				if (stackSize != sizeof...(Params))
					throw FunctionException(std::string("Stack size doesn't match up with params size. Stack size: " + std::to_string(stackSize) + " | Parameter size: " + std::to_string(sizeof...(Params))));

				return std::make_tuple(
					Value<NthTypeOf<Indices, Result...>>::Read(state, Indices + 1).value()...
				);
			}

			template <typename ...Result>
			static inline auto args_to_tup(State* state)
			{
				return args_to_tup_helper<Result...>(state, std::make_index_sequence<sizeof...(Result)>());
			}

			static inline int Function(lua_State* L)
			{
				State* state = reinterpret_cast<State*>(lua_touserdata(L, lua_upvalueindex(1)));
				std::optional<ReturnType>(*func)(Params...) = reinterpret_cast<std::optional<ReturnType>(*)(Params...)>(lua_touserdata(L, lua_upvalueindex(2)));

				try
				{
					auto argument_tuple = args_to_tup<Params...>(state);
					std::apply(func, argument_tuple);
				}
				catch (const FunctionException& e)
				{
					//throw FunctionException(e.what());
					//printf("FunctionException: %s\n", e.what());
					return luaL_error(L, e.what());
				}

				printf("ProxyFunction: %p - %p\n", state, func);
				return 0;
			}
		};

		static inline void Write(State* state, std::optional<ReturnType>(*value)(Params...))
		{
			printf("Write: %p - %p\n", state, value);

			lua_pushlightuserdata(state->GetState(), reinterpret_cast<void*>(state));
			lua_pushlightuserdata(state->GetState(), reinterpret_cast<void*>(value));
			lua_pushcclosure(state->GetState(), &ProxyFunction::Function, 2);
		}
	};

	template<>
	struct Value<void>
	{
		static inline std::optional<void*> Read(State* state, int index)
		{
			return std::nullopt;
		};

		static inline void Write(State* state, void* a = nullptr)
		{
			lua_pushnil(state->GetState());
		};
	};

	template<typename Integer>
	struct Value<Integer, typename std::enable_if<std::is_integral<Integer>::value>::type>
	{
		static inline std::optional<Integer> Read(State* state, int index)
		{
			if (lua_type(state->GetState(), index) != LUA_TNUMBER)
				return std::nullopt;

			int temp;
			Integer result = static_cast<Integer>(lua_tointegerx(state->GetState(), index, &temp));

			return (temp == 1) ? std::make_optional(result) : std::nullopt;
		}

		static inline void Write(State* state, Integer value)
		{
			lua_pushinteger(state->GetState(), value);
		}
	};

	template<typename Float>
	struct Value<Float, typename std::enable_if<std::is_floating_point<Float>::value>::type>
	{
		static inline std::optional<Float> Read(State* state, int index)
		{
			if (lua_type(state->GetState(), index) != LUA_TNUMBER)
				return 0;

			int temp;
			Float result = static_cast<Float>(lua_tonumberx(state->GetState(), index, &temp));

			return (temp == 1) ? std::make_optional(result) : std::nullopt;
		}

		static inline void Write(State* state, Float value)
		{
			lua_pushnumber(state->GetState(), value);
		}
	};

	template<>
	struct Value<const char*>
	{
		static inline std::optional<const char*> Read(State* state, int index)
		{
			printf("index: %p - %d\n", state, index);

			const auto value = lua_tostring(state->GetState(), index);
			if (value == NULL)
				return std::nullopt;

			return value;
		}

		static inline void Push(State* state, const char* value)
		{
			lua_pushstring(state->GetState(), value);
		}
	};

	template<>
	struct Value<std::string>
	{
		static inline std::optional<std::string> Read(State* state, int index)
		{
			return Value<const char*>::Read(state, index);
		}

		static inline std::string Push(State* state, const std::string& value)
		{
			lua_pushstring(state->GetState(), value.c_str());
		}
	};

	template<>
	struct Value<bool>
	{
		static inline std::optional<bool> Read(State* state, int index)
		{
			if (lua_type(state->GetState(), index) != LUA_TBOOLEAN)
				return std::nullopt;

			return lua_toboolean(state->GetState(), index);
		}

		static inline void Write(State* state, bool value)
		{
			lua_pushboolean(state->GetState(), value);
		}
	};
}
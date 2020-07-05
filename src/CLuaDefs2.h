#pragma once

#include <Main.h>

#define L_ASSERT(a,b) \
	assert((!a?(Core->LogError(b),true):true)&&a)

#define lua_globalfunction(a,b,c) \
	lua_register(a,b,c)

//#define lua_endstaticclass(a) \
//	lua_endclass(L,true)

void lua_initclass(lua_State* L);
void lua_beginclass(lua_State* L, const char* className, const char* baseClass = nullptr);
void lua_endclass(lua_State* L);
void lua_getclass(lua_State* L, const char* className);
void lua_getclassmt(lua_State* L, const char* className);
void lua_classfunction(lua_State* L, const char* functionName, const char* globalFuncName);
void lua_classfunction(lua_State* L, const char* functionName, lua_CFunction function);
void lua_classmeta(lua_State* L, const char* metaName, lua_CFunction metaFunction, bool isClosure = false); //if isClosure set to true we store metatable in the upvalue
void lua_classvariable(lua_State* L, const char* variableName, const char* setFunction, const char* getFunction);

void lua_pushuserdata(lua_State* L, const char* className, void* pObject, bool refUserData = true);
void lua_pushmvalue(lua_State* L, alt::MValueConst mValue);

void lua_stacktrace(lua_State* L, const char* stackName = "Unknown");
void lua_dumptable(lua_State* L, int idx, int level = 0);
void lua_getdebuginfo(lua_State* L, lua_Debug& debugInfo);
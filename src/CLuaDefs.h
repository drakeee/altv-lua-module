#pragma once

#include <Main.h>

#ifdef __linux__
#include <Defs/CLuaVector3Defs.h>
#endif

#define L_ASSERT(a,b) \
	assert((!a?(Core->LogError(b),true):true)&&a)


/*#define lua_globalfunction(a,b,c) \
	lua_register(a,b,c)*/

//#define lua_endstaticclass(a) \
//	lua_endclass(L,true)
void lua_globalfunction(lua_State* L, const char* functionName, lua_CFunction func);

void lua_initclass(lua_State* L);
void lua_beginclass(lua_State* L, const char* className, const char* baseClass = nullptr);
void lua_endclass(lua_State* L);
void lua_getclass(lua_State* L, const char* className);
void lua_getclassmt(lua_State* L, const char* className);
void lua_classfunction(lua_State* L, const char* functionName, const char* globalFuncName);
void lua_classfunction(lua_State* L, const char* functionName, lua_CFunction function);
void lua_classmeta(lua_State* L, const char* metaName, lua_CFunction metaFunction, bool useClosure = false); //if useClosure set to true we store metatable in the upvalue
void lua_classvariable(lua_State* L, const char* variableName, const char* setFunction, const char* getFunction);

void lua_pushuserdata(lua_State* L, const char* className, void* pObject, bool refUserData = true);
void lua_pushbaseobject(lua_State* L, alt::IBaseObject* baseObject, bool refUserData = true);

template<class T, std::size_t W, class _Layout = alt::VectorLayout<T, W>>
void lua_pushvector(lua_State* L, const alt::Vector<T, W, _Layout>& vector, bool refUserData = false)
{
	alt::Vector<T, W, _Layout>* vec = new alt::Vector<T, W, _Layout>(vector);
	lua_pushuserdata(L, CLuaVector3Defs::ClassName, vec, refUserData);
}
//void lua_pushvehicle(lua_State* L, alt::IVehicle* vehicle, bool refUserData = true);
void lua_pushrgba(lua_State* L, const alt::RGBA &color, bool refUserData = false);
void lua_pushmvalue(lua_State* L, const alt::MValueConst &mValue);
void lua_pushmvalueargs(lua_State* L, alt::MValueArgs& args);
void lua_pushresource(lua_State* L, alt::IResource* resource, bool refUserData = true);
void lua_pushstringarray(lua_State* L, const alt::Array<alt::StringView>& array);
int lua_functionref(lua_State* L, int idx);

void lua_todict(lua_State* L, int idx);
alt::MValue lua_tomvalue(lua_State* L, int indx);
//void lua_toentity(lua_State* L, alt::IEntity* entity);

void lua_stacktrace(lua_State* L, const char* stackName = "Unknown");
void lua_dumptable(lua_State* L, int idx, int level = 0);
void lua_getdebuginfo(lua_State* L, lua_Debug& debugInfo);
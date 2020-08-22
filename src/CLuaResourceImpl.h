#pragma once

#include <Main.h>

class CLuaScriptRuntime;
class CLuaResourceImpl : public alt::IResource::Impl
{
public:
	class LuaFunction : public alt::IMValueFunction::Impl
	{
	public:
		LuaFunction(CLuaResourceImpl* resource, int functionRef) :
			resource(resource),
			functionRef(functionRef)
		{

		}
		~LuaFunction() {}

		alt::MValue Call(alt::MValueArgs args) const override;

	private:
		CLuaResourceImpl* resource;
		int functionRef;
	};

	typedef std::map<std::string, std::vector<int>>		EventsReferences;

	CLuaResourceImpl(CLuaScriptRuntime* runtime, alt::IResource* resource);
	~CLuaResourceImpl();

#ifdef ALT_SERVER_API
	bool MakeClient(alt::IResource::CreationInfo* info, alt::Array<alt::String> files) override;
#endif

	bool Start() override;
	bool Stop() override;

	bool OnEvent(const alt::CEvent* ev) override;
	void OnTick() override;

	void OnCreateBaseObject(alt::Ref<alt::IBaseObject> object) override;
	void OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object) override;

	lua_State*	GetLuaState(void) { return this->resourceState; }
	bool		RegisterEvent(std::string eventName, int functionReference);
	bool		RemoveEvent(std::string eventName, int functionReference);
	bool		RegisterClientEvent(std::string eventName, int functionReference);
	bool		RemoveClientEvent(std::string eventName, int functionReference);
	void		TriggerResourceLocalEvent(std::string eventName, alt::MValueArgs args);
	void		IncludeModulesPath(void);
	inline const std::vector<int>& GetEventReferences(std::string eventName)
	{
		return this->eventsReferences[eventName];
	}
	inline const std::vector<int>& GetClientEventReferences(std::string eventName)
	{
		return this->clientEventsReferences[eventName];
	}
	inline bool				AddFunctionRef(const void* ptr, int functionRef)
	{
		if (this->IsFunctionRefExists(ptr))
			return false;

		this->functionReferences[ptr] = functionRef;
		return true;
	}
	inline bool				RemoveFunctionRef(const void* ptr)
	{
		if (!this->IsFunctionRefExists(ptr))
			return false;

		this->functionReferences.erase(ptr);
		return true;
	}
	inline bool				IsFunctionRefExists(const void* ptr)
	{
		return this->functionReferences.find(ptr) != this->functionReferences.end();
	}
	inline int				GetFunctionRef(const void* ptr)
	{
		if (!this->IsFunctionRefExists(ptr))
			return LUA_NOREF;

		return this->functionReferences[ptr];
	}
	inline void				AddExport(std::string exportName, LuaFunction* func)
	{
		this->exportFunction->Set(exportName, Core->CreateMValueFunction(func));
	}
	inline bool				IsExportExists(std::string exportName)
	{
		return this->exportFunction->Get(exportName)->GetType() != alt::IMValue::Type::NONE;
	}
	inline alt::IResource* GetResource(void)
	{
		return this->resource;
	}
	inline std::string& GetWorkingPath(void)
	{
		return this->workingPath;
	}
	inline std::map<std::string, bool>& GetLoadedFiles(void)
	{
		return this->loadedFiles;
	}

private:
	lua_State*			resourceState = nullptr;
	CLuaScriptRuntime*	runtime;
	alt::IResource*		resource;
	std::string			workingPath;

	EventsReferences			eventsReferences;
	EventsReferences			clientEventsReferences;
	std::map<const void*, int>	functionReferences;
	alt::MValueDict				exportFunction;
	std::map<std::string, bool> loadedFiles;
};
#pragma once

#include <Main.h>

class LuaScriptRuntime;
class LuaResourceImpl : public alt::IResource::Impl
{
public:
	struct LuaTimer
	{
		uint32_t functionIndex;
		uint32_t interval;
		bool repeat;
		int64_t lastTime;
	};

	class LuaFunction : public alt::IMValueFunction::Impl
	{
	public:
		LuaFunction(LuaResourceImpl* resource, int functionRef) :
			resource(resource),
			functionRef(functionRef)
		{

		}
		~LuaFunction() {}

		alt::MValue Call(alt::MValueArgs args) const override;

	private:
		LuaResourceImpl* resource;
		int functionRef;
	};

	typedef std::map<std::string, std::vector<int>>		EventsReferences;

	LuaResourceImpl(LuaScriptRuntime* runtime, alt::IResource* resource);
	~LuaResourceImpl();

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
	//bool		RegisterLocalEvent(std::string eventName, int functionReference);
	//bool		RemoveLocalEvent(std::string eventName, int functionReference);
	//bool		RegisterRemoteEvent(std::string eventName, int functionReference);
	//bool		RemoveRemoteEvent(std::string eventName, int functionReference);
#ifdef ALT_CLIENT_API
	//bool		RegisterWebEvent(alt::IWebView* webView, std::string eventName, int functionReference);
	//bool		RemoveWebEvent(alt::IWebView* webView, std::string eventName, int functionReference);
	/*inline const std::vector<int>& GetWebEventReferences(alt::IWebView* webView, std::string eventName)
	{
		return this->webEventsReferences[webView][eventName];
	}*/

	//bool		RegisterWebSocketEvent(alt::IWebSocketClient* webSocket, std::string eventName, int functionReference);
	//bool		RemoveWebSocketEvent(alt::IWebSocketClient* webSocket, std::string eventName, int functionReference);
	/*inline const std::vector<int>& GetWebSocketEventReferences(alt::IWebSocketClient* webSocket, std::string eventName)
	{
		return this->webSocketEventsReferences[webSocket][eventName];
	}*/

	inline bool IsScriptExists(alt::String path)
	{
		auto pkg = resource->GetPackage();
		return pkg->FileExists(path);
	}

	inline alt::String GetScript(alt::String path)
	{
		auto pkg = resource->GetPackage();
		if (!pkg->FileExists(path))
		{
			Core->LogError(" Client main \"" + path + "\" is not found");
			return true;
		}

		auto file = pkg->OpenFile(path);
		alt::String script{ pkg->GetFileSize(file) };

		pkg->ReadFile(file, script.GetData(), script.GetSize());
		pkg->CloseFile(file);

		return script;
	}
#endif
	inline ResourceEventManager* GetResourceEventManager() { return this->resourceEventManager; }
	void		TriggerResourceLocalEvent(std::string eventName, alt::MValueArgs args);
	void		IncludePath(const char* path);
	/*inline const std::vector<int>& GetLocalEventReferences(std::string eventName)
	{
		return this->localEventsReferences[eventName];
	}
	inline const std::vector<int>& GetRemoteEventReferences(std::string eventName)
	{
		return this->remoteEventsReferences[eventName];
	}*/
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

		luaL_unref(this->resourceState, LUA_REGISTRYINDEX, this->GetFunctionRef(ptr));

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
	inline const void* GetFunctionRefByID(int functionRef)
	{
		for (auto it = this->functionReferences.begin(); it != this->functionReferences.end(); ++it)
			if (it->second == functionRef)
				return it->first;

		return nullptr;
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
#ifdef ALT_SERVER_API
	inline alt::config::Node::Dict& GetResourceConfig(void)
	{
		return this->resourceConfigDict;
	}
#endif
	inline bool AddEntity(alt::IBaseObject* baseObject)
	{
		auto entityFound = std::find(this->entities.begin(), this->entities.end(), baseObject) != this->entities.end();
		if (entityFound)
			return false;
		
		this->entities.push_back(baseObject);
		return true;
	}

	inline bool RemoveEntity(alt::IBaseObject* baseObject)
	{
		auto it = std::find(this->entities.begin(), this->entities.end(), baseObject);
		if (it == this->entities.end())
			return false;

		this->entities.erase(it);
		return true;
	}

	uint32_t CreateTimer(uint32_t functionIndex, uint32_t interval, bool repeat);
	inline bool DestroyTimer(uint32_t timerIndex)
	{
		return (this->timerReferences.erase(timerIndex) > 0);
	}

private:
	lua_State*			resourceState = nullptr;
	LuaScriptRuntime*	runtime;
	ResourceEventManager* resourceEventManager;

#ifdef ALT_SERVER_API
	alt::config::Node::Dict resourceConfigDict;
#endif
	alt::IResource*		resource;
	std::string			workingPath;

	//EventsReferences			localEventsReferences;
	//EventsReferences			remoteEventsReferences;

	uint32_t timerIndex = -1;
	std::map<uint32_t, LuaTimer>	timerReferences;

#ifdef ALT_CLIENT_API
	//std::map<alt::IWebView*, EventsReferences> webEventsReferences;
	//std::map<alt::IWebSocketClient*, EventsReferences> webSocketEventsReferences;
#endif

	std::map<const void*, int>	functionReferences;
	alt::MValueDict				exportFunction;
	std::map<std::string, bool> loadedFiles;
	std::list<alt::IBaseObject*> entities;
};
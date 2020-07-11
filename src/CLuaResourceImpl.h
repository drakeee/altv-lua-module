#pragma once

#include <Main.h>

class CLuaScriptRuntime;
class CLuaResourceImpl : public alt::IResource::Impl
{
public:
	typedef std::map<std::string, std::vector<int>>		EventsReferences;

	CLuaResourceImpl(CLuaScriptRuntime* runtime, alt::IResource* resource);
	~CLuaResourceImpl();

	bool Start() override;
	bool Stop() override;

	bool OnEvent(const alt::CEvent* ev) override;
	void OnTick() override;

	void OnCreateBaseObject(alt::Ref<alt::IBaseObject> object) override;
	void OnRemoveBaseObject(alt::Ref<alt::IBaseObject> object) override;

	lua_State*	GetLuaState(void) { return this->resourceState; }
	bool		RegisterEvent(std::string eventName, int functionReference);
	bool		RemoveEvent(std::string eventName, int functionReference);

private:
	lua_State*			resourceState = nullptr;
	CLuaScriptRuntime*	runtime;
	alt::IResource*		resource;

	EventsReferences	eventsReferences;
};
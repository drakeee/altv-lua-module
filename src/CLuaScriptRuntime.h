#pragma once

#include "Main.h"

class CLuaScriptRuntime : public alt::IScriptRuntime
{

public:
	alt::IResource::Impl*	CreateImpl(alt::IResource* resource) override;
	void					DestroyImpl(alt::IResource::Impl* impl) override;

	static CLuaScriptRuntime& Instance()
	{
		static CLuaScriptRuntime _Instance;
		return _Instance;
	}

private:
	//alt::ICore* _core = &alt::ICore::Instance();

protected:
	CLuaScriptRuntime() {};
	~CLuaScriptRuntime() {};
};
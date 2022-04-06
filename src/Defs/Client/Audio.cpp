#include <Main.h>

#ifdef ALT_CLIENT_API

namespace lua::Class
{
	const char* Audio::ClassName = "Audio";
	void Audio::Init(lua_State* L)
	{
        lua_beginclass(L, Audio::ClassName, BaseObject::ClassName);
        {
            lua_classfunction(L, "new", CreateAudio);
            lua_classfunction(L, "on", On);
            lua_classfunction(L, "off", Off);

            lua_classfunction(L, "addOutput", AddOutput);
            lua_classfunction(L, "removeOutput", RemoveOutput);
            lua_classfunction(L, "getOutputs", GetOutputs);

            lua_classfunction(L, "play", Play);
            lua_classfunction(L, "pause", Pause);
            lua_classfunction(L, "reset", Reset);
            lua_classfunction(L, "seek", Seek);

            lua_classvariable(L, "source", SetSource, GetSource);
            lua_classvariable(L, "looped", SetLoop, IsLoop);
            lua_classvariable(L, "volume", SetVolume, GetVolume);
            lua_classvariable(L, "category", SetCategory, GetCategory);
            lua_classvariable(L, "frontendPlay", nullptr, IsFrontendPlay);
            lua_classvariable(L, "currentTime", nullptr, GetCurrentTime);
            lua_classvariable(L, "maxTime", nullptr, GetMaxTime);
            lua_classvariable(L, "playing", nullptr, IsPlaying);
        }
        lua_endclass(L);
	}

    int Audio::CreateAudio(lua_State* L)
    {
        std::string source;
        float volume;
        uint32_t category;
        std::string categoryString;
        bool frontend;

        ArgumentReader argReader(L);
        argReader.ReadString(source);
        argReader.ReadNumber(volume);
        if (argReader.IsNextType(LUA_TNUMBER))
            argReader.ReadNumberDefault(category, (uint32_t)0);
        else
        {
            argReader.ReadString(categoryString);
            category = Core->Hash(categoryString);
        }
        argReader.ReadBoolDefault(frontend, false);

        if (argReader.HasAnyError())
        {
            argReader.GetErrorMessages();
            return 0;
        }

        LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);

        lua_pushbaseobject(L, Core->CreateAudio(source, volume, category, frontend, resourceImpl->GetResource()));

        return 1;
    }

    int Audio::On(lua_State* L)
    {
        alt::IAudio* audio;
        std::string eventName;
        int functionIndex;

        ArgumentReader argReader(L);
        argReader.ReadUserData(audio);
        argReader.ReadString(eventName);
        argReader.ReadFunction(functionIndex);

        if (argReader.HasAnyError())
        {
            argReader.GetErrorMessages();
            return 0;
        }

        LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
        ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

        lua_pushboolean(L, resourceEventManager->SubscribeEvent(audio, eventName, functionIndex));

        return 1;
    }

    int Audio::Off(lua_State* L)
    {
        alt::IAudio* audio;
        std::string eventName;
        int functionIndex;

        ArgumentReader argReader(L);
        argReader.ReadUserData(audio);
        argReader.ReadString(eventName);
        argReader.ReadFunction(functionIndex);

        if (argReader.HasAnyError())
        {
            argReader.GetErrorMessages();
            return 0;
        }

        LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
        ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

        lua_pushboolean(L, resourceEventManager->UnsubscribeEvent(audio, eventName, functionIndex));

        return 1;
    }

    int Audio::SetSource(lua_State* L)
    {
        alt::IAudio* audio;
        std::string source;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);
        argReader.ReadString(source);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->SetSource(source);

        return 0;
    }

    int Audio::GetSource(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushstring(L, audio->GetSource().ToString());

        return 1;
    }

    int Audio::SetLoop(lua_State* L)
    {
        alt::IAudio* audio;
        bool toggle;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);
        argReader.ReadBool(toggle);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->SetLoop(toggle);

        return 0;
    }

    int Audio::SetVolume(lua_State* L)
    {
        alt::IAudio* audio;
        float volume;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);
        argReader.ReadNumber(volume);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->SetVolume(volume);

        return 0;
    }

    int Audio::SetCategory(lua_State* L)
    {
        alt::IAudio* audio;
        uint32_t category;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);
        argReader.ReadNumber(category);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->SetCategory(category);

        return 0;
    }

    int Audio::IsLoop(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushboolean(L, audio->IsLoop());

        return 1;
    }

    int Audio::GetVolume(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushnumber(L, audio->GetVolume());

        return 1;
    }

    int Audio::GetCategory(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushnumber(L, audio->GetCategory());

        return 1;
    }

    int Audio::IsFrontendPlay(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushboolean(L, audio->IsFrontendPlay());

        return 1;
    }

    int Audio::AddOutput(lua_State* L)
    {
        alt::IAudio* audio;
        alt::IEntity* entity = nullptr;
        uint32_t scriptID;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.IsNextType(LUA_TNUMBER))
            argReader.ReadNumber(scriptID);
        else if(argReader.IsNextType(LUA_TUSERDATA))
            argReader.ReadBaseObject(entity);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        if (entity == nullptr)
            audio->AddOutput(scriptID);
        else
            audio->AddOutput(entity);

        return 0;
    }

    int Audio::RemoveOutput(lua_State* L)
    {
        alt::IAudio* audio;
        alt::IEntity* entity = nullptr;
        uint32_t scriptID;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.IsNextType(LUA_TNUMBER))
            argReader.ReadNumber(scriptID);
        else if (argReader.IsNextType(LUA_TUSERDATA))
            argReader.ReadBaseObject(entity);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        if (entity == nullptr)
            audio->RemoveOutput(scriptID);
        else
            audio->RemoveOutput(entity);

        return 0;
    }

    int Audio::GetOutputs(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushmvalue(L, audio->GetOutputs());

        return 1;
    }

    int Audio::Play(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->Play();

        return 0;
    }

    int Audio::Pause(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->Pause();

        return 0;
    }

    int Audio::Reset(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->Reset();

        return 0;
    }

    int Audio::GetCurrentTime(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushnumber(L, audio->GetCurrentTime());

        return 1;
    }

    int Audio::GetMaxTime(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushnumber(L, audio->GetMaxTime());

        return 1;
    }

    int Audio::Seek(lua_State* L)
    {
        alt::IAudio* audio;
        double time;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);
        argReader.ReadNumber(time);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        audio->Seek(time);

        return 0;
    }

    int Audio::IsPlaying(lua_State* L)
    {
        alt::IAudio* audio;

        ArgumentReader argReader(L);
        argReader.ReadBaseObject(audio);

        if (argReader.HasAnyError())
        {
            argReader.HasAnyError();
            return 0;
        }

        lua_pushboolean(L, audio->IsPlaying());

        return 1;
    }
	
    int Audio::SetPosition(lua_State* L)
    {
		alt::IAudio* audio;
        alt::Vector3f position;
		
		ArgumentReader argReader(L);
		argReader.ReadBaseObject(audio);
		argReader.ReadVector(position);
		

        if (argReader.HasAnyError())
        {
            argReader.GetErrorMessages();
            return 0;
        }
		
        audio->SetPosition(position);
		
        return 0;
    }
	
	int Audio::GetPosition(lua_State* L)
	{
		alt::IAudio* audio;
		
		ArgumentReader argReader(L);
		argReader.ReadBaseObject(audio);
		

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}
				
        lua_pushvector3(L, audio->GetPosition());
		
		return 1;
	}

    int Audio::ResetPosition(lua_State* L)
    {
		alt::IAudio* audio;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(audio);

		if (argReader.HasAnyError())
		{
			argReader.HasAnyError();
			return 0;
		}

		audio->ResetPosition();

		return 0;
    }
}

#endif
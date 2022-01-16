#include <Main.h>

#ifdef ALT_CLIENT_API

namespace lua::Class
{
    const char* RmlDocument::ClassName = "RmlDocument";
    void RmlDocument::Init(lua_State* L)
    {
		lua_beginclass(L, RmlDocument::ClassName, RmlElement::ClassName);
		{
			lua_classmeta(L, "__tostring", tostring);

			lua_classfunction(L, "new", CreateRmlDocument);

			lua_classfunction(L, "show", Show);
			lua_classfunction(L, "hide", Hide);

			lua_classfunction(L, "update", Update);

			lua_classfunction(L, "createElement", CreateElement);
			lua_classfunction(L, "createTextNode", CreateTextNode);

			lua_classvariable(L, "title", SetTitle, GetTitle);
			lua_classvariable(L, "sourceUrl", nullptr, GetSourceUrl);
			lua_classvariable(L, "isVisible", nullptr, IsVisible);
			lua_classvariable(L, "isModal", nullptr, IsModal);

			lua_classvariable(L, "body", nullptr, GetBody);
		}
		lua_endclass(L);
    }

	int RmlDocument::tostring(lua_State* L)
	{
		lua_pushstring(L, "userdata:RmlDocument");

		return 1;
	}

    int RmlDocument::CreateRmlDocument(lua_State* L)
	{
		std::string url;

		ArgumentReader argReader(L);
		argReader.ReadString(url);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		DEBUG_INFO("CreateRmlDocument: working path: " + resourceImpl->GetWorkingPath());

		lua_pushbaseobject(L, Core->CreateDocument(url, resourceImpl->GetWorkingPath(), resourceImpl->GetResource()));

		return 1;
	}

    int RmlDocument::SetTitle(lua_State* L)
	{
		alt::IRmlDocument* document;
		std::string title;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);
		argReader.ReadString(title);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		document->SetTitle(title);

		return 0;
	}

    int RmlDocument::GetTitle(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, document->GetTitle());

		return 1;
	}

    int RmlDocument::GetSourceUrl(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, document->GetSourceUrl());

		return 1;
	}

    int RmlDocument::CreateElement(lua_State* L)
	{
		alt::IRmlDocument* document;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, document->CreateElement(name));

		return 1;
	}

    int RmlDocument::CreateTextNode(lua_State* L)
	{
		alt::IRmlDocument* document;
		std::string text;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);
		argReader.ReadString(text);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, document->CreateTextNode(text));

		return 1;
	}

    int RmlDocument::Hide(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		document->Hide();

		return 0;
	}

    int RmlDocument::Show(lua_State* L)
	{
		alt::IRmlDocument* document;
		bool isModal;
		bool focused;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);
		argReader.ReadBoolDefault(isModal, false);
		argReader.ReadBoolDefault(focused, true);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		document->Show(isModal, focused);

		return 0;
	}

    int RmlDocument::IsVisible(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, document->IsVisible());

		return 1;
	}

    int RmlDocument::IsModal(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, document->IsModal());

		return 1;
	}

    int RmlDocument::GetBody(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, document->GetBody());

		return 1;
	}

	int RmlDocument::Update(lua_State* L)
	{
		alt::IRmlDocument* document;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(document);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		document->Update();

		return 0;
	}
}

#endif
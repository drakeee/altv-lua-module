#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
	const char* WebView::ClassName = "WebView";
	void WebView::Init(lua_State* L)
	{
		DEBUG_INFO("WebView::Init");

		lua_beginclass(L, WebView::ClassName, BaseObject::ClassName);
		{
			lua_classmeta(L, "__tostring", tostring);

			lua_classfunction(L, "new", CreateWebView);
			lua_classfunction(L, "on", On);
			lua_classfunction(L, "off", Off);
			lua_classfunction(L, "emit", Trigger);
			lua_classfunction(L, "focus", Focus);
			lua_classfunction(L, "unfocus", Unfocus);
			lua_classfunction(L, "isFocused", IsFocused);
			lua_classfunction(L, "getUrl", GetUrl);
			lua_classfunction(L, "setUrl", SetUrl);
			lua_classfunction(L, "isVisible", IsVisible);
			lua_classfunction(L, "setVisible", SetVisible);
			lua_classfunction(L, "isOverlay", IsOverlay);
			lua_classfunction(L, "isReady", IsReady);

			lua_classvariable(L, "focused", nullptr, IsFocused);
			lua_classvariable(L, "url", SetUrl, GetUrl);
			lua_classvariable(L, "visible", SetVisible, IsVisible);
			lua_classvariable(L, "overlay", nullptr, IsOverlay);
			lua_classvariable(L, "ready", nullptr, IsReady);
		}
		lua_endclass(L);

		DEBUG_INFO("WebView::Init ...done");
	}

	int WebView::tostring(lua_State* L)
	{
		alt::IWebView* resource;

		ArgumentReader argReader(L);
		argReader.ReadUserData(resource);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		alt::StringView type(alt::String("userdata:WebView"));
		lua_pushstring(L, type.CStr());

		return 1;
	}

	int WebView::CreateWebView(lua_State* L)
	{
		std::string url;

		ArgumentReader argReader(L);
		argReader.ReadString(url);

		auto resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		if (resourceImpl == nullptr)
		{
			Core->LogError("Invalid resource when calling CreateWebView");
			return 0;
		}

		switch (argReader.GetArgNum())
		{
		case 2:
		{
			bool isOverlay;

			argReader.ReadBool(isOverlay);

			lua_pushwebview(L, Core->CreateWebView(resourceImpl->GetResource(), url, { 0, 0 }, { 0, 0 }, true, isOverlay).Get());

			break;
		}
		case 3:
		{
			uint32_t drawableHash;
			std::string targetTexture;

			argReader.ReadNumber(drawableHash);
			argReader.ReadString(targetTexture);

			lua_pushwebview(L, Core->CreateWebView(resourceImpl->GetResource(), url, drawableHash, targetTexture).Get());

			break;
		}
		default:
		{
			Vector3fp position;
			Vector3fp size;
			bool isVisible;
			bool isOverlay;

			argReader.ReadVectorDefault(position, Vector3fp(0, 0, 0));
			argReader.ReadVectorDefault(size, Vector3fp(0, 0, 0));
			argReader.ReadBoolDefault(isVisible, true);
			argReader.ReadBoolDefault(isOverlay, false);

			lua_pushwebview(L, Core->CreateWebView(resourceImpl->GetResource(), url, position, size, isVisible, isOverlay).Get());

			break;
		}
		}

		return 1;
	}

	int WebView::On(lua_State* L)
	{
		alt::IWebView* webView;
		std::string eventName;
		int functionIndex;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		lua_pushboolean(L, resourceEventManager->SubscribeEvent(webView, eventName, functionIndex));

		return 1;
	}

	int WebView::Off(lua_State* L)
	{
		alt::IWebView* webView;
		std::string eventName;
		int functionIndex;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionIndex);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		lua_pushboolean(L, resourceEventManager->UnsubscribeEvent(webView, eventName, functionIndex));

		return 1;
	}

	int WebView::Trigger(lua_State* L)
	{
		alt::IWebView* webView;
		std::string eventName;
		alt::MValueArgs args;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);
		argReader.ReadString(eventName);
		argReader.ReadArguments(args);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		webView->Trigger(eventName, args);

		return 0;
	}

	int WebView::Focus(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		webView->Focus();

		return 0;
	}

	int WebView::Unfocus(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		webView->Unfocus();

		return 0;
	}

	int WebView::IsFocused(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, webView->IsFocused());

		return 1;
	}

	int WebView::GetUrl(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, webView->GetUrl().CStr());

		return 1;
	}

	int WebView::SetUrl(lua_State* L)
	{
		alt::IWebView* webView;
		std::string url;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);
		argReader.ReadString(url);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		webView->SetUrl(url);

		return 0;
	}

	int WebView::IsVisible(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, webView->IsVisible());

		return 1;
	}

	int WebView::SetVisible(lua_State* L)
	{
		alt::IWebView* webView;
		bool visible;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);
		argReader.ReadBool(visible);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		webView->SetVisible(visible);

		return 1;
	}

	int WebView::IsOverlay(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, webView->IsOverlay());

		return 1;
	}


	int WebView::IsReady(lua_State* L)
	{
		alt::IWebView* webView;

		ArgumentReader argReader(L);
		argReader.ReadUserData(webView);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, webView->IsReady());

		return 1;
	}
}
#endif
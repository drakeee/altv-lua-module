#include <Main.h>

const char* CLuaWebViewDefs::ClassName = "WebView";
void CLuaWebViewDefs::Init(lua_State* L)
{
	lua_globalfunction(L, "createWebView", CreateWebView);
	lua_globalfunction(L, "emitWebView", Trigger);
	lua_globalfunction(L, "focusWebView", Focus);
	lua_globalfunction(L, "unfocusWebView", Unfocus);
	lua_globalfunction(L, "isWebViewFocused", IsFocused);
	lua_globalfunction(L, "getWebViewUrl", GetUrl);
	lua_globalfunction(L, "setWebViewUrl", SetUrl);
	lua_globalfunction(L, "isWebViewVisible", IsVisible);
	lua_globalfunction(L, "setWebViewVisible", SetVisible);
	lua_globalfunction(L, "isWebViewOverlay", IsOverlay);
	lua_globalfunction(L, "isWebViewReady", IsReady);

	lua_beginclass(L, CLuaWebViewDefs::ClassName);
	{
		lua_classfunction(L, "new", CreateWebView);
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

		lua_classvariable(L, "focused", nullptr, "isFocused");
		lua_classvariable(L, "url", "setUrl", "getUrl");
		lua_classvariable(L, "visible", "setVisible", "isVisible");
		lua_classvariable(L, "overlay", nullptr, "isOverlay");
		lua_classvariable(L, "ready", nullptr, "isReady");
	}
	lua_endclass(L);
}

int CLuaWebViewDefs::CreateWebView(lua_State *L)
{
	std::string url;

	CArgReader argReader(L);
	argReader.ReadString(url);

	auto resourceImpl = CLuaScriptRuntime::Instance().GetResourceImplFromState(L);
	if (resourceImpl == nullptr)
	{
		Core->LogError("Invalied resource when calling CreateWebView");
		return 0;
	}

	switch(argReader.GetArgNum())
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
		argReader.ReadBoolDefault(isVisible, false);
		argReader.ReadBoolDefault(isOverlay, false);

		lua_pushwebview(L, Core->CreateWebView(resourceImpl->GetResource(), url, position, size, isVisible, isOverlay).Get());

		break;
	}
	}

	return 1;
}

int CLuaWebViewDefs::Trigger(lua_State *L)
{
	alt::IWebView* webView;
	std::string eventName;
	alt::MValueArgs args;

	CArgReader argReader(L);
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

int CLuaWebViewDefs::Focus(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webView->Focus();

	return 0;
}

int CLuaWebViewDefs::Unfocus(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	webView->Unfocus();

	return 0;
}

int CLuaWebViewDefs::IsFocused(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webView->IsFocused());

	return 1;
}

int CLuaWebViewDefs::GetUrl(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushstring(L, webView->GetUrl().CStr());

	return 1;
}

int CLuaWebViewDefs::SetUrl(lua_State *L)
{
	alt::IWebView* webView;
	std::string url;

	CArgReader argReader(L);
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

int CLuaWebViewDefs::IsVisible(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webView->IsVisible());

	return 1;
}

int CLuaWebViewDefs::SetVisible(lua_State *L)
{
	alt::IWebView* webView;
	bool visible;

	CArgReader argReader(L);
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

int CLuaWebViewDefs::IsOverlay(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webView->IsOverlay());

	return 1;
}


int CLuaWebViewDefs::IsReady(lua_State *L)
{
	alt::IWebView* webView;

	CArgReader argReader(L);
	argReader.ReadUserData(webView);

	if (argReader.HasAnyError())
	{
		argReader.GetErrorMessages();
		return 0;
	}

	lua_pushboolean(L, webView->IsReady());

	return 1;
}


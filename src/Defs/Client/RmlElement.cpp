#include <Main.h>

#ifdef ALT_CLIENT_API

namespace lua::Class
{
	const char* RmlElement::ClassName = "RmlEmenet";
	void RmlElement::Init(lua_State* L)
	{
		lua_beginclass(L, RmlElement::ClassName, BaseObject::ClassName);
		{
			lua_classfunction(L, "on", On);
			lua_classfunction(L, "off", Off);

			lua_classfunction(L, "appendChild", AppendChild);
			lua_classfunction(L, "insertBefore", InsertBefore);
			lua_classfunction(L, "replaceChild", ReplaceChild);
			lua_classfunction(L, "removeChild", RemoveChild);

			lua_classfunction(L, "addClass", AddClass);
			lua_classfunction(L, "removeClass", RemoveClass);
			lua_classfunction(L, "hasClass", HasClass);
			lua_classfunction(L, "getClassList", GetClassList);

			lua_classfunction(L, "addPseudoClass", AddPseudoClass);
			lua_classfunction(L, "removePseudoClass", RemovePseudoClass);
			lua_classfunction(L, "hasPseudoClass", HasPseudoClass);
			lua_classfunction(L, "getPseudoClassList", GetPseudoClassList);

			lua_classfunction(L, "setOffset", SetOffset);

			lua_classfunction(L, "isPointWithinElement", IsPointWithinElement);

			lua_classfunction(L, "setProperty", SetProperty);
			lua_classfunction(L, "removeProperty", RemoveProperty);
			lua_classfunction(L, "hasProperty", HasProperty);
			lua_classfunction(L, "hasLocalProperty", HasLocalProperty);
			lua_classfunction(L, "getProperty", GetProperty);
			lua_classfunction(L, "getLocalProperty", GetLocalProperty);
			lua_classfunction(L, "getPropertyAbsoluteValue", GetPropertyAbsoluteValue);

			lua_classfunction(L, "setAttribute", SetAttribute);
			lua_classfunction(L, "removeAttribute", RemoveAttribute);
			lua_classfunction(L, "hasAttribute", HasAttribute);
			lua_classfunction(L, "getAttribute", GetAttribute);
			lua_classfunction(L, "getAttributes", GetAttributes);

			lua_classfunction(L, "closest", GetClosest);

			lua_classfunction(L, "getElementByID", GetElementByID);
			lua_classfunction(L, "getElementsByTagName", GetElementsByTagName);
			lua_classfunction(L, "getElementsByClassName", GetElementsByClassName);
			lua_classfunction(L, "querySelector", QuerySelector);
			lua_classfunction(L, "querySelectorAll", QuerySelectorAll);

			lua_classfunction(L, "focus", Focus);
			lua_classfunction(L, "blur", Blur);
			lua_classfunction(L, "click", Click);
			lua_classfunction(L, "scrollIntoView", ScrollIntoView);

			lua_classvariable(L, "relativeOffset", nullptr, GetRelativeOffset);
			lua_classvariable(L, "absoluteOffset", nullptr, GetAbsoluteOffset);
			lua_classvariable(L, "baseline", nullptr, GetBaseline);
			lua_classvariable(L, "zIndex", nullptr, GetZIndex);
			lua_classvariable(L, "containingBlock", nullptr, GetContainingBlock);

			lua_classvariable(L, "focusedElement", nullptr, GetFocusedElement);

			lua_classvariable(L, "tagName", nullptr, GetTagName);
			lua_classvariable(L, "id", SetID, GetID);

			lua_classvariable(L, "isOwned", nullptr, IsOwned);

			lua_classvariable(L, "absoluteLeft", nullptr, GetAbsoluteLeft);
			lua_classvariable(L, "absoluteTop", nullptr, GetAbsoluteTop);
			lua_classvariable(L, "clientLeft", nullptr, GetClientLeft);
			lua_classvariable(L, "clientTop", nullptr, GetClientTop);
			lua_classvariable(L, "clientWidth", nullptr, GetClientWidth);
			lua_classvariable(L, "clientHeight", nullptr, GetClientHeight);
			lua_classvariable(L, "offsetLeft", nullptr, GetOffsetLeft);
			lua_classvariable(L, "offsetTop", nullptr, GetOffsetTop);
			lua_classvariable(L, "offsetWidth", nullptr, GetOffsetWidth);
			lua_classvariable(L, "offsetHeight", nullptr, GetOffsetHeight);

			lua_classvariable(L, "scrollLeft", SetScrollLeft, GetScrollLeft);
			lua_classvariable(L, "scrollTop", SetScrollTop, GetScrollTop);
			lua_classvariable(L, "scrollWidth", nullptr, GetScrollWidth);
			lua_classvariable(L, "scrollHeight", nullptr, GetScrollHeight);

			lua_classvariable(L, "isVisible", nullptr, IsVisible);

			lua_classvariable(L, "parent", nullptr, GetParent);
			lua_classvariable(L, "nextSibling", nullptr, GetNextSibling);
			lua_classvariable(L, "previousSibling", nullptr, GetPreviousSibling);
			lua_classvariable(L, "firstChild", nullptr, GetFirstChild);
			lua_classvariable(L, "lastChild", nullptr, GetLastChild);

			lua_classvariable(L, "childCount", nullptr, GetChildCount);
			lua_classvariable(L, "hasChildren", nullptr, HasChildren);

			lua_classvariable(L, "innerRML", SetInnerRML, GetInnerRML);

			lua_classvariable(L, "ownerDocument", nullptr, GetOwnerDocument);

			lua_classvariable(L, "childNodes", nullptr, GetChildNodes);
		}
		lua_endclass(L);
	}


    int RmlElement::On(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string eventName;
		int functionReference;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionReference);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		lua_pushboolean(L, resourceEventManager->SubscribeEvent(rmlElement, eventName, functionReference));

		return 1;
	}

    int RmlElement::Off(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string eventName;
		int functionReference;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(eventName);
		argReader.ReadFunction(functionReference);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		LuaResourceImpl* resourceImpl = LuaScriptRuntime::Instance().GetResourceImplFromState(L);
		ResourceEventManager* resourceEventManager = resourceImpl->GetResourceEventManager();

		lua_pushboolean(L, resourceEventManager->UnsubscribeEvent(rmlElement, eventName, functionReference));

		return 1;
	}

    int RmlElement::AddClass(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->AddClass(name));

		return 1;
	}

    int RmlElement::RemoveClass(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->RemoveClass(name));

		return 1;
	}

    int RmlElement::HasClass(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->HasClass(name));

		return 1;
	}

    int RmlElement::GetClassList(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_newtable(L);
		int index = 1;
		for each (std::string className in rmlElement->GetClassList())
		{
			lua_pushnumber(L, index);
			lua_pushstring(L, className);
			lua_rawset(L, -3);

			index++;
		}

		return 1;
	}

    int RmlElement::AddPseudoClass(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->AddPseudoClass(name));

		return 1;
	}

    int RmlElement::RemovePseudoClass(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->RemovePseudoClass(name));

		return 1;
	}

    int RmlElement::HasPseudoClass(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->HasPseudoClass(name));

		return 1;
	}

    int RmlElement::GetPseudoClassList(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_newtable(L);
		int index = 1;
		for each (std::string className in rmlElement->GetPseudoClassList())
		{
			lua_pushnumber(L, index);
			lua_pushstring(L, className);
			lua_rawset(L, -3);

			index++;
		}

		return 1;
	}

    int RmlElement::SetOffset(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		alt::IRmlElement* offsetParent;
		alt::Vector2f offset;
		bool fixed;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadBaseObject(offsetParent);
		argReader.ReadVector(offset);
		argReader.ReadBoolDefault(fixed, false);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->SetOffset(offsetParent, offset, fixed);

		return 0;
	}

    int RmlElement::GetRelativeOffset(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector2(L, rmlElement->GetRelativeOffset());

		return 1;
	}

    int RmlElement::GetAbsoluteOffset(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector2(L, rmlElement->GetAbsoluteOffset());

		return 1;
	}

    int RmlElement::GetBaseline(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetBaseline());

		return 1;
	}

    int RmlElement::GetZIndex(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetZIndex());

		return 1;
	}

    int RmlElement::IsPointWithinElement(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		alt::Vector2f point;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadVector(point);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->IsPointWithinElement(point));

		return 1;
	}

    int RmlElement::SetProperty(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;
		std::string value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);
		argReader.ReadString(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->SetProperty(name, value));

		return 1;
	}

    int RmlElement::RemoveProperty(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->RemoveProperty(name));

		return 1;
	}

    // Checks property for local element and all inherited from ancestors
    int RmlElement::HasProperty(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->HasProperty(name));

		return 1;
	}

    // Only check property for local element
    int RmlElement::HasLocalProperty(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->HasLocalProperty(name));

		return 1;
	}

    int RmlElement::GetProperty(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, rmlElement->GetProperty(name));

		return 1;
	}

    int RmlElement::GetLocalProperty(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, rmlElement->GetLocalProperty(name));

		return 1;
	}

    // Returns the relative unit (e.g. 'percent' or 'angle') as absolute value ('px' or 'rad')
    int RmlElement::GetPropertyAbsoluteValue(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetPropertyAbsoluteValue(name));

		return 1;
	}

    int RmlElement::GetContainingBlock(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushvector2(L, rmlElement->GetContainingBlock());

		return 1;
	}

    int RmlElement::GetFocusedElement(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetFocusedElement());

		return 1;
	}

    int RmlElement::GetTagName(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, rmlElement->GetTagName());

		return 1;
	}

    int RmlElement::GetID(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, rmlElement->GetID());

		return 1;
	}

    int RmlElement::SetID(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string id;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(id);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->SetID(id);

		return 0;
	}

    int RmlElement::IsOwned(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->IsOwned());

		return 1;
	}

    int RmlElement::SetAttribute(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;
		std::string value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);
		argReader.ReadString(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->SetAttribute(name, value);

		return 0;
	}

    int RmlElement::RemoveAttribute(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->RemoveAttribute(name));

		return 1;
	}

    int RmlElement::HasAttribute(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->HasAttribute(name));

		return 1;
	}

    int RmlElement::GetAttribute(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string name;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(name);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, rmlElement->GetAttribute(name));

		return 1;
	}

    int RmlElement::GetAttributes(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_newtable(L);
		int index = 1;
		for (auto &map : rmlElement->GetAttributes())
		{
			lua_pushstring(L, map.first);
			lua_pushstring(L, map.second);
			lua_rawset(L, -3);

			index++;
		}

		return 1;
	}

    int RmlElement::GetAbsoluteLeft(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetAbsoluteLeft());

		return 1;
	}

    int RmlElement::GetAbsoluteTop(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetAbsoluteTop());

		return 1;
	}

    int RmlElement::GetClientLeft(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetClientLeft());

		return 1;
	}

    int RmlElement::GetClientTop(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetClientTop());

		return 1;
	}

    int RmlElement::GetClientWidth(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetClientWidth());

		return 1;
	}

    int RmlElement::GetClientHeight(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetClientHeight());

		return 1;
	}

    int RmlElement::GetOffsetParent(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetOffsetParent());

		return 1;
	}

    int RmlElement::GetOffsetLeft(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetOffsetLeft());

		return 1;
	}

    int RmlElement::GetOffsetTop(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetOffsetTop());

		return 1;
	}

    int RmlElement::GetOffsetWidth(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetOffsetWidth());

		return 1;
	}

    int RmlElement::GetOffsetHeight(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetOffsetHeight());

		return 1;
	}

    int RmlElement::GetScrollLeft(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetScrollLeft());

		return 1;
	}

    int RmlElement::SetScrollLeft(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		float value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadNumber(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->SetScrollLeft(value);

		return 0;
	}

    int RmlElement::GetScrollTop(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetScrollTop());

		return 1;
	}

    int RmlElement::SetScrollTop(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		float value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadNumber(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->SetScrollTop(value);

		return 0;
	}

    int RmlElement::GetScrollWidth(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetScrollWidth());

		return 1;
	}

    int RmlElement::GetScrollHeight(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetScrollHeight());

		return 1;
	}

    int RmlElement::IsVisible(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->IsVisible());

		return 1;
	}

    int RmlElement::GetParent(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetParent());

		return 1;
	}

    int RmlElement::GetClosest(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string selectors;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(selectors);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetClosest(selectors));

		return 1;
	}

    int RmlElement::GetNextSibling(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetNextSibling());

		return 1;
	}

    int RmlElement::GetPreviousSibling(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetPreviousSibling());

		return 1;
	}

    int RmlElement::GetFirstChild(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetFirstChild());

		return 1;
	}

    int RmlElement::GetLastChild(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetLastChild());

		return 1;
	}

    int RmlElement::GetChild(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		int index;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadNumber(index);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetChild(index));

		return 1;
	}

    int RmlElement::GetChildCount(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rmlElement->GetChildCount());

		return 1;
	}

    int RmlElement::AppendChild(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		alt::IRmlElement* element;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadBaseObject(element);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->AppendChild(element);

		return 0;
	}

    int RmlElement::InsertBefore(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		alt::IRmlElement* element;
		alt::IRmlElement* adjacentElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadBaseObject(element);
		argReader.ReadBaseObject(adjacentElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->InsertBefore(element, adjacentElement);

		return 0;
	}

    int RmlElement::ReplaceChild(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		alt::IRmlElement* newElement;
		alt::IRmlElement* oldElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadBaseObject(newElement);
		argReader.ReadBaseObject(oldElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->ReplaceChild(newElement, oldElement);

		return 0;
	}

    int RmlElement::RemoveChild(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		alt::IRmlElement* element;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadBaseObject(element);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->RemoveChild(element);

		return 0;
	}

    int RmlElement::HasChildren(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->HasChildren());

		return 1;
	}

    int RmlElement::GetInnerRML(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushstring(L, rmlElement->GetInnerRML());

		return 1;
	}

    int RmlElement::SetInnerRML(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string value;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(value);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->SetInnerRML(value);

		return 0;
	}

    int RmlElement::Focus(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushboolean(L, rmlElement->Focus());

		return 1;
	}

    int RmlElement::Blur(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->Blur();

		return 0;
	}

    int RmlElement::Click(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->Click();

		return 0;
	}

    int RmlElement::ScrollIntoView(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		bool alignWithTop;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadBoolDefault(alignWithTop, true);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rmlElement->ScrollIntoView(alignWithTop);

		return 0;
	}

    int RmlElement::GetElementByID(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string id;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(id);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetElementByID(id));

		return 1;
	}

    int RmlElement::GetElementsByTagName(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string tag;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(tag);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		int index = 1;
		for (alt::Ref<alt::IRmlElement> element : rmlElement->GetElementsByTagName(tag))
		{
			lua_pushnumber(L, index);
			lua_pushbaseobject(L, element);
			lua_rawset(L, -3);
			index++;
		}

		return 1;
	}

    int RmlElement::GetElementsByClassName(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string tag;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(tag);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		int index = 1;
		for (alt::Ref<alt::IRmlElement> element : rmlElement->GetElementsByClassName(tag))
		{
			lua_pushnumber(L, index);
			lua_pushbaseobject(L, element);
			lua_rawset(L, -3);
			index++;
		}

		return 1;
	}

    int RmlElement::QuerySelector(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string selector;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(selector);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->QuerySelector(selector));

		return 1;
	}

    int RmlElement::QuerySelectorAll(lua_State* L)
	{
		alt::IRmlElement* rmlElement;
		std::string selector;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);
		argReader.ReadString(selector);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		int index = 1;
		for (alt::Ref<alt::IRmlElement> element : rmlElement->QuerySelectorAll(selector))
		{
			lua_pushnumber(L, index);
			lua_pushbaseobject(L, element);
			lua_rawset(L, -3);
			index++;
		}

		return 1;
	}

	int RmlElement::GetOwnerDocument(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushbaseobject(L, rmlElement->GetOwnerDocument());

		return 1;
	}

	int RmlElement::GetChildNodes(lua_State* L)
	{
		alt::IRmlElement* rmlElement;

		ArgumentReader argReader(L);
		argReader.ReadBaseObject(rmlElement);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		int childCount = rmlElement->GetChildCount();
		for(int i = 0; i < childCount; i++)
		{
			lua_pushnumber(L, i + 1);
			lua_pushbaseobject(L, rmlElement->GetChild(i));
			lua_rawset(L, -3);
		}

		return 1;
	}
}

#endif
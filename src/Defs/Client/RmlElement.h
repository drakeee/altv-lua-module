#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API

namespace lua::Class
{
    class RmlElement
    {
    public:
        static const char* ClassName;
        static void Init(lua_State* L);

    private:
        static int tostring(lua_State* L);

        static int CreateRmlElement(lua_State* L);
        static int On(lua_State* L);
        static int Off(lua_State* L);

        static int AddClass(lua_State* L);
        static int RemoveClass(lua_State* L);
        static int HasClass(lua_State* L);
        static int GetClassList(lua_State* L);

        static int AddPseudoClass(lua_State* L);
        static int RemovePseudoClass(lua_State* L);
        static int HasPseudoClass(lua_State* L);
        static int GetPseudoClassList(lua_State* L);

        static int SetOffset(lua_State* L);
        static int GetRelativeOffset(lua_State* L);
        static int GetAbsoluteOffset(lua_State* L);
        static int GetBaseline(lua_State* L);
        static int GetZIndex(lua_State* L);

        static int IsPointWithinElement(lua_State* L);

        static int SetProperty(lua_State* L);
        static int RemoveProperty(lua_State* L);
        // Checks property for local element and all inherited from ancestors
        static int HasProperty(lua_State* L);
        // Only check property for local element
        static int HasLocalProperty(lua_State* L);
        static int GetProperty(lua_State* L);
        static int GetLocalProperty(lua_State* L);
        // Returns the relative unit (e.g. 'percent' or 'angle') as absolute value ('px' or 'rad')
        static int GetPropertyAbsoluteValue(lua_State* L);

        static int GetContainingBlock(lua_State* L);

        static int GetFocusedElement(lua_State* L);

        static int GetTagName(lua_State* L);
        static int GetID(lua_State* L);
        static int SetID(lua_State* L);

        static int IsOwned(lua_State* L);

        static int SetAttribute(lua_State* L);
        static int RemoveAttribute(lua_State* L);
        static int HasAttribute(lua_State* L);
        static int GetAttribute(lua_State* L);
        static int GetAttributes(lua_State* L);

        static int GetAbsoluteLeft(lua_State* L);
        static int GetAbsoluteTop(lua_State* L);
        static int GetClientLeft(lua_State* L);
        static int GetClientTop(lua_State* L);
        static int GetClientWidth(lua_State* L);
        static int GetClientHeight(lua_State* L);
        static int GetOffsetParent(lua_State* L);
        static int GetOffsetLeft(lua_State* L);
        static int GetOffsetTop(lua_State* L);
        static int GetOffsetWidth(lua_State* L);
        static int GetOffsetHeight(lua_State* L);

        static int GetScrollLeft(lua_State* L);
        static int SetScrollLeft(lua_State* L);
        static int GetScrollTop(lua_State* L);
        static int SetScrollTop(lua_State* L);
        static int GetScrollWidth(lua_State* L);
        static int GetScrollHeight(lua_State* L);

        static int IsVisible(lua_State* L);

        static int GetParent(lua_State* L);
        static int GetClosest(lua_State* L);
        static int GetNextSibling(lua_State* L);
        static int GetPreviousSibling(lua_State* L);
        static int GetFirstChild(lua_State* L);
        static int GetLastChild(lua_State* L);
        static int GetChild(lua_State* L);
        static int GetChildCount(lua_State* L);
        static int AppendChild(lua_State* L);
        static int InsertBefore(lua_State* L);
        static int ReplaceChild(lua_State* L);
        static int RemoveChild(lua_State* L);
        static int HasChildren(lua_State* L);

        static int GetInnerRML(lua_State* L);
        static int SetInnerRML(lua_State* L);

        static int Focus(lua_State* L);
        static int Blur(lua_State* L);
        static int Click(lua_State* L);
        static int ScrollIntoView(lua_State* L);

        static int GetElementByID(lua_State* L);
        static int GetElementsByTagName(lua_State* L);
        static int GetElementsByClassName(lua_State* L);
        static int QuerySelector(lua_State* L);
        static int QuerySelectorAll(lua_State* L);

        static int GetOwnerDocument(lua_State* L);

        static int GetChildNodes(lua_State* L);
    };
}

#endif
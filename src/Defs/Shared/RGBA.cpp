#include <Main.h>

namespace lua::Class
{
	const char* RGBA::ClassName = "RGBA";
	void RGBA::Init(lua_State* L)
	{
		DEBUG_INFO("RGBA::Init");

		lua_beginclass(L, ClassName);
		{
			lua_classfunction(L, "new", CreateRGBA);
			lua_classfunction(L, "setColor", SetColor);
			lua_classfunction(L, "getColor", GetColor);
			lua_classfunction(L, "setR", SetR);
			lua_classfunction(L, "getR", GetR);
			lua_classfunction(L, "setG", SetG);
			lua_classfunction(L, "getG", GetG);
			lua_classfunction(L, "setB", SetB);
			lua_classfunction(L, "getB", GetB);
			lua_classfunction(L, "setA", SetA);
			lua_classfunction(L, "getA", GetA);

			lua_classvariable(L, "color", "setColor", "getColor");
			lua_classvariable(L, "r", "setR", "getR");
			lua_classvariable(L, "g", "setG", "getG");
			lua_classvariable(L, "b", "setB", "getB");
			lua_classvariable(L, "a", "setA", "getA");
		}
		lua_endclass(L);

		DEBUG_INFO("RGBA::Init ...done");
	}

	int RGBA::SetColor(lua_State* L)
	{
		alt::RGBA* rgba;
		alt::RGBA* copy;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);
		argReader.ReadUserData(copy);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rgba->r = copy->r;
		rgba->g = copy->g;
		rgba->b = copy->b;
		rgba->a = copy->a;

		return 0;
	}

	int RGBA::GetColor(lua_State* L)
	{
		alt::RGBA* rgba;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rgba->toInt());

		return 1;
	}

	int RGBA::CreateRGBA(lua_State* L)
	{
		int r, g, b, a;

		ArgumentReader argReader(L);
		argReader.ReadNumber(r);
		argReader.ReadNumber(g);
		argReader.ReadNumber(b);
		argReader.ReadNumber(a);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushrgba(L, alt::RGBA(r, g, b, a));

		return 1;
	}

	int RGBA::SetR(lua_State* L)
	{
		alt::RGBA* rgba;
		int r;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);
		argReader.ReadNumber(r);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rgba->r = r;

		return 0;
	}

	int RGBA::GetR(lua_State* L)
	{
		alt::RGBA* rgba;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rgba->r);

		return 1;
	}

	int RGBA::SetG(lua_State* L)
	{
		alt::RGBA* rgba;
		int g;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);
		argReader.ReadNumber(g);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rgba->g = g;

		return 0;
	}

	int RGBA::GetG(lua_State* L)
	{
		alt::RGBA* rgba;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rgba->g);

		return 1;
	}

	int RGBA::SetB(lua_State* L)
	{
		alt::RGBA* rgba;
		int b;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);
		argReader.ReadNumber(b);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rgba->b = b;

		return 0;
	}

	int RGBA::GetB(lua_State* L)
	{
		alt::RGBA* rgba;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rgba->b);

		return 1;
	}

	int RGBA::SetA(lua_State* L)
	{
		alt::RGBA* rgba;
		int a;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);
		argReader.ReadNumber(a);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		rgba->a = a;

		return 0;
	}

	int RGBA::GetA(lua_State* L)
	{
		alt::RGBA* rgba;

		ArgumentReader argReader(L);
		argReader.ReadUserData(rgba);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		lua_pushnumber(L, rgba->a);

		return 1;
	}
}
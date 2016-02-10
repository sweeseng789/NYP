#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdarg.h>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CLua
{
public:
	CLua(const std::string fileName);
	~CLua();

	//============= GET LUA DATA VARIABLE =============//
	template<typename dataType>
	dataType lua_get()
	{
		return 0;
	}

	template<typename dataType>
	dataType getData(const std::string variableName)
	{
		if (!L)
		{
			std::cout << "Script not loaded" << std::endl;
			return 0;
		}

		lua_getglobal(L, variableName.c_str());
		dataType result = lua_get<dataType>();
		return result;
	}

	//============= GET LUA VECTOR DATA VARIABLE =============//
	template<typename dataType>
	std::vector<dataType> lua_getVector()
	{
		return std::vector<dataType>();
	}

	template<typename dataType>
	std::vector<dataType> getVector(const std::string variableName)
	{
		lua_getglobal(L, variableName.c_str());

		if (lua_isnil(L, -1))
		{
			std::cout << variableName << " is not valid" << std::endl;
			return std::vector<dataType>();
		}

		std::vector<dataType> result = lua_getVector<dataType>();
		return result;
	}

	//============= GET LUA FUNCTION =============//
	//template<typename dataType>
	int add(int argCount, ...)
	{
		lua_State* temp = lua_open();
		luaL_openlibs(temp);

		if (luaL_loadfile(temp, "Lua/function.Lua") || lua_pcall(temp, 0, 0, 0))
		{
			std::cout << "Unable to load function.lua" << std::endl;
			return 0;
		}

		lua_getglobal(temp, "add");

		va_list args;
		va_start(args, argCount);
		for (int a = 0; a < argCount; ++a)
		{
			lua_pushnumber(temp, va_arg(args, int));
		}
		va_end(args);

		lua_pcall(temp, argCount, 1, 0);

		int result = (int)lua_tonumber(temp, -1);
		lua_pop(temp, 1);
		lua_close(temp);

		return result;
	}

	//Setter
	void clean()
	{
		int n = lua_gettop(L);
		lua_pop(L, n);
	}

private:
	lua_State* L;
};

//============= INT =============//
//Data Variable
template<>
inline int CLua::lua_get<int>()
{
	return (int)lua_tonumber(L, -1);
}

//Vector Variable
template<>
inline std::vector<int> CLua::lua_getVector()
{
	std::vector<int> result;

	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		int newData = (int)lua_tonumber(L, -1);
		result.push_back(newData);
		lua_pop(L, 1);
	}

	clean();
	return result;
}

//============= BOOL =============//
//Data Variable
template<>
inline bool CLua::lua_get<bool>()
{
	return static_cast<bool>(lua_toboolean(L, -1));
}

//Vector Variable
template<>
inline std::vector<bool> CLua::lua_getVector()
{
	std::vector<bool> result;

	lua_pushnil(L);
	while (lua_next(L, -2))
	{
		bool newData = (bool)lua_toboolean(L, -1);
		result.push_back(newData);
		lua_pop(L, 1);
	}
	clean();

	return result;
}

//============= FLOAT =============//
template<>
inline float CLua::lua_get<float>()
{
	return (float)lua_tonumber(L, -1);
}

//============= STRING =============//
template<>
inline std::string CLua::lua_get<std::string>()
{
	std::string result;
	if (lua_isstring(L, -1))
	{
		result = std::string(lua_tostring(L, -1));
	}
	return result;
}
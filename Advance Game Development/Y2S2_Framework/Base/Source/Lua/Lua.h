#pragma once

#include <string>
#include <vector>
#include <iostream>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CLua
{
public:
	CLua(const std::string fileLoc);
	~CLua();

	//============= GETTER =============//

	//Get Lua Data Type
	template<typename dataType>
	dataType lua_get(const std::string variableName)
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
		dataType result = lua_get<dataType>(variableName);
		return result;
	}


	//Get Lua Vector Data Type
	template<typename dataType>
	std::vector<dataType> lua_getVector(const std::string variableName)
	{
		return std::vector<dataType>();
	}

	template<typename dataType>
	std::vector<dataType> getVector(const std::string variableName)
	{
		std::vector<dataType> result;
		result = lua_getVector<dataType>(variableName);
		return result;
	}

	/*std::vector<int> getIntVector(const std::string variableName)
	{
		std::vector<int> result;
		lua_getglobal(L, variableName.c_str());

		if (lua_isnil(L, -1))
		{
			std::cout << variableName << " is not valid" << std::endl;
			return result;
		}

		lua_pushnil(L);
		while (lua_next(L, -2))
		{
			int numToPushBack = (int)lua_tonumber(L, -1);
			result.push_back(numToPushBack);
			lua_pop(L, 1);
		}

		clearTop();

		return result;
	}*/

	//Setter
	void clean()
	{
		int n = lua_gettop(L);
		lua_pop(L, n);
	}
private:
	lua_State* L;
};

//Int
template<>
inline int CLua::lua_get<int>(const std::string variableName)
{
	if (!lua_isnumber(L, -1))
		std::cout << variableName << " is not a number" << std::endl;
	return (int)lua_tonumber(L, -1);
}

template<>
inline std::vector<int> CLua::lua_getVector(const std::string variableName)
{
	std::vector<int> result;

	lua_getglobal(L, variableName.c_str());

	if (lua_isnil(L, -1))
	{
		std::cout << variableName << " is not a valid" << std::endl;
		return result;
	}

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

//Bool
template<>
inline bool CLua::lua_get<bool>(const std::string variableName)
{
	return (bool)lua_toboolean(L, -1);
}

//Float
template<>
inline float CLua::lua_get<float>(const std::string variableName)
{
	if (!lua_isnumber(L, -1))
		std::cout << variableName << " is not a number" << std::endl;
	return (float)lua_tonumber(L, -1);
}

//String
template<>
inline std::string CLua::lua_get<std::string>(const std::string variableName)
{
	std::string result;
	if (lua_isstring(L, -1))
	{
		result = std::string(lua_tostring(L, -1));
	}
	return result;
}
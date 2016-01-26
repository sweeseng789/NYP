extern "C"
{
#include "Lua\lua.h"
#include "Lua\lualib.h"
#include "Lua\lauxlib.h"
}

#include <iostream>

int main(int argc, char* argv[])
{
	int s = 0;
	lua_State * L = lua_open();

	//Load the Libs
	luaL_openlibs(L);
	/*if (luaL_loadfile(L, "my.Lua") || lua_pcall(L, 0, 0, 0))
	{
		std::cout << "Error" << std::endl;
	}

	lua_getglobal(L, "SCREENWIDTH");
	if (!lua_isnumber(L, -1))
	{
		std::cout << "Screenwidrth should be a number" << std::endl;

		return -1;
	}*/

	////DO Stuff with lua
	//char* strLuaInput = "a = 1 + 1;\nprint(a);\n";
	//luaL_dostring(L, strLuaInput);

	/*if (luaL_dofile(L, "Lua/Text/my.lua"))
	{
		std::cout << "Siann" << std::endl;
	}*/
	//lua_getglobal(L, "SCREENWDITH");

	luaL_openlibs(L);
	if (luaL_loadfile(L, "Lua/Text/my.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L, -1));
		return -1;
	}
	//lua_getglobal(L, "SCREENWIDTH");
	///*if (!lua_isnumber(L, -1)) {
	//	printf("`SCREENWIDTH' should be a number\n");
	//	return -1;
	//}*/
	//int SCREENWIDTH = (int)lua_tonumber(L, -1);

	//std::cout << SCREENWIDTH << std::endl;
	//std::cout << (int)lua_tonumber(L, -2);
	lua_getglobal(L, "SCREENWIDTH");
	std::cout << (int)lua_tonumber(L, 1) << std::endl;

	lua_getglobal(L, "SCREENHEIGHT");
	std::cout << (int)lua_tonumber(L, 2) << std::endl;

	lua_getglobal(L, "COLORDEPTH");
	std::cout << (int)lua_tonumber(L, 3) << std::endl;

	//Run Lua Script
	/*luaL_dofile(L, "my.Lua");
	char* strLuaInput = "a = 1 + 1;\n print(a); \n";
	luaL_dostring(L, strLuaInput);*/

	std::cout << "So Done With Lua in C++" << std::endl;
	lua_close(L);

	system("pause");
	return 0;
}
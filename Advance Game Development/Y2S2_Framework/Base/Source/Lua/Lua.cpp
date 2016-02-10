#include "Lua.h"



CLua::CLua(const std::string fileName)
{
	L = lua_open();
	luaL_openlibs(L);

	std::string fileDir = "Lua/";
	fileDir += fileName + ".Lua";

	if (luaL_loadfile(L, fileDir.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		std::cout << fileDir << " is not a valid link" << std::endl;
		return;
	}
	else
	{
		std::cout << fileDir << " is loaded successfully" << std::endl;
	}
}


CLua::~CLua()
{
	if (L != NULL)
	{
		lua_close(L);
	}
}
#pragma once
#include "ModDLL.h"
#include "LuaDebugInformation.h"
#include "LuaDebugger.h"

extern "C" {
#include "Lua535/include/lua.h"
#include "Lua535/include/lauxlib.h"
#include "Lua535/include/lualib.h"
}


std::string returnLowerCaseString(std::string str) {
	std::string buffer = str;
	std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
	return buffer;
}


#ifdef _WIN32
#pragma comment(lib, "../Lua535/liblua53.a")
#endif

namespace ModDLLLua {

	void enterLua(changes change) {
		system("cls");
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		std::string userInput;
		bool runLua = true;
		std::cout << "To exit ModDLL Lua type \"exit\"" << std::endl;
		while (runLua) {
			std::cout << "[LUA]> ";
			std::getline(std::cin, userInput);
			if (returnLowerCaseString(userInput) == "exit") {
				runLua = false;
				break;
			}
			int r = luaL_dostring(L, userInput.c_str());
			if (r == LUA_OK) {

			}
			else
			{
				std::string error = luaL_checkstring(L, -1);
				std::cout << "Lua Error: " << error << std::endl;
			}
		}
		lua_close(L);

	}

	void luaScript(changes change, std::vector<std::string> bufferVector) {
		if (bufferVector[1] != "" && std::ifstream(bufferVector[1]).good()) {

		}
		else {
			std::cout << "Incorrect arguments" << std::endl;
			return;
		}
		system("cls");
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		int successful = luaL_dofile(L, bufferVector[1].c_str());
		if (successful == LUA_OK) {
			std::cout << "Successfully Ran Lua[\"" << bufferVector[1] << "\"]" << std::endl;
		}
		else
		{
			std::string error = luaL_checkstring(L, -1);
			std::cout << "Lua Error: " << error << std::endl;
		}
	}


	void startDebug(changes change, std::vector<std::string> bufferVector) {
		LuaDebugInformation myInfo(bufferVector[1]);
		std::cout << "L: " << myInfo.lineNumber() << std::endl;
	}

}
#pragma once
#include "ModDLL.h"

class luaTokenParser {

};

class LuaDebugInformation
{
	public:
		LuaDebugInformation(std::string fName);
		~LuaDebugInformation();
	private:
		std::ifstream file;
		std::string fileName;
		std::vector<luaTokenParser> lineInformation;
		int numberOfLines;
};


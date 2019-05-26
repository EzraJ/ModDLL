#pragma once
#ifndef LUADEBUGINFORMATION_INCLUDE
#define LUADEBUGINFORMATION_INCLUDE

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class luaTokenParser {

};

class LuaDebugInformation
{
	public:
		LuaDebugInformation(std::string fName);
		~LuaDebugInformation();
		int lineNumber();
		std::string FNAME();
	private:
		std::ifstream file;
		std::string fileName;
		std::vector<luaTokenParser> lineInformation;
		int numberOfLines = 0;
};

#endif
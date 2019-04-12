#include "LuaDebugInformation.h"



LuaDebugInformation::LuaDebugInformation(std::string fName){
	file.open(fName);
	if (file.good()) {
		fileName = fName;
		std::cout << "[LUADEBUG]Opened file:" << fName << std::endl;
	}
	else {
		std::cout << "[LUADEBUG]Failed to open file:" << fName << std::endl;
		delete this;
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string fileContent = buffer.str();

}


LuaDebugInformation::~LuaDebugInformation(){

}

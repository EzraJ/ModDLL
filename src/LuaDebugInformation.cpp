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
	std::string readFileBuffer;
	std::cout << "Start reading" << std::endl;
	file.close();
	file.open(fName);
	while (std::getline(file, readFileBuffer)) {
		numberOfLines++;
		std::cout << "Read line: " << readFileBuffer << std::endl;
	}

}

std::string LuaDebugInformation::FNAME() {
	return LuaDebugInformation::fileName;
}

int LuaDebugInformation::lineNumber() {
	return LuaDebugInformation::numberOfLines;
}

LuaDebugInformation::~LuaDebugInformation(){
	file.close();
}

// ModDLL.cpp : Defines the exported functions for the DLL application.
// For Programmer defined functions, its recommended you only use changes as your arguments,
// as it is the only arguments you really need.
//

#include "stdafx.h"
#include "ModDLLLua.h"
#include "ModDLL.h"
#include "tokenParser.h"


// Programmer Defined Variables(constant)


// Programmer Defined Functions
std::string getPath() {
	char path[256];
	_getcwd(path, sizeof(path));
	return std::string(path);
}



// Usage Functions
bool compareAlpha(std::string a, std::string b) {
	std::transform(a.begin(), a.end(), a.begin(), tolower);
	std::transform(b.begin(), b.end(), b.begin(), ::tolower);
	return a < b;
}

std::string returnLowerCase(std::string str) {
	std::string buffer = str;
	std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
	return buffer;
}

std::vector<std::string> parse(std::string inp) {
	std::istringstream ss(inp);
	using StrIt = std::istream_iterator<std::string>;
	std::vector<std::string> container(StrIt(ss), StrIt{});
	return container;
}

std::string unparse(std::vector<std::string> inp) {
	std::string toReturn;
	for (std::vector<std::string>::iterator it = inp.begin(); it != inp.end(); it++) {
		toReturn += *it + " ";
	}
	return toReturn;
}



void clear() {
	system("cls");
}

bool runProgram(changes change, std::vector<std::string> bufferVector) {

	std::ifstream fileBuffer(bufferVector[0]);
	if (fileBuffer.good() && bufferVector.size() == 1) {
		std::cout << "Successfully ran[\"" << bufferVector[0] << "\"]" << std::endl;
		system(std::string("start " + bufferVector[0]).c_str());
		return true;
	}
	else {
		return false;
	}

}

void dirAdv(changes change, std::vector<std::string> bufferVector) {
	std::string oldDir = change.dataChange.stringChange;
	std::string buffer;
	bool boolBuf = false;
	buffer = bufferVector[1];
	if (_chdir(buffer.c_str()) == -1) {
		boolBuf = false;
		if (_chdir(std::string(change.dataChange.stringChange + "\\" + buffer).c_str()) == -1) {
			std::cout << "Invalid directory." << std::endl;
			_chdir(oldDir.c_str());
			change.dataChange.stringChange = oldDir;
			return;
		}
		else {
			boolBuf = true;
		}
	}
	if (boolBuf) {
		change.dataChange.stringChange = change.dataChange.stringChange + " " + buffer;
	}
	else {
		change.dataChange.stringChange = getPath();
	}
}

void printVersion() {
	std::cout << 'v'  << VERSION << std::endl;
}

void make(changes change, std::vector<std::string> bufferVector) {
	std::ofstream file(bufferVector[1]);
	file << bufferVector[1];
	file.close();
}

void cat(changes change, std::vector<std::string> bufferVector){
	std::string fname = bufferVector[1];
	std::ifstream file(fname);
	if (file.is_open()) {
		std::cout << file.rdbuf() << std::endl;
	}
	file.close();
}

void list(changes change) {
	std::string path = change.dataChange.stringChange;
	for (const auto& entry : std::experimental::filesystem::v1::directory_iterator(path)) {
		std::string buffer = entry.path().u8string();
		std::string::size_type test = buffer.find(getPath() + "\\");
		if (test != std::string::npos) {
			buffer.erase(test, std::string(getPath() + "\\").length());
		}
		std::cout << buffer << std::endl;
	}
	std::cout << std::endl;
}

void help();

void man(changes change) {
	std::ifstream manFile("man.txt");
	std::string fileBuffer = std::string(std::istreambuf_iterator<char>(manFile), std::istreambuf_iterator<char>());
	std::cout << fileBuffer;
}

void echoFunction(changes change, std::vector<std::string> bufferVector) {
	for (std::vector<std::string>::iterator it = bufferVector.begin(); it != bufferVector.end(); it++) {
		if (*it != "echo") {
			std::cout << *it << " ";
		}
	}
	std::cout << std::endl;
}


void alias(changes change, std::vector<std::string> bufferVector);
void variableParse(changes change, std::vector<std::string> &bufferVector);



// Variables

std::unordered_map<std::string, std::string> variableSpace = { {"home", "H:/Desktop"} };
std::vector<std::function<void(changes, std::vector<std::string>&)>> strParse = { variableParse };
std::unordered_map<std::string, std::function<void(changes, std::vector<std::string>)>> special = { {"LuaScript", ModDLLLua::luaScript}, {"cd", dirAdv}, {"touch", make}, {"cat", cat}, {"echo", echoFunction}, {"alias", alias}, {"LuaDebug", ModDLLLua::debugInformation} };
std::unordered_map<std::string, std::function<void()>> funcs = { {"debug", debug}, {"clear", clear}, {"VERSION", printVersion}, {"programs", help} };
std::unordered_map<std::string, std::function<void(changes)>> funcsChanges = { {"exit", modExit}, {"ls", list}, {"man", man}, {"lua", ModDLLLua::enterLua} };

bool debugMode = false;




// Default Functions

void alias(changes change, std::vector<std::string> bufferVector) {
	tokenParser token(unparse(bufferVector), "alias");
	if (debugMode) {
		std::cout << "\narg0: " << token.getString("arg0") << std::endl << "arg1: " << token.getString("arg1") << std::endl << "arg2: " << token.getString("arg2") << std::endl;
	}
	if (token.getType("arg1") == parserType::setter) {
		std::string variableMake;
		for (int i = 2; i < token.getNumberOfArgs(); i++) {
			if (i == 2) {
				variableMake += std::string(token.getString("arg" + std::to_string(i)));
			}
			else {
				variableMake += std::string(" " + token.getString("arg" + std::to_string(i)));
			}
			
			if (debugMode) {
				std::cout << "var[" << i << "]: " << token.getString(std::string("arg" + std::to_string(i)));
				std::cin.get();
			}
		}
		variableSpace[token.getString("arg0")] = variableMake;
	}
	std::cout << std::endl;
}


void variableParse(changes change, std::vector<std::string> &bufferVector) {
	int i = 0;
	for (std::vector<std::string>::iterator it = bufferVector.begin(); it != bufferVector.end(); it++) {
		std::string strBuffer = *it;
		if (strBuffer[0] == '$'  && variableSpace.find(strBuffer.substr(1, strBuffer.length())) != variableSpace.end()) {
			strBuffer = variableSpace[strBuffer.substr(1, strBuffer.length())];
			bufferVector[i] = strBuffer;
			if (debugMode) {
				std::cout << "DEBUG(buffer, calc): " << strBuffer << ", " << bufferVector[i] << std::endl;
			}
		}
		i++;
	}
	for (std::vector<std::string>::iterator it = bufferVector.begin(); it != bufferVector.end(); it++) {
		if (debugMode) {
			std::cout << "Contents of buffer: " << *it << std::endl;
		}
	}
}

void help() {
	std::vector<std::string> funcHelp;
	for (std::unordered_map<std::string, std::function<void()>>::iterator it = funcs.begin(); it != funcs.end(); it++) {
		funcHelp.push_back(it->first);

	}
	for (std::unordered_map<std::string, std::function<void(changes)>>::iterator it = funcsChanges.begin(); it != funcsChanges.end(); it++) {
		funcHelp.push_back(it->first);
	}
	for (std::unordered_map<std::string, std::function<void(changes, std::vector<std::string>)>>::iterator it = special.begin(); it != special.end(); it++) {
		funcHelp.push_back(it->first);
	}
	std::sort(funcHelp.begin(), funcHelp.end(), compareAlpha);
	for (std::vector<std::string>::iterator it = funcHelp.begin(); it != funcHelp.end(); it++) {
		std::cout << *it << std::endl;
	}
}



void debug() {
	debugMode = !debugMode;
}

void modExit(changes change)
{
	change.dataChange.boolChange = false;
}


// Core Functions
bool run(changes change) {
	bool programRan = runProgram(change, parse(change.input));
	if (programRan) { return true; }
	try {
		std::vector<std::string> parseBuffer = parse(change.input);
		for (int i = 0; i <= strParse.size() - 1; i++) {
			strParse[i](change, parseBuffer);
		}
		if (special.find(parseBuffer[0]) != special.end() && parseBuffer.size() >= 2) {
			special[parseBuffer[0]](change, parseBuffer);
			return true;
		}
		else if (parseBuffer.size() == 1) {
			std::cout << "Invalid arguments(requires more input)" << std::endl;
		}

		if (funcsChanges.find(change.input) == funcsChanges.end()) {
			if (funcs.find(change.input) != funcs.end()) {
				funcs[change.input]();

				return true;
			}
			else {
				std::cout << "Unknown Command or Program[\"" << change.input << "\"]" << std::endl;
			}
		}
		else {
			funcsChanges[change.input](change);
			return true;
		}


		if (debugMode) {
			std::cout << "Ran: " << change.input << std::endl;
		}

	}
	catch (std::exception e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	return true;
}


void init(changes change, properties windowProperties) {
	SetConsoleScreenBufferSize(windowProperties.consoleHandle, windowProperties.points);
	SetConsoleWindowInfo(windowProperties.consoleHandle, TRUE, &windowProperties.windowSize);
	SetConsoleTitleW(windowProperties.windowName);
	char v[FILENAME_MAX];
	_getcwd(v, sizeof(v));
	change.dataChange.stringChange = v;
	std::cout << "VERSION: " << VERSION << std::endl;
}

void applyWindowProperties(properties windowProperties) {
	SetConsoleScreenBufferSize(windowProperties.consoleHandle, windowProperties.points);
	SetConsoleWindowInfo(windowProperties.consoleHandle, TRUE, &windowProperties.windowSize);
	SetConsoleTitleW(windowProperties.windowName);
}

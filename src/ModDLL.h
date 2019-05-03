#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <functional>
#include <exception>
#include <utility>
#include <algorithm>
#include <direct.h>
#include <filesystem>
#include <string>
#include <sstream>
#include <iterator>




// Programmer Defined Variables(constant)
const std::string VERSION = "1.1";

// Macro Definitions

#ifdef MODDLL_EXPORTS
#define MODDLL_API __declspec(dllexport)
#else
#define MODDLL_API __declspec(dllimport)
#endif

// Macro Defines
#define STRNULL ""

// Function Definitions


// Data Types
struct changesData {
	std::string& stringChange;
	bool& boolChange;
	int& intChange;
	changesData(std::string& stringChange, bool& boolChange, int& intChange) : stringChange(stringChange), boolChange(boolChange), intChange(intChange) {}
};

struct changes {
	std::string input;
	changesData dataChange;
	changes(std::string inp, changesData dataChange) : input(inp), dataChange(dataChange) {}
};

// Window data, program data, etc
struct properties {
	LPCWSTR windowName;
	COORD points;
	HANDLE consoleHandle;
	SMALL_RECT windowSize;

	//properties(std::string windowN, COORD point, HANDLE handle, SMALL_RECT windowInfo) : windowName(windowN), points(point), consoleHandle(handle), windowSize(windowInfo) {}
};

enum parserType {
	NA = 0,
	identifier,
	setter,
	variable
};


MODDLL_API void applyWindowProperties(properties windowProperties);
MODDLL_API std::vector<std::string> parse(std::string inp);
MODDLL_API void init(changes change, properties windowProperties); // Initialize variables, functions, and various other settings.
MODDLL_API bool run(changes change); // Function to be regularly ran that handles input.
MODDLL_API void modExit(changes change);
MODDLL_API void debug();


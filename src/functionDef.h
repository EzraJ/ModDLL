#pragma once
#ifndef FUNCTIONDEF_INCLUDE
#define FUNCTIONDEF_INCLUDE

#include <iostream>
#include <windows.h>
#include "tokenParser.h"


bool runProgram(changes change, std::vector<std::string> bufferVector);

void clear();
void dirAdv(changes change, std::vector<std::string> bufferVector);
void printVersion();
void make(changes change, std::vector<std::string> bufferVector);
void cat(changes change, std::vector<std::string> bufferVector);
void list(changes change);
void help();
void man(changes change, std::vector<std::string> bufferVector);
void echoFunction(changes change, std::vector<std::string> bufferVector);
void alias(changes change, std::vector<std::string> bufferVector);
void variableParse(changes change, std::vector<std::string>& bufferVector);

#endif
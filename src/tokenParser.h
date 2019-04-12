#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

#define STRNULL ""

class tokenParser {
public:

	parserType getType(std::string accesser) {
		try {
			return tokenTypes[accesser];
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			return parserType::NA;
		}

	}



	std::string getString(std::string accesser) {
		try {
			return tokens[accesser];
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
			return STRNULL;
		}
	}


	tokenParser(std::string toProcess, std::string delim = STRNULL) {
		std::vector<std::string> bufferVector = parse(toProcess);
		std::vector<std::string> excludedProcess;
		for (std::vector<std::string>::iterator it = bufferVector.begin(); it != bufferVector.end(); it++) {
			if (*it != delim && *it != " ") {
				excludedProcess.emplace_back(*it);
				std::cout << *it;
			}
		}
		for (std::vector<std::string>::iterator it = excludedProcess.begin(); it != excludedProcess.end(); it++) {
			advance(*it);
		}
	}

	void advance(std::string adv) {

		tokens[std::string("arg" + std::to_string(argT))] = adv;
		argT++;
		advanceType(adv);
	}

	void advanceType(std::string adv) {
		parserType bufferType = parserType::NA;
		if (adv == "=") {
			bufferType = parserType::setter;
		}
		else {
			if (argT - 1 != -1) {
				if (tokens[std::string("arg" + (std::to_string(argT - 1)))] != "=") {
					if (tokens[std::string("arg" + (argT + 1))] != STRNULL && tokens[std::string("arg" + std::to_string((argT + 1)))] != "=") {
						bufferType = parserType::variable;
					}
				}
				else {
					bufferType = parserType::identifier;
				}
			}
		}
		tokenTypes[std::string("arg" + std::to_string(argType))] = bufferType;
		argType++;
	}

private:
	int argT = 0;
	int argType = 0;
	std::unordered_map<std::string, std::string> tokens;
	std::unordered_map<std::string, parserType> tokenTypes;

	std::vector<std::string> parse(std::string inp) {
		std::istringstream ss(inp);
		using StrIt = std::istream_iterator<std::string>;
		std::vector<std::string> container(StrIt(ss), StrIt{});
		return container;
	}

};

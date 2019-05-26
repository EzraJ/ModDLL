#include "functionDef.h"

std::string getPath() {
	char path[256];
	_getcwd(path, sizeof(path));
	return std::string(path);
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
	std::cout << 'v' << VERSION << std::endl;
}

void make(changes change, std::vector<std::string> bufferVector) {
	std::ofstream file(bufferVector[1]);
	file << bufferVector[1];
	file.close();
}

void cat(changes change, std::vector<std::string> bufferVector) {
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


void man(changes change, std::vector<std::string> bufferVector) {
	std::ifstream manFile("man.txt");
	if (manFile.good()) {
		std::cout << "Succesfully opened up man file" << std::endl;
	}
	else {
		std::cout << "ERROR: Man file corrupted/not found" << std::endl;
		return;
	}

	manFile.close();
	manFile.open("man.txt");
	std::string keyWord = bufferVector[1];
	std::string buffer;
	int currentLine = 0;
	std::string printInformation;
	while (std::getline(manFile, buffer)) {
		currentLine++;
		if (buffer.find(keyWord, 0) != std::string::npos) {
			printInformation += buffer;
			break;
		}
	}

	while (std::getline(manFile, buffer)) {
		if (buffer != "SEP") {
			printInformation += "\n" + buffer;
		}
		else {
			break;
		}
	}

	std::cout << printInformation << std::endl;
	manFile.close();
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
void variableParse(changes change, std::vector<std::string> & bufferVector);



void modExit(changes change)
{
	change.dataChange.boolChange = false;
}

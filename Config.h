#pragma once
#include <string>
#include <stdio.h>
#include <sstream>

//class to parse the config file and hold the info it parsed
class Config {
public:
	int maxTransitions;
	int maxCharacters;
	int transitionsPerStep;
	int truncated;

	Config(std::string configFilePath);
	~Config();
};

Config::Config(std::string configFilePath) {
	//default values
	maxTransitions = 100;
	maxCharacters = 100;
	transitionsPerStep = 1;
	truncated = 0;

	//open the configFilePath and parse it
	FILE* fp = fopen(configFilePath.c_str(), "r");

	if (fp == NULL) {
		std::cout << "Error: config file not found " << configFilePath << std::endl;
	}
	else {
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		rewind(fp);
		char* buffer = new char[fileSize];
		fread(buffer, 1, fileSize, fp);
		std::stringstream ss(buffer);
		std::string line;

		while (std::getline(ss, line)) {
			if (line.compare(0, 20, "MAXIMUM_TRANSITIONS=") == 0) {
				maxTransitions = atoi(line.substr(20, line.length() - 20).c_str());
			}
			else if (line.compare(0, 19, "MAXIMUM_CHARACTERS=") == 0) {
				maxCharacters = atoi(line.substr(19, line.length() - 19).c_str());
			}
			else if (line.compare(0, 21, "TRANSITIONS_PER_STEP=") == 0) {
				transitionsPerStep = atoi(line.substr(21, line.length() - 21).c_str());
			}
			else if (line.compare(0, 10, "TRUNCATED=") == 0) {
				truncated = atoi(line.substr(10, line.length() - 10).c_str());
			}
		}

		std::cout << "maxTransitions: " << maxTransitions <<
			" max chars: " << maxCharacters <<
			" transitions per step: " << transitionsPerStep <<
			" truncated: " << truncated << std::endl;
	}
}

Config::~Config() {}
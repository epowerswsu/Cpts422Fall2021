#pragma once
#include <string>
#include <stdio.h>
#include <sstream>

//class to parse the config file and hold the info it parsed
class Config {
public:
	int maxTransitions;
	int transitionsPerStep;
	int truncated;

	Config(std::string configFilePath);
	~Config();
};

Config::Config(std::string configFilePath) {
	//default values
	maxTransitions = 100;
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
			if (line.compare(0, 15, "maxTransitions=") == 0) {
				maxTransitions = atoi(line.substr(15, line.length() - 15).c_str());
			}
			else if (line.compare(0, 19, "transitionsPerStep=") == 0) {
				transitionsPerStep = atoi(line.substr(19, line.length() - 19).c_str());
			}
			else if (line.compare(0, 10, "truncated=") == 0) {
				truncated = atoi(line.substr(10, line.length() - 10).c_str());
			}
		}

		std::cout << "maxTransitions: " << maxTransitions <<
			" transitions per step: " << transitionsPerStep <<
			" truncated: " << truncated << std::endl;
	}
}

Config::~Config() {}
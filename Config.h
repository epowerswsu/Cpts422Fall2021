#pragma once
#include <string>

//class to parse the config file and hold the info it parsed
class Config {
public:
	int maxTransitions;
	int transitionsPerStep;
	bool truncated;

	Config(std::string configFilePath);
	~Config();
};

Config::Config(std::string configFilePath) {
	//default values
	maxTransitions = 100;
	transitionsPerStep = 1;
	truncated = false;

	//open the configFilePath and parse it

}

Config::~Config() {}
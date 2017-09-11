#pragma once

#include <map>
#include <string>

class Script;

class Scripts {
	public:
		static void init();
		static void execute(const char* command);
		static void executeScript(std::string path);
		static void destroy();
		static void update();
		static void loadResource(std::string _path);
		static std::map<std::string, Script*> database;
};
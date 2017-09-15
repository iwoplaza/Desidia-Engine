#pragma once

#include <string>

class Script {
	protected:
		std::string path;
		std::string source;
	public:
		Script(std::string path, std::string source);

		void execute();
		std::string getSource();
		std::string getPath();
};
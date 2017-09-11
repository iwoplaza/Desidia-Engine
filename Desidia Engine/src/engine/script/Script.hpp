#pragma once

#include <string>

class Script {
	protected:
		std::string source;
	public:
		Script(std::string source);

		void execute();
		std::string getSource();
};
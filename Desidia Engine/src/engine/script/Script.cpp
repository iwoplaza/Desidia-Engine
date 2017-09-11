#include "Script.hpp"
#include "Scripts.hpp"

Script::Script(std::string _source) {
	source = _source;
}

void Script::execute() {
	Scripts::execute(source.c_str());
}

std::string Script::getSource() {
	return source;
}
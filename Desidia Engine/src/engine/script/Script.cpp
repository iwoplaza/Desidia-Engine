#include "Script.hpp"
#include "Scripts.hpp"
#include "ScriptContext.hpp"

Script::Script(std::string _path, std::string _source) : path(_path), source(_source){}

void Script::execute() {
	Scripts::execute(source.c_str());
}

std::string Script::getSource() {
	return source;
}

std::string Script::getPath() {
	return path;
}
#pragma once

#include <string>

class SceneLoader {
	public:
		static void loadResource(const char* _path);
		static void loadFromString(const char* _code);
};
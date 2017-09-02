#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

class Texture {
	public:
		Texture();
		Texture(std::string key);
		~Texture();

		string key;
		GLuint id;

		static map<string, Texture*> cache;
		static GLuint load(std::string key);
		static void unloadCache();
		static Texture* get(std::string key);
		static bool bind(std::string key);
		static bool add(std::string key);
};
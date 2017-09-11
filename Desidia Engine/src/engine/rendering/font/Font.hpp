#pragma once
#include "FontCharacter.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <GL/glew.h>

struct FontParsePair {
	FontParsePair();
	FontParsePair(const char* _key, const char* _data);

	std::string key;
	std::string data;
};

class Font {
	protected:
		int width;
		int height;
		int lineHeight;
		int size;
		GLuint textureAtlas;
		std::map<char, FontCharacter*> characters;
	public:
		Font();
		Font(const char* filename);

		bool loadFromFile(const char* _path);
		void bindTexture();
		bool isCharMapped(const char& _char);
		int getLineHeight();
		int getSize();
		FontCharacter* findCharacter(char);
		std::vector<FontParsePair> getDataFromLine(std::string _line);

		static std::map<const char*, Font*> database;
		static Font* loadResource(const char* _path);
};
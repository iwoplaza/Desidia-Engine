#include "Font.hpp"
#include "../texture/Texture.hpp"
#include "../../Resources.hpp"
#include <iostream>

FontParsePair::FontParsePair()
	: key(""), data("") {}

FontParsePair::FontParsePair(const char* _key, const char* _data)
	: key(_key), data(_data) {
}

Font::Font()
	: characters(map<char, FontCharacter*>()), width(1), height(1), lineHeight(0), size(0) {}

Font::Font(const char* _path) : Font() {
	loadFromFile(_path);
}

bool Font::loadFromFile(const char* _path) {
	string texturePath = _path;
	texturePath = texturePath.substr(0, texturePath.find_last_of('/')+1);

	std::ifstream in(Resources::ROOT_PATH + _path);
	if (!in.is_open()) {
		std::cerr << "Failed to open font: " << _path << endl;
		return false;
	}

	string line = "";
	while (getline(in, line)) {
		vector<FontParsePair> dataList = getDataFromLine(line);
		FontCharacter* _char = new FontCharacter();
		int _id = -1;

		for (FontParsePair pair : dataList) {
			if (pair.key == "id")
				_id = atoi(pair.data.c_str());
			else if (pair.key == "scaleW")
				width = atoi(pair.data.c_str());
			else if (pair.key == "scaleH")
				height = atoi(pair.data.c_str());
			else if (pair.key == "lineHeight")
				lineHeight = atoi(pair.data.c_str());
			else if (pair.key == "size")
				size = atoi(pair.data.c_str());
			else if (pair.key == "x")
				_char->texX = (float)atoi(pair.data.c_str()) / width;
			else if (pair.key == "y")
				_char->texY = (float)atoi(pair.data.c_str()) / height;
			else if (pair.key == "width") {
				_char->width = atoi(pair.data.c_str());
				_char->texW = (float)(_char->width) / width;
			}
			else if (pair.key == "height") {
				_char->height = atoi(pair.data.c_str());
				_char->texH = (float)(_char->height) / height;
			}
			else if (pair.key == "xoffset")
				_char->offsetX = atoi(pair.data.c_str());
			else if (pair.key == "yoffset")
				_char->offsetY = atoi(pair.data.c_str());
			else if (pair.key == "xadvance")
				_char->advanceX = atoi(pair.data.c_str());
			else if (pair.key == "file")
				texturePath += pair.data.c_str();
		}

		if (_id != -1) {
			_char->compile();
			characters[(char)_id] = _char;
		}
	}

	textureAtlas = Texture::load(texturePath);
	return false;
}

vector<FontParsePair> Font::getDataFromLine(std::string _line) {
	vector<FontParsePair> dataList = vector<FontParsePair>();
	bool grabbedTitle = false;
	bool grabbingValue = false;
	std::string bufferKey = "";
	std::string bufferData = "";
	for (int i = 0; i < _line.length(); i++) {
		if (i == (_line.length() - 1)) {
			if (_line[i] != '"'){
				if (!grabbingValue) bufferKey += _line[i];
				else				bufferData += _line[i];
			}

			if (!grabbedTitle) {
				grabbedTitle = true;
				dataList.push_back(FontParsePair("TITLE", bufferKey.c_str()));
			}
			else {
				dataList.push_back(FontParsePair(bufferKey.c_str(), bufferData.c_str()));
			}
			grabbingValue = false;
			bufferKey = "";
			bufferData = "";
		}else if (_line[i] == ' ' || _line[i] == '\n' || _line[i] == '\r') {
			if (_line[i-1] != ' ') {
				if (!grabbedTitle) {
					grabbedTitle = true;
					dataList.push_back(FontParsePair("TITLE", bufferKey.c_str()));
				}
				else {
					dataList.push_back(FontParsePair(bufferKey.c_str(), bufferData.c_str()));
				}
				grabbingValue = false;
				bufferKey = "";
				bufferData = "";
			}
		}
		else if (_line[i] == '=') {
			grabbingValue = true;
		}
		else if(_line[i] != '"'){
			if (!grabbingValue) bufferKey += _line[i];
			else				bufferData += _line[i];
		}
	}

	return dataList;
}

void Font::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureAtlas);
}

int Font::getLineHeight() {
	return lineHeight;
}

int Font::getSize() {
	return size;
}

bool Font::isCharMapped(const char& _char) {
	return !(characters.find(_char) == characters.end());
}

FontCharacter* Font::findCharacter(char c) {
	return characters[c];
}

Font* Font::loadResource(const char* _path) {
	return new Font(_path);
}
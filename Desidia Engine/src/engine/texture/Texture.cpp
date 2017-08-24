#include "Texture.hpp"
#include <iostream>
#include <IL/ilut.h>
#include <IL/ilu.h>
#pragma comment(lib, "DevIL.lib")
#pragma comment(lib, "ILU.lib")

map<string, Texture*> Texture::cache = map<string, Texture*>();

Texture::Texture() {
	key = "NULL";
}

Texture::Texture(string filename) {
	id = load(filename);
	key = filename;
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

GLuint Texture::load(string filename) {
	string path = "res/" + filename;

	GLuint textureID;

	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);
	ILboolean success = ilLoadImage((ILstring)path.c_str());
	
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	int type = ilGetInteger(IL_IMAGE_TYPE);

	iluFlipImage();

	if (!success) {
		ilDeleteImages(1, &imgID);
		cerr << "Couldn't load image: " << filename.c_str() << endl;
		exit(EXIT_FAILURE);
	}
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	ilDeleteImages(1, &imgID);

	return textureID;
}

void Texture::unloadCache() {
	typedef std::map<string, Texture*>::iterator it_type;
	for (it_type iterator = cache.begin(); iterator != cache.end(); iterator++) {
		delete iterator->second;
	}
	cache.clear();
}

Texture* Texture::get(std::string key) {
	if (cache.find(key) == cache.end()) {
		return nullptr;
	}
	return cache[key];
}

bool Texture::bind(string key) {
	Texture* texture = get(key);
	if (texture == nullptr) return false;
	glBindTexture(GL_TEXTURE_2D, texture->id);
	return true;
}

bool Texture::add(string filename) {
	Texture* texture = new Texture(filename);
	if (filename != "NULL") {
		cache[filename] = texture;
		return true;
	}
	return false;
}
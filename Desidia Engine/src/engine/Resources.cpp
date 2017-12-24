#include "Resources.hpp"
#include "loader/OBJLoader.hpp"
#include "scene/SceneLoader.hpp"
#include "rendering/shader/ShaderManager.hpp"
#include "rendering/font/Font.hpp"
#include "rendering/texture/Texture.hpp"
#include "rendering/material/Material.hpp"
#include "script\Scripts.hpp"
#include <rapidjson/document.h>
#include <fstream>
#include <iostream>

using namespace rapidjson;

std::string Resources::ROOT_PATH = "res/";
std::map<std::string, Mesh*> Resources::MODEL = std::map<std::string, Mesh*>();
std::map<std::string, Font*> Resources::FONT = std::map<std::string, Font*>();
std::map<std::string, Material*> Resources::MATERIAL = std::map<std::string, Material*>();

Resources::Resources() {
	resourcesToLoad = std::map<std::string, std::vector<std::string>>();
}

Resources::~Resources() {

}

void Resources::loadFromFile(const char* _path) {
	std::ifstream in(Resources::ROOT_PATH + _path);
	if (!in.is_open()) {
		std::cerr << "Failed to open a resource file: " << _path << std::endl;
		return;
	}

	std::string code;

	in.seekg(0, std::ios::end);
	code.reserve(in.tellg());
	in.seekg(0, std::ios::beg);

	code.assign((std::istreambuf_iterator<char>(in)),
				 std::istreambuf_iterator<char>());

	loadFromString(code.c_str());
}

void Resources::loadFromString(const char* _code) {
	Document document;
	document.Parse(_code);

	resourcesToLoad["models"] = std::vector<std::string>();
	if (document.HasMember("models")) {
		const Value& modelsNode = document["models"];
		for (auto& v : modelsNode.GetArray()) {
			resourcesToLoad["models"].push_back(v.GetString());
		}
	}

	resourcesToLoad["fonts"] = std::vector<std::string>();
	if (document.HasMember("fonts")) {
		const Value& fontsNode = document["fonts"];
		for (auto& v : fontsNode.GetArray()) {
			resourcesToLoad["fonts"].push_back(v.GetString());
		}
	}

	resourcesToLoad["shaders"] = std::vector<std::string>();
	if (document.HasMember("shaders")) {
		const Value& shadersNode = document["shaders"];
		for (auto& v : shadersNode.GetArray()) {
			resourcesToLoad["shaders"].push_back(v.GetString());
		}
	}

	resourcesToLoad["textures"] = std::vector<std::string>();
	if (document.HasMember("textures")) {
		const Value& texturesNode = document["textures"];
		for (auto& v : texturesNode.GetArray()) {
			resourcesToLoad["textures"].push_back(v.GetString());
		}
	}

	resourcesToLoad["materials"] = std::vector<std::string>();
	if (document.HasMember("materials")) {
		const Value& materialsNode = document["materials"];
		for (auto& v : materialsNode.GetArray()) {
			resourcesToLoad["materials"].push_back(v.GetString());
		}
	}

	resourcesToLoad["scripts"] = std::vector<std::string>();
	if (document.HasMember("scripts")) {
		const Value& scriptsNode = document["scripts"];
		for (auto& v : scriptsNode.GetArray()) {
			resourcesToLoad["scripts"].push_back(v.GetString());
		}
	}

	resourcesToLoad["scenes"] = std::vector<std::string>();
	if (document.HasMember("scene"))
		resourcesToLoad["scenes"].push_back(document["scene"].GetString());
}

void Resources::perform() {
	for (auto& key : resourcesToLoad["models"])
		loadModel(key);

	for (auto& key : resourcesToLoad["fonts"])
		loadFont(key);

	for (auto& key : resourcesToLoad["shaders"])
		loadShader(key);

	for (auto& key : resourcesToLoad["textures"])
		Texture::add(key.c_str());

	for (auto& key : resourcesToLoad["materials"])
		loadMaterial(key);

	for (auto& key : resourcesToLoad["scripts"])
		loadScript(key);

	for (auto& key : resourcesToLoad["scenes"])
		SceneLoader::loadResource(key.c_str());

	//TODO Create automatic loading for fonts from a resource file.
}

void Resources::loadModel(std::string key) {
	if(Resources::MODEL.find(key) == Resources::MODEL.end())
		Resources::MODEL[key] = OBJLoader::loadMeshFromFile(key);
}

void Resources::loadFont(std::string key) {
	if (Resources::FONT.find(key) == Resources::FONT.end())
		Resources::FONT[key] = Font::loadResource(key.c_str());
}

void Resources::loadMaterial(std::string key) {
	if (Resources::MATERIAL.find(key) == Resources::MATERIAL.end())
		Resources::MATERIAL[key] = Material::loadResource(key);
}

void Resources::loadScript(std::string key) {
	Scripts::loadResource(key);
	Scripts::executeScript(key);
}

void Resources::loadShader(std::string key) {
	ShaderManager::loadResource(key.c_str());
}
#include "SceneLoader.hpp"
#include "../Resources.hpp"
#include "Scene.hpp"
#include "../gameobject/GameObject.hpp"
#include "../util/Vector3.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>

using namespace rapidjson;

void SceneLoader::loadResource(const char* _path) {
	std::ifstream in(Resources::ROOT_PATH + _path);
	if (!in.is_open()) {
		std::cerr << "Failed to open a scene file: " << _path << std::endl;
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

void SceneLoader::loadFromString(const char* _code) {
	Document document;
	document.Parse(_code);

	if (!document.HasMember("name")) {
		std::cerr << "[SceneLoader] Parser Error: Scene's 'name' property is undefined." << std::endl;
		return;
	}
	Scene* scene = new Scene(document["name"].GetString());

	const Value& objectsNode = document["objects"];
	for (auto& objectNode : objectsNode.GetArray()) {
		GameObject* gameObject = GameObject::parseJSON(objectNode);
		if(gameObject != nullptr)
			scene->addGameObject(gameObject);
	}

	Scene::current = scene;
	Scene::current->init();
}
#include "Scene.hpp"
#include "../gameobject/GameObject.hpp"
#include <iostream>

Scene* Scene::current;

Scene::Scene() {
	gameObjects = map<string, GameObject*>();
	updatable = vector<GameObject*>();
}

Scene::Scene(string _name) : Scene() {
	name = _name;
}

Scene::~Scene() {
	for (pair<string, GameObject*> p : gameObjects) {
		delete p.second;
	}
	gameObjects.clear();
	updatable.clear();
}

void Scene::init() {
	for (std::pair<string, GameObject*> pair : gameObjects) {
		pair.second->init();
	}
	postInit();
}

void Scene::postInit() {
	for (std::pair<string, GameObject*> pair : gameObjects) {
		pair.second->postInit();
	}
}

void Scene::update() {
	for (GameObject* gameObject : updatable) {
		gameObject->update();
	}
}

void Scene::draw() {
	for (std::pair<string, GameObject*> pair : gameObjects) {
		pair.second->draw();
	}
}

void Scene::onMouseMove() {
	for (GameObject* gameObject : updatable) {
		gameObject->onMouseMove();
	}
}

void Scene::addGameObject(GameObject* _gameObject) {
	if (gameObjects.find(_gameObject->getName()) != gameObjects.end()) {
		cerr << "Tried to add a duplicate by the name of '" << _gameObject->getName() << "' to the scene." << endl;
		return;
	}

	gameObjects[_gameObject->getName()] = _gameObject;

	if (_gameObject->doesNeedUpdates()) {
		updatable.push_back(_gameObject);
	}
}

GameObject* Scene::getGameObject(std::string name) {
	if (gameObjects.find(name) == gameObjects.end()) return nullptr;
	return gameObjects[name];
}
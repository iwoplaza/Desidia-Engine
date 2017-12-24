#include "Scene.hpp"
#include "../gameobject/GameObject.hpp"
#include <iostream>

Scene* Scene::current;

Scene::Scene() {
	m_gameObjects = map<string, GameObject*>();
	m_updatable = vector<GameObject*>();
	m_physicsSpace = PhysicsSpace();
}

Scene::Scene(string _name) : Scene() {
	m_name = _name;
}

Scene::~Scene() {
	for (pair<string, GameObject*> p : m_gameObjects) {
		delete p.second;
	}
	m_gameObjects.clear();
	m_updatable.clear();
}

void Scene::init() {
	for (std::pair<string, GameObject*> pair : m_gameObjects) {
		pair.second->init();
	}
	postInit();
}

void Scene::postInit() {
	for (std::pair<string, GameObject*> pair : m_gameObjects) {
		pair.second->postInit();
	}
	m_physicsSpace.init();
}

void Scene::update() {
	for (GameObject* gameObject : m_updatable) {
		gameObject->update();
	}

	m_physicsSpace.update();
}

void Scene::draw() {
	for (std::pair<string, GameObject*> pair : m_gameObjects) {
		pair.second->draw();
	}

	m_physicsSpace.drawGizmos();
}

void Scene::onMouseMove() {
	for (GameObject* gameObject : m_updatable) {
		gameObject->onMouseMove();
	}
}

void Scene::addGameObject(GameObject* _gameObject) {
	if (m_gameObjects.find(_gameObject->getName()) != m_gameObjects.end()) {
		cerr << "Tried to add a duplicate by the name of '" << _gameObject->getName() << "' to the scene." << endl;
		return;
	}

	m_gameObjects[_gameObject->getName()] = _gameObject;

	if (_gameObject->doesNeedUpdates()) {
		m_updatable.push_back(_gameObject);
	}
}

GameObject* Scene::getGameObject(std::string name) {
	if (m_gameObjects.find(name) == m_gameObjects.end()) return nullptr;
	return m_gameObjects[name];
}

PhysicsSpace* Scene::getPhysicsSpace() {
	return &m_physicsSpace;
}
#include "Scene.hpp"
#include "../gameobject/GameObject.hpp"
#include "../lighting/LightSource.hpp"
#include "../rendering/shader/ShaderManager.hpp"
#include "../rendering/shader/Shader.hpp"
#include "../rendering/GLHelper.hpp"
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

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
	updateLighting();

	for (std::pair<string, GameObject*> pair : m_gameObjects) {
		pair.second->draw();
	}

	m_physicsSpace.drawGizmos();
}

void Scene::reload() {
	cout << "[SCENE] Reloading \"" << m_name << "\"..." << endl;

	for (std::pair<string, GameObject*> pair : m_gameObjects) {
		pair.second->reload();
	}
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

void Scene::addLightSource(LightSource* _lightSource) {
	std::vector<LightSource*>::iterator it = m_lightSources.begin();
	while (it != m_lightSources.end())
		if (*it == _lightSource)
			return;
		else
			it++;

	m_lightSources.push_back(_lightSource);
}

void Scene::updateLighting() {
	vector<LightSource*> *lightSources = &m_lightSources;
	ShaderManager::forEach([&lightSources] (Shader* shader) {
		ShaderManager::use(shader);

		int lightSourceCount = lightSources->size();
		GLfloat* locationBuffer = new GLfloat[lightSourceCount * 3];
		GLfloat* colorBuffer = new GLfloat[lightSourceCount * 4];
		for (int i = 0; i < lightSourceCount; ++i) {
			LightSource* lightSource = (*lightSources)[i];
			Vector3 location = lightSource->getLocation();
			Color color = lightSource->getColor();
			glm::vec4 glmLoc(location.x, location.y, location.z, 1);
			glmLoc = GLHelper::currentState.viewMatrix * glmLoc;
			locationBuffer[i * 3]	  =	glmLoc.x;
			locationBuffer[i * 3 + 1] = glmLoc.y;
			locationBuffer[i * 3 + 2] = glmLoc.z;
			colorBuffer[i * 4]	   = color.r;
			colorBuffer[i * 4 + 1] = color.g;
			colorBuffer[i * 4 + 2] = color.b;
			colorBuffer[i * 4 + 3] = color.a;
		}
		glUniform3fv(ShaderManager::getUniform("uLightSources.location"), lightSourceCount, locationBuffer);
		glUniform4fv(ShaderManager::getUniform("uLightSources.color"), lightSourceCount, colorBuffer);
	});
}

void Scene::removeLightSource(LightSource* _lightSource) {
	std::vector<LightSource*>::iterator it = m_lightSources.begin();
	while (it != m_lightSources.end())
		if (*it == _lightSource)
			m_lightSources.erase(it);
		else
			it++;
}

GameObject* Scene::getGameObject(std::string name) {
	if (m_gameObjects.find(name) == m_gameObjects.end()) return nullptr;
	return m_gameObjects[name];
}

PhysicsSpace* Scene::getPhysicsSpace() {
	return &m_physicsSpace;
}
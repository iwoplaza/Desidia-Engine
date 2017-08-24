#include "Scene.hpp"

Scene::Scene() {
	gameObjects = map<string, GameObject*>();
}

Scene::~Scene() {
	for (pair<string, GameObject*> p : gameObjects) {
		delete p.second;
	}
	gameObjects.clear();
}
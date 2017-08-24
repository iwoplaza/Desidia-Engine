#pragma once
#include <map>

using namespace std;

class GameObject;

class Scene {
	protected:
		map<string, GameObject*> gameObjects;

	public:
		Scene();
		~Scene();
};
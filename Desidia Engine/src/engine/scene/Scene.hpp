#pragma once
#include <map>
#include <vector>

using namespace std;

class GameObject;

class Scene {
	protected:
		string name;
		map<string, GameObject*> gameObjects;
		vector<GameObject*> updatable;
	public:
		Scene();
		Scene(string _name);
		~Scene();

		void init();
		void update();
		void draw();
		void addGameObject(GameObject* _gameObject);
		GameObject* getGameObject(std::string name);

		static Scene* current;
};
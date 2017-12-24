#pragma once
#include <map>
#include <vector>
#include "../physics/PhysicsSpace.hpp"

using namespace std;

class GameObject;

class Scene {
	protected:
		string m_name;
		map<string, GameObject*> m_gameObjects;
		vector<GameObject*> m_updatable;
		PhysicsSpace m_physicsSpace;
	public:
		Scene();
		Scene(string _name);
		~Scene();

		void init();
		void postInit();
		void update();
		void draw();
		void onMouseMove();
		void addGameObject(GameObject* _gameObject);
		GameObject* getGameObject(std::string name);
		PhysicsSpace* getPhysicsSpace();

		static Scene* current;
};
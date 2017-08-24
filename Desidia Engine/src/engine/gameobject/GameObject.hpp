#pragma once
#include "component\Component.hpp"
#include <vector>
#include <map>

using namespace std;

class GameObject {
	private:
		string name;
		bool needsUpdates = false;
		map<string, vector<Component*>> componentGroups;
	public:
		GameObject(string _name);
		~GameObject();

		void update();
		void draw();

		GameObject* addComponent(Component* _component);
		GameObject* markUpdatable();
};
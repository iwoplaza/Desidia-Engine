#pragma once
#include "component\Component.hpp"
#include "../util/Vector3.hpp"
#include <vector>
#include <map>

using namespace std;

class GameObject {
	private:
		string name;
		Vector3 location;
		bool needsUpdates = false;
		map<string, vector<Component*>> componentGroups;
	public:
		GameObject(string _name);
		~GameObject();

		void init();
		void update();
		void draw();
		GameObject* addComponent(Component* _component);
		GameObject* markUpdatable();
		
		string getName();
		bool doesNeedUpdates();
		void setLocation(const Vector3& _location);

		friend ostream& operator<<(ostream& os, const GameObject& v);

		static GameObject* parseJSON(const Value&);
};
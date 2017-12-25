#pragma once
#include "component/Component.hpp"
#include "Transform.hpp"
#include <vector>
#include <map>

using namespace std;

class GameObject {
	private:
		string name;
		Transform m_transform;
		bool needsUpdates = false;
		map<string, vector<Component*>> componentGroups;
	public:
		GameObject(string _name);
		~GameObject();

		void init();
		void postInit();
		void update();
		void draw();
		void reload();
		void onMouseMove();
		GameObject* addComponent(Component* _component);
		GameObject* markUpdatable();
		
		string getName() const;
		Transform* getTransform();
		bool doesNeedUpdates();
		
		vector<Component*> getComponents(string groupName);
		Component* getComponent(string groupName, int index);
		Component* getComponent(string groupName);

		friend ostream& operator<<(ostream& os, const GameObject& v);

		static GameObject* parseJSON(const Value&);
};
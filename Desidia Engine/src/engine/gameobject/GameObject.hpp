#pragma once
#include "component/Component.hpp"
#include "../util/Vector3.hpp"
#include "../util/Quaternion.hpp"
#include <vector>
#include <map>

using namespace std;

class GameObject {
	private:
		string name;
		Vector3 location;
		Quaternion orientation;
		Vector3 scale;
		glm::mat4 transform;
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
		
		string getName();
		bool doesNeedUpdates();
		Vector3 getLocation();
		Quaternion getOrientation();
		Vector3 getScale();
		glm::mat4 getTransform();
		Vector3 getForwardVector();
		Vector3 getRightVector();
		vector<Component*> getComponents(string groupName);
		Component* getComponent(string groupName, int index);
		Component* getComponent(string groupName);
		void setLocation(const Vector3& _location);
		void setOrientation(const Quaternion& _orientation);
		void setOrientation(const Vector3& _orientation);
		void rotate(const Vector3& _rotation);
		void rotateX(float _x);
		void rotateY(float _y);
		void rotateZ(float _z);
		void setScale(const Vector3& _scale);

		friend ostream& operator<<(ostream& os, const GameObject& v);

		static GameObject* parseJSON(const Value&);
};
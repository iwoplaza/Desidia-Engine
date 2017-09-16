#pragma once
#include "component\Component.hpp"
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
		glm::mat4 transform;
		bool needsUpdates = false;
		map<string, vector<Component*>> componentGroups;
	public:
		GameObject(string _name);
		~GameObject();

		void init();
		void update();
		void draw();
		void onMouseMove();
		GameObject* addComponent(Component* _component);
		GameObject* markUpdatable();
		
		string getName();
		bool doesNeedUpdates();
		Vector3 getLocation();
		Quaternion getOrientation();
		glm::mat4 getTransform();
		Vector3 getForwardVector();
		Vector3 getRightVector();
		void setLocation(const Vector3& _location);
		void setOrientation(const Quaternion& _orientation);
		void setOrientation(const Vector3& _orientation);
		void rotate(const Vector3& _rotation);
		void rotateX(float _x);
		void rotateY(float _y);
		void rotateZ(float _z);

		friend ostream& operator<<(ostream& os, const GameObject& v);

		static GameObject* parseJSON(const Value&);
};
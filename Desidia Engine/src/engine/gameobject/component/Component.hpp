#pragma once

#include <string>

using namespace std;

class GameObject;

class Component {
	protected:
		GameObject* gameObject;
	
	public:
		Component();
		~Component();

		Component* setGameObject(GameObject* _gameObject);

		virtual void update();
		virtual void draw();
		virtual const char* getType() = 0;
};
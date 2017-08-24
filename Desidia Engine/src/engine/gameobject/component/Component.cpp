#include "Component.hpp"
#include "../GameObject.hpp"
#include <iostream>

Component::Component() {

}

Component::~Component() {

}

Component* Component::setGameObject(GameObject* _gameObject) {
	if (gameObject == nullptr)
		gameObject = _gameObject;
	else
		cerr << "Tried to set a parent GameObject to an already established Component.";

	return this;
}

void Component::update() {}
void Component::draw() {}
#include "Component.hpp"
#include "../GameObject.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentMesh.hpp"
#include "../component/ComponentScript.hpp"
#include "../component/ComponentCamera.hpp"
#include <iostream>

map<string, FUNCTION_COMPONENT_PARSE> Component::callbackMap = map<string, FUNCTION_COMPONENT_PARSE>();

void Component::registerAll() {
	registerComponent("ComponentMesh", ComponentMesh::parseJSON);
	registerComponent("ComponentScript", ComponentScript::parseJSON);
	registerComponent("ComponentCamera", ComponentCamera::parseJSON);
}

void Component::registerComponent(string type, FUNCTION_COMPONENT_PARSE callback) {
	callbackMap[type] = callback;
}

Component* Component::parseJSON(string type, const Value& value) {
	//cout << "Parsing a component of type: " << (callbackMap.find(type) == callbackMap.end() ? "Unknown" : "Success") << endl;
	if (callbackMap.find(type) == callbackMap.end())
		return nullptr;

	return callbackMap[type](value);
}

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

void Component::init() {}
void Component::update() {}
void Component::draw() {}
void Component::onMouseMove() {}
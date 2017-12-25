#include "Component.hpp"
#include "../GameObject.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentMesh.hpp"
#include "../component/ComponentScript.hpp"
#include "../component/ComponentCamera.hpp"
#include "../component/ComponentRigidbody.hpp"
#include <iostream>

map<string, FUNCTION_COMPONENT_PARSE> Component::callbackMap = map<string, FUNCTION_COMPONENT_PARSE>();

void Component::registerAll() {
	registerComponent("ComponentMesh", ComponentMesh::parseJSON);
	registerComponent("ComponentScript", ComponentScript::parseJSON);
	registerComponent("ComponentCamera", ComponentCamera::parseJSON);
	registerComponent("ComponentRigidbody", ComponentRigidbody::parseJSON);
}

void Component::registerComponent(string type, FUNCTION_COMPONENT_PARSE callback) {
	callbackMap[type] = callback;
}

Component* Component::parseJSON(string type, const Value& value) {
	if (callbackMap.find(type) == callbackMap.end())
		return nullptr;

	return callbackMap[type](value);
}

Component::Component() {

}

Component::~Component() {

}

GameObject* Component::getGameObject() {
	return m_gameObject;
}

Component* Component::setGameObject(GameObject* _gameObject) {
	if (m_gameObject == nullptr)
		m_gameObject = _gameObject;
	else
		cerr << "Tried to set a parent GameObject to an already established Component.";

	return this;
}
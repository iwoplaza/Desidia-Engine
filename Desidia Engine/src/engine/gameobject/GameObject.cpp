#include "GameObject.hpp"

GameObject::GameObject(string _name) {
	name = _name;

	componentGroups = map<string, vector<Component*>>();
}

GameObject::~GameObject() {
	for (pair<string, vector<Component*>> p : componentGroups) {
		for (Component* component : p.second) {
			delete component;
		}
	}
}

void GameObject::update() {
	for (pair<string, vector<Component*>> p : componentGroups) {
		for (Component* component : p.second) {
			component->update();
		}
	}
}

void GameObject::draw() {
	for (pair<string, vector<Component*>> p : componentGroups) {
		for (Component* component : p.second) {
			component->draw();
		}
	}
}

GameObject* GameObject::addComponent(Component* _component) {
	if(componentGroups.find(_component->getType()) == componentGroups.end()) {
		componentGroups[_component->getType()] = vector<Component*>();
	}

	_component->setGameObject(this);
	componentGroups[_component->getType()].push_back(_component);
	return this;
}

GameObject* GameObject::markUpdatable() {
	needsUpdates = true;
	return this;
}
#include "ComponentCamera.hpp"
#include <iostream>

using namespace std;

vector<Component*> ComponentCamera::cameras;
Component* ComponentCamera::activeCamera;

ComponentCamera::ComponentCamera() : Component() {

}

void ComponentCamera::activate() {
	activeCamera = this;
}

const char* ComponentCamera::getType() {
	return "ComponentCamera";
}

Component* ComponentCamera::parseJSON(const Value& value) {
	Component* component = new ComponentCamera();
	return component;
}
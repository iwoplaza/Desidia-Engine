#include "ComponentCamera.hpp"
#include "../GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

vector<ComponentCamera*> ComponentCamera::cameras;
ComponentCamera* ComponentCamera::activeCamera;

ComponentCamera::ComponentCamera() : Component() {

}

void ComponentCamera::init() {
	activate();
}

void ComponentCamera::activate() {
	activeCamera = this;
}

glm::mat4 ComponentCamera::getRotationMatrix() {
	return glm::mat4(glm::toMat4(gameObject->getOrientation()));
}

glm::mat4 ComponentCamera::getViewMatrix() {
	glm::mat4 transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(-gameObject->getLocation().x, -gameObject->getLocation().y, -gameObject->getLocation().z));
	return getRotationMatrix() * transform;
}

const char* ComponentCamera::getType() {
	return "ComponentCamera";
}

Component* ComponentCamera::parseJSON(const Value& value) {
	Component* component = new ComponentCamera();
	return component;
}
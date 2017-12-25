#include "ComponentCamera.hpp"
#include "../GameObject.hpp"
#include "../../Engine.hpp"
#include "../../Display.hpp"
#include "../../Base.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

vector<ComponentCamera*> ComponentCamera::cameras;
ComponentCamera* ComponentCamera::activeCamera;

const int ComponentCamera::MODE_ORTHOGRAPHIC = 0;
const int ComponentCamera::MODE_PERSPECTIVE = 1;

ComponentCamera::ComponentCamera()
	: Component() {
	rotationMatrix = glm::mat4();
	viewMatrix = glm::mat4();
	projectionMatrix = glm::mat4();

	fov = 45.0f;
	near_plane = 0.01f;
	far_plane = 100;
	setTargetDimensions(Engine::display->getWidth(), Engine::display->getHeight());

	mode = MODE_PERSPECTIVE;
}

void ComponentCamera::init() {
	activate();
}

void ComponentCamera::activate() {
	activeCamera = this;
	updateProjection();
}

void ComponentCamera::updateProjection() {
	setTargetDimensions(Engine::display->getWidth(), Engine::display->getHeight());
	switch (mode) {
		case MODE_ORTHOGRAPHIC:
			projectionMatrix = glm::ortho(0.0f, (float)targetWidth, 0.0f, (float)targetHeight, near_plane, far_plane);
			break;
		case MODE_PERSPECTIVE:
			projectionMatrix = glm::perspective((float)(fov*PI/180.0f), ratio, near_plane, far_plane);
			break;
	}
}

glm::mat4 ComponentCamera::getRotationMatrix() {
	return glm::mat4(glm::toMat4(m_gameObject->getOrientation()));
}

glm::mat4 ComponentCamera::getViewMatrix() {
	glm::mat4 transform = glm::mat4();
	transform = glm::translate(transform, glm::vec3(-m_gameObject->getLocation().x, -m_gameObject->getLocation().y, -m_gameObject->getLocation().z));
	return glm::inverse(getRotationMatrix()) * transform;
}

glm::mat4 ComponentCamera::getProjectionMatrix() {
	return projectionMatrix;
}

float ComponentCamera::getFOV() { return fov; }
float ComponentCamera::getRatio() { return ratio; }
float ComponentCamera::getNear() { return near_plane; }
float ComponentCamera::getFar() { return far_plane; }

const char* ComponentCamera::getType() {
	return "ComponentCamera";
}

void ComponentCamera::setMode(int _mode) {
	mode = _mode;
	updateProjection();
}

void ComponentCamera::setFOV(float _fov) {
	fov = _fov;
	updateProjection();
}
void ComponentCamera::setTargetDimensions(int _width, int _height) {
	targetWidth = _width;
	targetHeight = _height;
	ratio = (float)targetWidth / targetHeight;
}

Component* ComponentCamera::parseJSON(const Value& value) {
	int mode = MODE_PERSPECTIVE;
	float fov = 45.0f;
	float near_plane = 0.01f;
	float far_plane = 500.0f;
	float left = 0, right = 1, bottom = 0, top = 1;

	if (value.HasMember("mode"))
		mode = value["mode"].GetInt();

	Component* component = new ComponentCamera();
	return component;
}
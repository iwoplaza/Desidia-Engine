#include "Camera.hpp"
#include "GLHelper.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	location = Vector3();
	rotation = Vector3();
	maxPitch = PI*0.5;
	minPitch = -PI*0.5;

	rightVector = Vector3();
	upVector = Vector3();
	forwardVector = Vector3();

	rotationMatrix = glm::mat4();
}

void Camera::setLocation(const Vector3& _location) {
	setLocation(_location.x, _location.y, _location.z);
}

void Camera::setLocation(const float& x, const float& y, const float& z) {
	location.x = x;
	location.y = y;
	location.z = z;
	updateView();
}

void Camera::moveBy(const Vector3& _location) {
	setLocation(location + _location);
}

void Camera::moveForward(float scalar) {
	moveBy(forwardVector * scalar);
}

void Camera::moveRight(float scalar) {
	moveBy(rightVector * scalar);
}

void Camera::setRotation(const Vector3& _rotation) {
	setRotation(_rotation.x, _rotation.y, _rotation.z);
}

void Camera::setRotation(const float& x, const float& y, const float& z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	if (rotation.x < minPitch)
		rotation.x = minPitch;
	if (rotation.x > maxPitch)
		rotation.x = maxPitch;
	updateView();
}

void Camera::rotate(const Vector3& _rotation) {
	setRotation(rotation+_rotation);
}

void Camera::rotate(const float& x, const float& y, const float& z) {
	setRotation(rotation.x + x, rotation.y + y, rotation.z + z);
}

void Camera::updateView() {
	rotationMatrix = glm::mat4();
	rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1, 0, 0));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0, 1, 0));

	GLHelper::viewMatrix = rotationMatrix;
	GLHelper::viewMatrix = glm::translate(GLHelper::viewMatrix, glm::vec3(location.x, location.y, location.z));

	glm::vec4 forward = glm::vec4(0, 0, 1, 1) * rotationMatrix;
	forwardVector.x = forward.x;
	forwardVector.y = forward.y;
	forwardVector.z = forward.z;

	glm::vec4 right = glm::vec4(-1, 0, 0, 1) * rotationMatrix;
	rightVector.x = right.x;
	rightVector.y = right.y;
	rightVector.z = right.z;
}

Vector3 Camera::getLocation() {
	return location;
}

Vector3 Camera::getRotation() {
	return rotation;
}
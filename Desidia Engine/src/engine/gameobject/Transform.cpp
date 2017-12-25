#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

Transform::Transform() {
	m_location = Vector3();
	m_orientation = Quaternion();
	m_scale = Vector3();
	m_matrix = glm::mat4();
}

void Transform::updateMatrix() {
	m_matrix = glm::translate(glm::mat4(), glm::vec3(m_location.x, m_location.y, m_location.z));
	m_matrix = m_matrix * glm::mat4(glm::toMat4(m_orientation));
}

Vector3 Transform::getLocation() const {
	return m_location;
}

Quaternion Transform::getOrientation() const {
	return m_orientation;
}

Vector3 Transform::getScale() const {
	return m_scale;
}

glm::mat4 Transform::getMatrix() const {
	return m_matrix;
}

Vector3 Transform::getForwardVector() const {
	glm::vec3 vector = glm::vec3(0, 0, -1);
	vector = glm::quat(m_orientation) * vector;
	Vector3 vec3 = Vector3(vector.x, vector.y, vector.z);
	return vec3;
}

Vector3 Transform::getRightVector() const {
	glm::vec3 vector = glm::vec3(-1, 0, 0);
	vector = glm::quat(m_orientation) * vector;
	Vector3 vec3 = Vector3(vector.x, vector.y, vector.z);
	return vec3;
}

void Transform::setLocation(const Vector3& _location) {
	m_location = _location;
}

void Transform::setOrientation(const Quaternion& _orientation) {
	m_orientation = _orientation;
}

void Transform::setOrientation(const Vector3& _orientation) {
	m_orientation = Quaternion(_orientation);
}

void Transform::rotate(const Vector3& r) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(r.x, r.y, r.z)));
}

void Transform::rotateX(float _x) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(_x, 0, 0)));
}

void Transform::rotateY(float _y) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(0, _y, 0)));
}

void Transform::rotateZ(float _z) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(0, 0, _z)));
}

void Transform::setScale(const Vector3& _scale) {
	m_scale = _scale;
}
#include "Transform.hpp"
#include "GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

Transform::Transform() {
	m_location = Vector3();
	m_orientation = Quaternion();
	m_scale = Vector3();
	m_matrix = glm::mat4();
	m_parent = nullptr;
}

Transform::Transform(GameObject* _gameObject) : Transform() {
	m_gameObject = _gameObject;
}

void Transform::updateMatrix() {
	m_matrix = glm::mat4();
	m_matrix = glm::translate(m_matrix, glm::vec3(m_location.x, m_location.y, m_location.z));
	m_matrix = m_matrix * glm::mat4(glm::toMat4(m_orientation));
}

GameObject* Transform::getGameObject() const {
	return m_gameObject;
}

Transform* Transform::getParent() const {
	return m_parent;
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

glm::mat4 Transform::getInheritedMatrix() const {
	if (m_parent == nullptr)
		return m_matrix;
	else
		return m_parent->getInheritedMatrix() * m_matrix;
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

void Transform::setParent(Transform* _parent) {
	m_parent = _parent;
}

void Transform::setLocation(const Vector3& _location) {
	m_location = _location;
	updateMatrix();
}

void Transform::setOrientation(const Quaternion& _orientation) {
	m_orientation = _orientation;
	updateMatrix();
}

void Transform::setOrientation(const Vector3& _orientation) {
	m_orientation = Quaternion(_orientation);
	updateMatrix();
}

void Transform::rotate(const Vector3& r) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(r.x, r.y, r.z)));
	updateMatrix();
}

void Transform::rotateX(float _x) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(_x, 0, 0)));
	updateMatrix();
}

void Transform::rotateY(float _y) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(0, _y, 0)));
	updateMatrix();
}

void Transform::rotateZ(float _z) {
	m_orientation = Quaternion(m_orientation * glm::dquat(glm::vec3(0, 0, _z)));
	updateMatrix();
}

void Transform::setScale(const Vector3& _scale) {
	m_scale = _scale;
	updateMatrix();
}
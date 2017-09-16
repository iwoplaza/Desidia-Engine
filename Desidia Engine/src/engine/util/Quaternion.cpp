#include "Quaternion.hpp"
#include "Vector3.hpp"

Quaternion::Quaternion() : glm::dquat() {}
Quaternion::Quaternion(const glm::dquat &quat) : glm::dquat(quat) {}
Quaternion::Quaternion(Vector3 vec) : glm::dquat(glm::vec3(vec.x, vec.y, vec.z)) {}
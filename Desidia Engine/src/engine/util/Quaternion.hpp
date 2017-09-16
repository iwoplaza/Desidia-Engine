#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Vector3;

class Quaternion : public glm::dquat{
	public:
		Quaternion();
		Quaternion(const glm::dquat &quat);
		Quaternion(Vector3);
};
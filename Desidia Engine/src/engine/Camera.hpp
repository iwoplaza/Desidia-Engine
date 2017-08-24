#pragma once
#include "Vector3.hpp"
#include <glm\glm.hpp>
#define PI 3.14159265359

class Camera {
	protected:
		Vector3 location;
		Vector3 rotation;
		Vector3 rightVector;
		Vector3 upVector;
		Vector3 forwardVector;

		float maxPitch;
		float minPitch;

		glm::mat4 rotationMatrix;
	public:
		Camera();

		void setLocation(const Vector3& location);
		void setLocation(const float& x, const float& y, const float& z);
		void moveBy(const Vector3& location);
		void moveRight(float scalar);
		void moveForward(float scalar);
		void setRotation(const Vector3& rotation);
		void setRotation(const float& x, const float& y, const float& z);
		void rotate(const Vector3& rotation);
		void rotate(const float& x, const float& y, const float& z);
		void updateView();

		Vector3 getLocation();
		Vector3 getRotation();
};
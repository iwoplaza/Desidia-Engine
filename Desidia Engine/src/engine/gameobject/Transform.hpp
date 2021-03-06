#pragma once

#include "../util/Vector3.hpp"
#include "../util/Quaternion.hpp"

class GameObject;

class Transform {
	protected:
		Vector3 m_location;
		Quaternion m_orientation;
		Vector3 m_scale;
		glm::mat4 m_matrix;

		GameObject* m_gameObject;
		Transform* m_parent;
	public:
		Transform();
		Transform(GameObject* _gameObject);

		void updateMatrix();

		GameObject* getGameObject() const;
		Transform* getParent() const;
		Vector3 getLocation() const;
		Quaternion getOrientation() const;
		Vector3 getScale() const;
		glm::mat4 getMatrix() const;
		glm::mat4 getInheritedMatrix() const;
		Vector3 getForwardVector() const;
		Vector3 getRightVector() const;
		void setParent(Transform* _parent);
		void setLocation(const Vector3& _location);
		void setOrientation(const Quaternion& _orientation);
		void setOrientation(const Vector3& _orientation);
		void rotate(const Vector3& _rotation);
		void rotateX(float _x);
		void rotateY(float _y);
		void rotateZ(float _z);
		void setScale(const Vector3& _scale);
};
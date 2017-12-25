#pragma once

#include "../util/Vector3.hpp"
#include <glm/glm.hpp>

class PhysicsSpace;
class Collider;

class PhysicsBody {
	protected:
		Vector3 m_location;
		Vector3 m_velocity;
		float m_mass;
		float m_gravityInfluence;

		Collider* m_collider;
		glm::mat4 m_transform;

		PhysicsSpace* m_physicsSpace;
	public:
		PhysicsBody(PhysicsSpace*, Vector3, float, Collider*);
		~PhysicsBody();

		void update();
		void resolve(PhysicsBody* other);
		void addForce(Vector3 _force);
		void updateTransform();
		void drawGizmos();
		Collider* getCollider();
		glm::mat4 getTransform();
		Vector3 getLocation();
		Vector3 getVelocity();
		void setLocation(Vector3 _location);
		void setVelocity(Vector3 _velocity);
};
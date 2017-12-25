#pragma once

#include "Component.hpp"
#include "../../util/Vector3.hpp"
#include <string>

class Collider;
class PhysicsBody;

class ComponentRigidbody : public Component {
	protected:
		float m_mass;
		Collider* m_collider;
		PhysicsBody* m_physicsBody;
	public:
		ComponentRigidbody(float, Collider*);
		~ComponentRigidbody();

		void init();
		void update();
		void addForce(Vector3 _force);
		void setVelocity(Vector3 _velocity);
		PhysicsBody* getPhysicsBody();
		Vector3 getVelocity();
		const char* getType();

		static Component* parseJSON(const Value&);
};
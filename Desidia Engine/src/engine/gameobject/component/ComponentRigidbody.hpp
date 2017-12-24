#pragma once

#include "Component.hpp"
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

		void init();
		const char* getType();

		static Component* parseJSON(const Value&);
};
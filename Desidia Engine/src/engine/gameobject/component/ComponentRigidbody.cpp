#include "ComponentRigidbody.hpp"
#include "../GameObject.hpp"
#include "../../scene/Scene.hpp"
#include "../../physics/PhysicsSpace.hpp"
#include "../../physics/PhysicsBody.hpp"
#include "../../physics/collider/Collider.hpp"
#include <iostream>

ComponentRigidbody::ComponentRigidbody(float _mass, Collider* _collider) : Component() {
	m_mass = _mass;
	m_collider = _collider;
}

ComponentRigidbody::~ComponentRigidbody() {
	delete m_physicsBody;
}

void ComponentRigidbody::init() {
	PhysicsSpace* physicsSpace = Scene::current->getPhysicsSpace();
	m_physicsBody = new PhysicsBody(physicsSpace, m_gameObject->getLocation(), m_mass, m_collider);
}

void ComponentRigidbody::update() {
	m_gameObject->setLocation(m_physicsBody->getLocation());
}

void ComponentRigidbody::addForce(Vector3 _force) {
	m_physicsBody->addForce(_force);
}

void ComponentRigidbody::setVelocity(Vector3 _velocity) {
	m_physicsBody->setVelocity(_velocity);
}

PhysicsBody* ComponentRigidbody::getPhysicsBody() {
	return m_physicsBody;
}

Vector3 ComponentRigidbody::getVelocity() {
	return m_physicsBody->getVelocity();
}

const char* ComponentRigidbody::getType() {
	return "ComponentRigidbody";
}

Component* ComponentRigidbody::parseJSON(const Value& value) {
	if (!value.HasMember("collider") || !value["collider"].HasMember("type")) {
		std::cerr << "[SceneLoader] Necessary parameters weren't specified for a ComponentRigidbody. (collider, collider.type)" << endl;
		return nullptr;
	}

	float mass = 1;
	if (value.HasMember("mass"))
		mass = value["mass"].GetFloat();

	const Value& colliderNode = value["collider"];
	std::string colliderType = colliderNode["type"].GetString();
	Collider* collider = Collider::parseJSON(colliderType, colliderNode);

	Component* component = new ComponentRigidbody(mass, collider);
	return component;
}
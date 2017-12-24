#include "PhysicsSpace.hpp"
#include "PhysicsBody.hpp"
#include "collider/PolygonCollider.hpp"
#include "collider/MeshCollider.hpp"
#include "collider/SphereCollider.hpp"
#include "../scene/Scene.hpp"
#include "../gameobject/GameObject.hpp"
#include "../rendering/GLHelper.hpp"
#include "../util/Time.hpp"
#include "../Resources.hpp"
#include <algorithm>

Material gizmoMaterial = Material("_native/shaders/shadeless.shader", Color(0.2, 1, 0.5));

PhysicsSpace::PhysicsSpace() {
	m_physicsBodies = std::vector<PhysicsBody*>();
	m_gravity = Vector3(0, -0.1f, 0);
	m_timer = 0;
	m_stepSize = 1.0F;
}

void PhysicsSpace::init() {
	m_physicsBodies = {};
	m_physicsBodies.push_back(new PhysicsBody(this, Vector3(0, 0, 0), 0, new MeshCollider(Resources::MODEL["models/cube.obj"]->getMeshData())));
	m_physicsBodies.push_back(new PhysicsBody(this, Vector3(0, 1, 2), 1, new SphereCollider(Vector3(0, 0, 0), 1)));
}

void PhysicsSpace::update() {
	m_timer += Time::delta;

	while (m_timer >= m_stepSize * Time::fixedDelta) {
		simulate();
		m_timer -= m_stepSize * Time::delta;
	}
}

void PhysicsSpace::simulate() {
	GameObject* gameObject = Scene::current->getGameObject("character");
	Vector3 velocity = m_physicsBodies[1]->getVelocity();
	velocity.x += gameObject->getLocation().x - m_physicsBodies[1]->getLocation().x;
	velocity.z += gameObject->getLocation().z - m_physicsBodies[1]->getLocation().z;
	float dampen = 0.7f;
	velocity.x *= dampen;
	velocity.z *= dampen;
	m_physicsBodies[1]->setVelocity(velocity);

	for (PhysicsBody* physicsBody : m_physicsBodies) {
		physicsBody->update();
	}
}

void PhysicsSpace::drawGizmos() {
	for (PhysicsBody* physicsBody : m_physicsBodies) {
		physicsBody->drawGizmos();
	}
	
	/*MeshCollider* meshCollider = (MeshCollider*)physicsBodies[0]->getCollider();
	SphereCollider* sphere = (SphereCollider*)physicsBodies[1]->getCollider();

	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (PolygonCollider polygon : (meshCollider->getPolygons())) {
		Vector3 point = physicsBodies[1]->getLocation() + sphere->getOrigin();
		Vector3 contactPoint;
		float minimumDistance = pointToPolygonDistance(point, &polygon, contactPoint);

		polygon.getProjectionMesh()->update({ {
				Vertex(contactPoint),
				Vertex(point)
			},{ 0, 1, 0 } });

		GLHelper::saveState();
		//GLHelper::translate(contactPoint);
		float normalScale = minimumDistance;
		//GLHelper::scale(normalScale, normalScale, normalScale);

		gizmoMaterial.use();
		polygon.getProjectionMesh()->draw();

		GLHelper::loadState();
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);*/
}

Vector3 PhysicsSpace::getGravity() {
	return m_gravity;
}

std::vector<PhysicsBody*> PhysicsSpace::getBodies() {
	return m_physicsBodies;
}

void PhysicsSpace::setGravity(Vector3 _gravity) {
	m_gravity = _gravity;
}
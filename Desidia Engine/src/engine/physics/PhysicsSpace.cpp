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
	m_gravity = Vector3(0, -1.0f, 0);
	m_timer = 0;
	m_stepSize = 0.01F;
}

void PhysicsSpace::init() {
}

void PhysicsSpace::update() {
	m_timer += Time::delta;

	while (m_timer >= m_stepSize) {
		simulate();
		m_timer -= m_stepSize;
	}
}

void PhysicsSpace::addBody(PhysicsBody* _physicsBody) {
	m_physicsBodies.push_back(_physicsBody);
}

void PhysicsSpace::removeBody(PhysicsBody* _physicsBody) {
	std::vector<PhysicsBody*>::iterator it = m_physicsBodies.begin();
	while (it != m_physicsBodies.end())
		if (*it == _physicsBody)
			it = m_physicsBodies.erase(it);
		else
			it++;
}

void PhysicsSpace::simulate() {
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

float PhysicsSpace::getPartialTicks() {
	return m_timer / m_stepSize;
}

void PhysicsSpace::setGravity(Vector3 _gravity) {
	m_gravity = _gravity;
}
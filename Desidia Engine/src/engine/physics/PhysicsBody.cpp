#include "PhysicsBody.hpp"
#include "PhysicsSpace.hpp"
#include "PhysicsUtils.hpp"
#include "collider/Collider.hpp"
#include "collider/MeshCollider.hpp"
#include "collider/SphereCollider.hpp"
#include "../rendering/geometry/Polygon.hpp"
#include "../rendering/GLHelper.hpp"
#include "../gameobject/component/Component.hpp"
#include "../util/Time.hpp"
#include <glm/gtc/matrix_transform.hpp>

PhysicsBody::PhysicsBody(PhysicsSpace* _physicsSpace, Vector3 _location, float _mass, Collider* _collider) {
	m_physicsSpace = _physicsSpace;
	m_location = _location;
	m_collider = _collider;
	m_velocity = Vector3();
	m_mass = _mass;
	m_gravityInfluence = 1.0F;

	updateTransform();
}

void PhysicsBody::update() {
	m_velocity += m_physicsSpace->getGravity() * (m_mass * m_gravityInfluence);
	m_location += m_velocity * Time::fixedDelta;

	vector<PhysicsBody*> bodies = m_physicsSpace->getBodies();
	for (PhysicsBody* body : bodies) {
		if(body != this)
			resolve(body);
	}

	cout << m_velocity << endl;

	updateTransform();
}

void PhysicsBody::updateTransform() {
	m_transform = glm::translate(glm::mat4(), glm::vec3(m_location.x, m_location.y, m_location.z));
}

void PhysicsBody::resolve(PhysicsBody* other) {
	Collider* otherCollider = other->getCollider();

	if (m_collider->getTypeName() == "SphereCollider")
	if (otherCollider->getTypeName() == "MeshCollider") {
		SphereCollider* sphere = (SphereCollider*)m_collider;
		MeshCollider* meshCollider = (MeshCollider*) otherCollider;
		float minimalDistance = 0;
		Vector3 nearest = Vector3();
		bool setMinimal = false;
		Vector3 point = m_location + sphere->getOrigin();

		for (Polygon polygon : meshCollider->getPolygons()) {
			Vector3 projection;
			float distance = PhysicsUtils::pointToPolygonDistance(point, &polygon, projection);
			if (abs(distance) < abs(minimalDistance) || !setMinimal) {
				minimalDistance = distance;
				nearest = projection;
				setMinimal = true;
			}
		}

		if (abs(minimalDistance) < sphere->getRadius()) {
			float penetrationDepth = sphere->getRadius() - abs(minimalDistance);
			if (minimalDistance < 0)
				penetrationDepth *= -1;
			Vector3 penetration = (point - nearest) * penetrationDepth;

			m_location += penetration;
			m_velocity += penetration/Time::fixedDelta;
		}
		/*
		*	float pointToPlane(Vector3f point, Plane plane) {
		*		float distance = dot( plane.normal, (point - plane.point) );
		*		Vector3 contactPoint = point - plane.normal * distance;
		*
		*		return distance;
		*	}
		*/
	}
}

Collider* PhysicsBody::getCollider() {
	return m_collider;
}

Vector3 PhysicsBody::getLocation() {
	return m_location;
}

Vector3 PhysicsBody::getVelocity() {
	return m_velocity;
}

void PhysicsBody::setLocation(Vector3 _location) {
	m_location = _location;
	updateTransform();
}

void PhysicsBody::setVelocity(Vector3 _velocity) {
	m_velocity = _velocity;
}

void PhysicsBody::drawGizmos() {
	GLHelper::saveState();
	GLHelper::transform(m_transform);
	
	m_collider->drawGizmos();

	GLHelper::loadState();
}
#include "SphereCollider.hpp"
#include "../../Resources.hpp"
#include "../../rendering/GLHelper.hpp"
#include "../../util/Color.hpp"

SphereCollider::SphereCollider(Vector3 _origin, float _radius) {
	m_origin = _origin;
	m_radius = _radius;
	m_material = Material("_native/shaders/shadeless.shader", Color(0.4, 0.7, 1.0));
}

const Vector3& SphereCollider::getOrigin() {
	return m_origin;
}

const float& SphereCollider::getRadius() {
	return m_radius;
}

const char* SphereCollider::getTypeName() {
	return "SphereCollider";
}

void SphereCollider::drawGizmos() {
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLHelper::saveState();
	GLHelper::translate(m_origin);
	GLHelper::scale(m_radius, m_radius, m_radius);

	m_material.use();
	Resources::MODEL["_native/models/icosphere.obj"]->draw();

	GLHelper::loadState();

	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Collider* SphereCollider::parseJSON(const Value& value) {
	if (!value.HasMember("origin") || !value.HasMember("radius")) {
		std::cerr << "[Collider] Necessary parameters weren't specified for a SphereCollider. (origin, radius)" << endl;
		return nullptr;
	}

	const Value& locationNode = value["origin"];
	Vector3 origin(locationNode.GetArray()[0].GetFloat(), locationNode.GetArray()[1].GetFloat(), locationNode.GetArray()[2].GetFloat());
	float radius = value["radius"].GetFloat();

	Collider* component = new SphereCollider(origin, radius);
	return component;
}
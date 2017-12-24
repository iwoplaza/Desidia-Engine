#pragma once

#include "Collider.hpp"
#include "../../rendering/geometry/Mesh.hpp"
#include "../../util/Vector3.hpp"
#include "../../rendering/material/Material.hpp"

class SphereCollider : public Collider {
	protected:
		Vector3 m_origin;
		float m_radius;
		Material m_material;
	public:
		SphereCollider(Vector3 _origin, float _radius);

		const Vector3& getOrigin();
		const float& getRadius();

		// Overriden
		const char* getTypeName();
		void drawGizmos();

		static Collider* SphereCollider::parseJSON(const Value& value);
};
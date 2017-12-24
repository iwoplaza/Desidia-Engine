#pragma once

#include "Collider.hpp"
#include "../../rendering/geometry/Mesh.hpp"
#include "../../rendering/geometry/DynamicMesh.hpp"
#include "../../rendering/geometry/Polygon.hpp"
#include "../../util/Vector3.hpp"
#include "../../rendering/material/Material.hpp"

class PolygonCollider : public Collider {
	protected:
		Polygon m_polygon;

		// Used for debugging
		Mesh* m_gizmoMesh;
		Mesh* m_normalLineMesh;
		DynamicMesh* m_projectionMesh;
		Material m_material;
	public:
		PolygonCollider(Polygon _polygon);
		PolygonCollider(Vector3* _points);

		Vector3* getPoints();
		const Vector3& getNormal();

		Mesh* getNormalLineMesh();
		DynamicMesh* getProjectionMesh();

		// Overriden
		const char* getTypeName();
		void drawGizmos();

		static Collider* parseJSON(const Value& value);
};
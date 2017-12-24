#pragma once

#include "Collider.hpp"
#include "../../rendering/geometry/Mesh.hpp"
#include "../../rendering/geometry/Polygon.hpp"
#include "../../util/Vector3.hpp"

class MeshCollider : public Collider {
	protected:
		std::vector<Polygon> m_polygons;
	public:
		MeshCollider(MeshData meshData);
		MeshCollider(std::vector<Polygon> _polygons);
		MeshCollider();

		std::vector<Polygon> getPolygons();

		// Overriden
		const char* getTypeName();
		void drawGizmos();

		static Collider* parseJSON(const Value& value);
};
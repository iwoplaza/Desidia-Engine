#include "MeshCollider.hpp"
#include "PolygonCollider.hpp"
#include "../../Resources.hpp"

MeshCollider::MeshCollider(std::vector<Polygon> _polygons) {
	m_polygons = _polygons;
}
MeshCollider::MeshCollider() : MeshCollider(std::vector<Polygon>()) {}
MeshCollider::MeshCollider(MeshData meshData) : MeshCollider() {
	m_polygons.reserve(meshData.indices.size() / 3);
	for (int i = 0; i < meshData.indices.size() / 3; i++) {
		m_polygons.emplace_back(new Vector3[3]{
			meshData.vertices[meshData.indices[i * 3]].getLocation(),
			meshData.vertices[meshData.indices[i * 3 + 1]].getLocation(),
			meshData.vertices[meshData.indices[i * 3 + 2]].getLocation()
		});
	}
}

void MeshCollider::drawGizmos() {
	for (PolygonCollider polygon : m_polygons) {
		polygon.drawGizmos();
	}
}

std::vector<Polygon> MeshCollider::getPolygons() {
	return m_polygons;
}

const char* MeshCollider::getTypeName() {
	return "MeshCollider";
}

Collider* MeshCollider::parseJSON(const Value& value) {
	if (!value.HasMember("model")) {
		std::cerr << "[Collider] Necessary parameters weren't specified for a MeshCollider. (model)" << endl;
		return nullptr;
	}

	std::string model = value["model"].GetString();
	
	Collider* component = new MeshCollider(Resources::MODEL[model]->getMeshData());
	return component;
}
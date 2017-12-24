#include "PolygonCollider.hpp"
#include "../../rendering/GLHelper.hpp"
#include "../../rendering/geometry/Vertex.hpp"

PolygonCollider::PolygonCollider(Polygon _polygon) {
	m_polygon = _polygon;

	/*m_gizmoMesh = new Mesh();
	m_gizmoMesh->fillOut({ {
		Vertex(m_polygon.getPoints()[0]),
		Vertex(m_polygon.getPoints()[1]),
		Vertex(m_polygon.getPoints()[2])
	}, { 0, 1, 2 } });

	m_normalLineMesh = new Mesh();
	m_normalLineMesh->fillOut({ {
		Vertex(0, 0, 0),
		Vertex(m_polygon.getNormal())
	},{ 0, 1, 0 } });

	m_projectionMesh = new DynamicMesh();
	m_projectionMesh->fillOut({ {
		Vertex(0, 0, 0),
		Vertex(1, 1, 1)
	},{ 0, 1, 0 } });*/
	
	m_material = Material("_native/shaders/shadeless.shader", Color(1, 0.7, 0.3));
}
PolygonCollider::PolygonCollider(Vector3* _points) : PolygonCollider(Polygon(_points)) {}

Vector3* PolygonCollider::getPoints() {
	return m_polygon.getPoints();
}

const Vector3& PolygonCollider::getNormal() {
	return m_polygon.getNormal();
}

const char* PolygonCollider::getTypeName() {
	return "PolygonCollider";
}

Mesh* PolygonCollider::getNormalLineMesh() {
	return m_normalLineMesh;
}

DynamicMesh* PolygonCollider::getProjectionMesh() {
	return m_projectionMesh;
}

void PolygonCollider::drawGizmos() {
	return;

	Vector3 center = (m_polygon.getPoints()[0] + m_polygon.getPoints()[1] + m_polygon.getPoints()[2]) / 3.0f;
	float normalScale = 0.2F;

	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_gizmoMesh->draw();

	GLHelper::saveState();
	GLHelper::translate(center);
	GLHelper::scale(normalScale, normalScale, normalScale);

	m_material.use();
	m_normalLineMesh->draw();

	GLHelper::loadState();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
}

Collider* PolygonCollider::parseJSON(const Value& value) {
	if (!value.HasMember("origin") || !value.HasMember("radius")) {
		std::cerr << "[Collider] Necessary parameters weren't specified for a PolygonCollider. (origin, radius)" << endl;
		return nullptr;
	}

	const Value& pointsNode = value["points"];
	GenericArray<true, Value> some = pointsNode.GetArray();
	Vector3 a(pointsNode.GetArray()[0].GetArray()[0].GetFloat(),
			  pointsNode.GetArray()[0].GetArray()[1].GetFloat(),
			  pointsNode.GetArray()[0].GetArray()[2].GetFloat());
	Vector3 b(pointsNode.GetArray()[1].GetArray()[0].GetFloat(),
			  pointsNode.GetArray()[1].GetArray()[1].GetFloat(),
			  pointsNode.GetArray()[1].GetArray()[2].GetFloat());
	Vector3 c(pointsNode.GetArray()[2].GetArray()[0].GetFloat(),
			  pointsNode.GetArray()[2].GetArray()[1].GetFloat(),
			  pointsNode.GetArray()[2].GetArray()[2].GetFloat());

	Collider* component = new PolygonCollider(Polygon(new Vector3[3]{ a, b, c }));
	return component;
}
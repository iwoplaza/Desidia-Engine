#include "Polygon.hpp"

Polygon::Polygon() {
	m_points = {};
}

Polygon::Polygon(Vector3* _points) {
	m_points = _points;
	Vector3 line1 = m_points[0] - m_points[1];
	Vector3 line2 = m_points[0] - m_points[2];
	m_normal = line1.cross(line2).normalize();
}

Vector3* Polygon::getPoints() {
	return m_points;
}

Vector3 Polygon::getNormal() {
	return m_normal;
}
#include "PhysicsUtils.hpp"

bool PhysicsUtils::isOnSameSide(Vector3 point, Vector3 reference, Vector3 a, Vector3 b) {
	Vector3 cp1 = (b - a).cross(point - a);
	Vector3 cp2 = (b - a).cross(reference - a);
	return (cp1.dot(cp2) >= 0);
}

bool PhysicsUtils::isPointInTriangle(Vector3 point, Vector3* points) {
	if (isOnSameSide(point, points[0], points[1], points[2]) &&
		isOnSameSide(point, points[1], points[0], points[2]) &&
		isOnSameSide(point, points[2], points[0], points[1]))
		return true;
	else
		return false;
}

float PhysicsUtils::pointToLineDistance(Vector3 p, Vector3 a, Vector3 b, Vector3 &projection) {
	const float l2 = (a - b).lengthSquared();
	projection = a;
	if (l2 == 0.0)
		return (p - a).lengthSquared();
	const float t = std::max(0.0f, std::min(1.0f, (p - a).dot(b - a) / l2));
	projection = a + (b - a) * t;
	return (p - projection).length();
}

float PhysicsUtils::pointToPolygonDistance(Vector3 point, Polygon* polygon, Vector3& contactPoint) {
	Vector3* points = polygon->getPoints();
	float minimumDistance = Vector3(polygon->getNormal()).dot(point - points[0]);
	contactPoint = point - Vector3(polygon->getNormal()) * minimumDistance;

	if (!isPointInTriangle(contactPoint, polygon->getPoints())) {
		float distance;

		Vector3 projection = Vector3();
		distance = pointToLineDistance(point, points[0], points[1], projection);
		minimumDistance = distance;
		contactPoint = projection;

		distance = pointToLineDistance(point, points[1], points[2], projection);
		if (abs(distance) < abs(minimumDistance)) {
			minimumDistance = distance;
			contactPoint = projection;
		}
		distance = pointToLineDistance(point, points[0], points[2], projection);
		if (abs(distance) < abs(minimumDistance)) {
			minimumDistance = distance;
			contactPoint = projection;
		}
	}

	return minimumDistance;
}
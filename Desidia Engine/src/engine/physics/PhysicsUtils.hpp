#pragma once

#include "../util/Vector3.hpp"
#include "../rendering/geometry/Polygon.hpp"
#include <algorithm>

namespace PhysicsUtils {
	bool isOnSameSide(Vector3 point, Vector3 reference, Vector3 a, Vector3 b);
	bool isPointInTriangle(Vector3 point, Vector3* points);
	float pointToLineDistance(Vector3 p, Vector3 a, Vector3 b, Vector3 &projection);
	float pointToPolygonDistance(Vector3 point, Polygon* polygon, Vector3& contactPoint);
}
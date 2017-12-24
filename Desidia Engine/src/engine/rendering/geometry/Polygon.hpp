#pragma once

#include "../../util/Vector3.hpp"

class Polygon {
	protected:
		Vector3* m_points;
		Vector3 m_normal;

	public:
		Polygon();
		Polygon(Vector3* _points);

		Vector3* getPoints();
		Vector3 getNormal();
};
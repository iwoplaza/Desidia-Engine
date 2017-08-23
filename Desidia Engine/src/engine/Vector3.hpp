#pragma once

#include <iostream>

using namespace std;

class Vector3 {
	public:
		float x, y, z;

		Vector3()
			: x(0), y(0), z(0) {}
		Vector3(float _x, float _y, float _z)
			: x(_x), y(_y), z(_z) {}

		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(const Vector3& v);
		Vector3& operator/=(const Vector3& v);
		Vector3& operator*=(const float& s);
		Vector3& operator/=(const float& s);
		friend Vector3 operator+(Vector3 v1, const Vector3& v2);
		friend Vector3 operator-(Vector3 v1, const Vector3& v2);
		friend Vector3 operator*(Vector3 v1, const Vector3& v2);
		friend Vector3 operator/(Vector3 v1, const Vector3& v2);
		friend Vector3 operator*(Vector3 v, const float& s);
		friend Vector3 operator/(Vector3 v, const float& s);
		friend ostream& operator<<(ostream& os, const Vector3& v);
		friend istream& operator>>(ostream& is, Vector3& v);
};
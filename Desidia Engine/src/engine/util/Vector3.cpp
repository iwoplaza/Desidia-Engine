#pragma once

#include "Vector3.hpp"

Vector3& Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v) {
	if (v.x == 0 || v.y == 0 || v.z == 0)
		return Vector3(0, 0, 0);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3& Vector3::operator*=(const float& s) {
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(const float& s) {
	if (s == 0)
		return Vector3(0, 0, 0);
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector3 operator+(Vector3 v1, const Vector3& v2) {
	v1 += v2;
	return v1;
}

Vector3 operator-(Vector3 v1, const Vector3& v2) {
	v1 -= v2;
	return v1;
}

Vector3 operator*(Vector3 v1, const Vector3& v2) {
	v1 *= v2;
	return v1;
}

Vector3 operator/(Vector3 v1, const Vector3& v2) {
	v1 /= v2;
	return v1;
}

Vector3 operator*(Vector3 v, const float& s) {
	v *= s;
	return v;
}

Vector3 operator/(Vector3 v, const float& s) {
	v /= s;
	return v;
}

ostream& operator<<(ostream& os, const Vector3& v) {
	os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
	return os;
}

istream& operator>>(istream& is, Vector3& v) {
	is >> v.x >> v.y >> v.z;
	return is;
}
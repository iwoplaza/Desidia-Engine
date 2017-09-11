#pragma once

#include "Vector3.hpp"

float Vector3::length() {
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::normalize() {
	float len = length();
	if (len == 0)
		return Vector3(0, 0, 0);
	return Vector3(x/len, y/len, z/len);
}

Vector3 Vector3::cross(const Vector3& v) {
	return Vector3(y*v.z - z*v.y, 
				   z*v.x - x*v.z,
				   x*v.y - y*v.x);
}

float Vector3::dot(const Vector3& v) {
	return x*v.x + y*v.y;
}

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
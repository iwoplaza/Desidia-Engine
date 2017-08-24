#pragma once

#include "Vector2.hpp"

Vector2& Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& v) {
	if (v.x == 0 || v.y == 0)
		return Vector2(0, 0);
	x /= v.x;
	y /= v.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& s) {
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(const float& s) {
	if (s == 0)
		return Vector2(0, 0);
	x /= s;
	y /= s;
	return *this;
}

Vector2 operator+(Vector2 v1, const Vector2& v2) {
	v1 += v2;
	return v1;
}

Vector2 operator-(Vector2 v1, const Vector2& v2) {
	v1 -= v2;
	return v1;
}

Vector2 operator*(Vector2 v1, const Vector2& v2) {
	v1 *= v2;
	return v1;
}

Vector2 operator/(Vector2 v1, const Vector2& v2) {
	v1 /= v2;
	return v1;
}

Vector2 operator*(Vector2 v, const float& s) {
	v *= s;
	return v;
}

Vector2 operator/(Vector2 v, const float& s) {
	v /= s;
	return v;
}

ostream& operator<<(ostream& os, const Vector2& v) {
	os << "{ " << v.x << ", " << v.y << " }";
	return os;
}

istream& operator>>(istream& is, Vector2& v) {
	is >> v.x >> v.y;
	return is;
}
#pragma once

#include <iostream>

using namespace std;

class Vector2 {
public:
	float x, y;

	Vector2()
		: x(0), y(0) {}
	Vector2(float _x, float _y)
		: x(_x), y(_y) {}

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(const Vector2& v);
	Vector2& operator/=(const Vector2& v);
	Vector2& operator*=(const float& s);
	Vector2& operator/=(const float& s);
	friend Vector2 operator+(Vector2 v1, const Vector2& v2);
	friend Vector2 operator-(Vector2 v1, const Vector2& v2);
	friend Vector2 operator*(Vector2 v1, const Vector2& v2);
	friend Vector2 operator/(Vector2 v1, const Vector2& v2);
	friend Vector2 operator*(Vector2 v, const float& s);
	friend Vector2 operator/(Vector2 v, const float& s);
	friend ostream& operator<<(ostream& os, const Vector2& v);
	friend istream& operator>>(istream& is, Vector2& v);
};
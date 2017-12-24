#pragma once

#include <tuple>

class Vector2;
class Vector3;

struct Vertex {
	float x, y, z;		// Position
	float nx, ny, nz;	// Normal
	float u, v;			// UV Coordinates
	float tx, ty, tz;	// Tangent
	float bx, by, bz;	// Bitangent

	Vertex();
	Vertex(float _x, float _y, float _z);
	Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz);
	Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v);
	Vertex(Vector3 position);
	Vertex(Vector3 position, Vector3 normal, Vector2 texCoord);

	void addTangent(Vector3);
	void addBitangent(Vector3);

	Vector3 getLocation();

	friend bool operator== (const Vertex& lhs, const Vertex& rhs);
};
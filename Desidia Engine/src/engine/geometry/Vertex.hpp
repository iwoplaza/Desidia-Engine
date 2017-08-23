#pragma once

struct Vertex {
	float x, y, z;
	float nx, ny, nz;
	float u, v;

	Vertex()
		: x(0), y(0), z(0), nx(0), ny(0), nz(0), u(0), v(0) {}
	Vertex(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), nx(0), ny(0), nz(0), u(0), v(0) {}
	Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz)
		: x(_x), y(_y), z(_z), nx(_nx), ny(_ny), nz(_nz), u(0), v(0) {}
	Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
		: x(_x), y(_y), z(_z), nx(_nx), ny(_ny), nz(_nz), u(_u), v(_v) {}
};
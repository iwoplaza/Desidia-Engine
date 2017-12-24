#include "Vertex.hpp"
#include "../../util/Vector2.hpp"
#include "../../util/Vector3.hpp"

Vertex::Vertex()
	: x(0), y(0), z(0), nx(0), ny(0), nz(0), u(0), v(0), tx(0), ty(0), tz(0), bx(0), by(0), bz(0) {}
Vertex::Vertex(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z), nx(0), ny(0), nz(0), u(0), v(0), tx(0), ty(0), tz(0), bx(0), by(0), bz(0) {}
Vertex::Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz)
	: x(_x), y(_y), z(_z), nx(_nx), ny(_ny), nz(_nz), u(0), v(0), tx(0), ty(0), tz(0), bx(0), by(0), bz(0) {}
Vertex::Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
	: x(_x), y(_y), z(_z), nx(_nx), ny(_ny), nz(_nz), u(_u), v(_v), tx(0), ty(0), tz(0), bx(0), by(0), bz(0) {}
Vertex::Vertex(Vector3 p)
	: x(p.x), y(p.y), z(p.z), nx(0), ny(0), nz(0), u(0), v(0), tx(0), ty(0), tz(0), bx(0), by(0), bz(0) {}
Vertex::Vertex(Vector3 p, Vector3 n, Vector2 t)
	: x(p.x), y(p.y), z(p.z), nx(n.x), ny(n.y), nz(n.z), u(t.x), v(t.y), tx(0), ty(0), tz(0), bx(0), by(0), bz(0) {}

void Vertex::addTangent(Vector3 v) {
	tx += v.x;
	ty += v.y;
	tz += v.z;
}

void Vertex::addBitangent(Vector3 v) {
	bx += v.x;
	by += v.y;
	bz += v.z;
}

Vector3 Vertex::getLocation() {
	return Vector3(x, y, z);
}

bool operator== (const Vertex& lhs, const Vertex& rhs) {
	return	lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z &&
			lhs.nx == rhs.nx && lhs.ny == rhs.ny && lhs.nz == rhs.nz &&
			lhs.u == rhs.u && lhs.v == rhs.v &&
			lhs.tx == rhs.tx && lhs.ty == rhs.ty && lhs.tz == rhs.tz &&
			lhs.bx == rhs.bx && lhs.by == rhs.by && lhs.bz == rhs.bz;
}
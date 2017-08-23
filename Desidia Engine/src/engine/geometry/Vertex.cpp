#include "Vertex.hpp"
#include "../Vector2.hpp"
#include "../Vector3.hpp"

Vertex::Vertex(Vector3 p, Vector3 n, Vector2 t)
	: x(p.x), y(p.y), z(p.z), nx(n.x), ny(n.y), nz(n.z), u(t.x), v(t.y) {}
#pragma once

#include <vector>

struct Vertex;

struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};
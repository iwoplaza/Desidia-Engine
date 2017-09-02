#pragma once

#include <vector>
#include "Vertex.hpp"
#include <GL/glew.h>

using namespace std;

class Mesh {
	public:
		Mesh();
		~Mesh();

		GLuint vaoID;
		GLuint vboIndicesID;
		GLuint vboVerticesID;
		int totalIndices;

		void draw();

		void fillOut(vector<Vertex> _vertices, vector<GLuint> _indices);
};
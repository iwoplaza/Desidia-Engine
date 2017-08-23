#pragma once

#include <vector>
#include "Vertex.hpp"
#include <GL/glew.h>

using namespace std;

class Mesh {
	public:
		Mesh();
		~Mesh();

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		GLuint vaoID;
		GLuint vboPositionsID;
		GLuint vboIndicesID;
		GLuint vboTexCoordsID;
		GLuint vboNormalsID;

		void draw();

		void fillOut(vector<Vertex> _vertices, vector<GLuint> _indices);
		void fillPositionBuffer(GLfloat* buffer);
		void fillIndexBuffer(GLuint* buffer);
		void fillTexCoordBuffer(GLfloat* buffer);
		void fillNormalBuffer(GLfloat* buffer);
};
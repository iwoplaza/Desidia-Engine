#include "Mesh.hpp"
#include "../shader/ShaderManager.hpp"
#include "../GLHelper.hpp"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

Mesh::Mesh() {
	totalIndices = 0;
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);
}

void Mesh::draw() {
	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, nx));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, u));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, tx));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, bx));

	GLHelper::publishMatrixUniforms();
	glDrawElements(GL_TRIANGLES, totalIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::fillOut(vector<Vertex> vertices, vector<GLuint> indices) {
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);

	totalIndices = indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);

	cout << "Created a mesh with " << vertices.size() << " vertices,  " << indices.size() << "indices." << endl;
}
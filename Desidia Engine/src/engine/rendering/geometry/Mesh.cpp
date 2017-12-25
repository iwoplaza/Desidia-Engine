#include "Mesh.hpp"
#include "../shader/ShaderManager.hpp"
#include "../GLHelper.hpp"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

Mesh::Mesh() {
	m_totalIndices = 0;
}

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices) : Mesh() {
	fillOut(vertices, indices);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &m_vboVerticesID);
	glDeleteBuffers(1, &m_vboIndicesID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void Mesh::draw() {
	glBindVertexArray(m_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboVerticesID);
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
	glDrawElements(GL_TRIANGLES, m_totalIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::fillOut(MeshData meshData) {
	fillOut(meshData.vertices, meshData.indices);
	m_meshData = meshData;
}

void Mesh::fillOut(vector<Vertex> vertices, vector<GLuint> indices) {
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(1, &m_vboVerticesID);
	glGenBuffers(1, &m_vboIndicesID);

	m_totalIndices = indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

MeshData Mesh::getMeshData() {
	return m_meshData;
}
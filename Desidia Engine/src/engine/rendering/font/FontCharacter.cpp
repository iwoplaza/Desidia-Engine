#include "FontCharacter.hpp"
#include "../shader/ShaderManager.hpp"
#include "../GLHelper.hpp"
#include "../geometry/Vertex.hpp"
#include <iostream>
#include <vector>

FontCharacter::FontCharacter() {}

FontCharacter::~FontCharacter() {
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);
}

void FontCharacter::compile() {
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);

	vector<Vertex> vertices = vector<Vertex>();
	vertices.push_back(Vertex(offsetX, -height - offsetY, 0, 0, 0, 0, texX, 1-(texY + texH)));
	vertices.push_back(Vertex(offsetX + width, -height - offsetY, 0, 0, 0, 0, texX + texW, 1-(texY + texH)));
	vertices.push_back(Vertex(offsetX + width, -offsetY, 0, 0, 0, 0, texX + texW, 1-texY));
	vertices.push_back(Vertex(offsetX, -offsetY, 0, 0, 0, 0, texX, 1-texY));

	vector<GLuint> indices = vector<GLuint>();
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void FontCharacter::draw() {
	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glEnableVertexAttribArray(ShaderManager::getAttribute("aVertexPosition"));
	glVertexAttribPointer(ShaderManager::getAttribute("aVertexPosition"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(ShaderManager::getAttribute("aVertexNormal"));
	glVertexAttribPointer(ShaderManager::getAttribute("aVertexNormal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, nx));
	glEnableVertexAttribArray(ShaderManager::getAttribute("aVertexTexCoord"));
	glVertexAttribPointer(ShaderManager::getAttribute("aVertexTexCoord"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, u));

	GLHelper::publishMatrixUniforms();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
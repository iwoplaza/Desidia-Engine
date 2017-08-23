#include "Mesh.hpp"
#include "../shader/ShaderManager.hpp"
#include "../GLHelper.hpp"
#include <glm/glm.hpp>
#include <iostream>

using namespace std;

Mesh::Mesh() {
	vertices = vector<Vertex>();
	indices = vector<GLuint>();
}

Mesh::~Mesh() {
	vertices.clear();
	indices.clear();
	glDeleteBuffers(1, &vboPositionsID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteBuffers(1, &vboTexCoordsID);
	glDeleteBuffers(1, &vboNormalsID);
	glDeleteVertexArrays(1, &vaoID);
}

void Mesh::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, vboPositionsID);
	glEnableVertexAttribArray(ShaderManager::getAttribute("vertexPosition"));
	glVertexAttribPointer(ShaderManager::getAttribute("vertexPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboNormalsID);
	glEnableVertexAttribArray(ShaderManager::getAttribute("vertexNormal"));
	glVertexAttribPointer(ShaderManager::getAttribute("vertexNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	//ShaderManager::vertexAttribPointer("vertexPosition", 3, GL_FLOAT, GL_FALSE, 0, 0);

	/*if (TextureManager.areTexturesEnabled()) {
		gl.bindBuffer(gl.ARRAY_BUFFER, this.textureCoordBuffer);
		gl.enableVertexAttribArray(ShaderManager.getAttribute('textureCoord'));
		ShaderManager.vertexAttribPointer('textureCoord', this.textureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
	}
	else {
		gl.disableVertexAttribArray(ShaderManager.getAttribute('textureCoord'));
	}*/

	/*if (ShaderManager.hasAttribute('normal')) {
		gl.bindBuffer(gl.ARRAY_BUFFER, this.normalBuffer);
		ShaderManager.vertexAttribPointer('normal', this.normalBuffer.itemSize, gl.FLOAT, false, 0, 0);
	}*/

	GLHelper::publishMatrixUniforms();
	//ShaderManager.setUniform1i("uEnableTextures", TextureManager.areTexturesEnabled());
	glBindVertexArray(vaoID);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::fillOut(vector<Vertex> _vertices, vector<GLuint> _indices) {
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vboPositionsID);
	glGenBuffers(1, &vboIndicesID);
	//glGenBuffers(1, &vboTexCoordsID);
	glGenBuffers(1, &vboNormalsID);

	vertices = _vertices;
	indices = _indices;

	vector<glm::vec3> positions = vector<glm::vec3>();
	for (int i = 0; i < vertices.size(); i++) {
		Vertex vertex = vertices[i];
		positions.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
	}

	vector<glm::vec3> normals = vector<glm::vec3>();
	for (int i = 0; i < vertices.size(); i++) {
		Vertex vertex = vertices[i];
		normals.push_back(glm::vec3(vertex.nx, vertex.ny, vertex.nz));
	}

	//GLsizei stride = sizeof();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboPositionsID);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderManager::getAttribute("vertexPosition"));
	glVertexAttribPointer(ShaderManager::getAttribute("vertexPosition"), 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	//glEnableVertexAttribArray(_shader["vVertex"]);
	//glVertexAttribPointer(_shader["vVertex"], 3, GL_FLOAT, GL_FALSE, 0, 0);

	//TexCoords
	/*glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordsID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), 0, GL_STATIC_DRAW);

	GLfloat* pTBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	fillTexCoordBuffer(pTBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	//glEnableVertexAttribArray(_shader["vTexCoord"]);
	//glVertexAttribPointer(_shader["vTexCoord"], 2, GL_FLOAT, GL_FALSE, 0, 0);
	//Normals*/
	glBindBuffer(GL_ARRAY_BUFFER, vboNormalsID);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(ShaderManager::getAttribute("vertexPosition"));
	glVertexAttribPointer(ShaderManager::getAttribute("vertexNormal"), 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	/*GLfloat* normalBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	fillNormalBuffer(normalBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);*/

	//glEnableVertexAttribArray(_shader["vNormal"]);
	//glVertexAttribPointer(_shader["vNormal"], 3, GL_FLOAT, GL_FALSE, 0, 0);



	//Indices
	
	glBindVertexArray(0);

	cout << "Created a mesh with " << indices.size() / 3 << " faces." << endl;
}

void Mesh::fillPositionBuffer(GLfloat* buffer) {
	glm::vec3* positions = (glm::vec3*)(buffer);

	for (int i = 0; i < vertices.size(); i++) {
		positions[i] = glm::vec3(vertices[i].x, vertices[i].y, vertices[i].z);
	}
}

void Mesh::fillIndexBuffer(GLuint* buffer) {
	for (int i = 0; i < indices.size(); i++) {
		buffer[i] = (GLuint)indices[i];
	}
}

void Mesh::fillTexCoordBuffer(GLfloat* buffer) {
	glm::vec2* texCoords = (glm::vec2*)(buffer);

	for (int i = 0; i < vertices.size(); i++) {
		texCoords[i] = glm::vec2(vertices[i].u, vertices[i].v);
	}
}

void Mesh::fillNormalBuffer(GLfloat* buffer) {
	glm::vec3* normals = (glm::vec3*)(buffer);

	for (int i = 0; i < vertices.size(); i++) {
		normals[i] = glm::vec3(vertices[i].nx, vertices[i].ny, vertices[i].nz);
	}
}
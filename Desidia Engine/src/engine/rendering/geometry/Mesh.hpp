#pragma once

#include <vector>
#include <GL/glew.h>
#include "Vertex.hpp"
#include "MeshData.hpp"

class Mesh {
	protected:
		GLuint m_vaoID;
		GLuint m_vboIndicesID;
		GLuint m_vboVerticesID;
		int m_totalIndices;

		MeshData m_meshData;

		void fillOut(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
	public:
		Mesh();
		Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
		~Mesh();

		void draw();
		void fillOut(MeshData meshData);
		MeshData getMeshData();
};
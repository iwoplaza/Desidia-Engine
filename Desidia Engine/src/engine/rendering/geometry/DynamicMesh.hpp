#pragma once

#include <vector>
#include <GL/glew.h>
#include "Vertex.hpp"
#include "MeshData.hpp"

class DynamicMesh {
	protected:
		GLuint m_vaoID;
		GLuint m_vboIndicesID;
		GLuint m_vboVerticesID;
		int m_totalIndices;

		MeshData m_meshData;

		void fillOut(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
	public:
		DynamicMesh();
		DynamicMesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
		~DynamicMesh();

		void draw();
		void fillOut(MeshData meshData);
		void update(MeshData meshData);
		//void append(MeshData meshData);
		MeshData getMeshData();
};
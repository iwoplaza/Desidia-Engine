#pragma once

#include <iostream>
#include <vector>
#include "../rendering/geometry/Mesh.hpp"

using namespace std;

class OBJObject {
	protected:
		const char* m_name;
		MeshData m_meshData;
	public:
		OBJObject(const char* _name);

		MeshData getMeshData();
		void setMeshData(MeshData meshData);
};

class OBJLoader {
	public:
		static MeshData loadMeshDataFromFile(string filename);
		static Mesh* loadMeshFromFile(string filename);
		static vector<OBJObject*> loadSceneFromFile(string filename);
};
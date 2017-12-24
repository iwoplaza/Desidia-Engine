#include "OBJLoader.hpp"
#include "../rendering/geometry/Mesh.hpp"
#include "../rendering/geometry/MeshData.hpp"
#include "../util/Vector3.hpp"
#include "../util/Vector2.hpp"
#include "../Resources.hpp"
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

OBJObject::OBJObject(const char* p_name) {
	m_name = p_name;
	m_meshData = MeshData();
}

MeshData OBJObject::getMeshData() {
	return m_meshData;
}

void OBJObject::setMeshData(MeshData meshData) {
	m_meshData = meshData;
}

MeshData OBJLoader::loadMeshDataFromFile(string filename) {
	vector<OBJObject*> objects = loadSceneFromFile(filename);
	if (objects.size() < 1) {
		std::cerr << "Failed to load \"" << filename << "\", because it doesn't contain any valid object data." << std::endl;
		return {};
	}
	return objects[0]->getMeshData();
}

Mesh* OBJLoader::loadMeshFromFile(string filename) {
	MeshData meshData = loadMeshDataFromFile(filename);
	Mesh* mesh = new Mesh();
	mesh->fillOut(meshData);
	return mesh;
}

void processMeshData(vector<Vertex> &vertices, vector<GLuint> &indices) {
	for (int i = 0; i < indices.size(); i += 3) {
		int index0 = indices[i];
		int index1 = indices[i + 1];
		int index2 = indices[i + 2];

		Vertex v0 = vertices[index0];
		Vertex v1 = vertices[index1];
		Vertex v2 = vertices[index2];

		Vector3 deltaPos1 = Vector3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
		Vector3 deltaPos2 = Vector3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
		Vector2 deltaUV1 = Vector2(v1.u - v0.u, v1.v - v0.v);
		Vector2 deltaUV2 = Vector2(v2.u - v0.u, v2.v - v0.v);

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		Vector3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		Vector3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
		Vector3 normal = Vector3(v0.nx + v1.nx + v2.nx, v0.ny + v1.ny + v2.ny, v0.nz + v1.nz + v2.nz).normalize();

		tangent = tangent - normal * normal.dot(tangent);
		if (normal.cross(tangent).dot(bitangent) < 0.0f)
			tangent *= -1.0f;

		vertices[index0].addTangent(tangent);
		vertices[index1].addTangent(tangent);
		vertices[index2].addTangent(tangent);
		vertices[index0].addBitangent(bitangent);
		vertices[index1].addBitangent(bitangent);
		vertices[index2].addBitangent(bitangent);
	}
}

vector<OBJObject*> OBJLoader::loadSceneFromFile(string filename) {
	vector<OBJObject*> objects = vector<OBJObject*>();
	OBJObject* object = nullptr;

	vector<Vector3> positions = {}, normals = {};
	vector<Vector2> texCoords = {};

	vector<Vertex> vertices = {};
	vector<GLuint> indices = {};

	ifstream in(Resources::ROOT_PATH + filename);
	if (!in.is_open()) {
		std::cerr << "Failed to open .obj: " << filename << endl;
		return objects;
	}

	string line;
	while (getline(in, line)) {
		if (line.length() == 0) continue;

		if (line.substr(0, 1) == "o") {
			if (object != nullptr) {
				processMeshData(vertices, indices);
				object->setMeshData({ vertices, indices });
				objects.push_back(object);
				vertices.clear();
				indices.clear();
			}
			object = new OBJObject(line.substr(2).c_str());
		} else if (line.substr(0, 2) == "vn") {
			string x = line.substr(line.find(' ') + 1);
			string y = x.substr(x.find(' ') + 1);
			string z = y.substr(y.find(' ') + 1);
			normals.push_back(Vector3(atof(x.substr(0, x.find(" ")).c_str()), atof(y.substr(0, y.find(" ")).c_str()), atof(z.c_str())));
		} else if (line.substr(0, 2) == "vt") {
			string x = line.substr(line.find(' ') + 1);
			string y = x.substr(x.find(' ') + 1);
			texCoords.push_back(Vector2(atof(x.substr(0, x.find(" ")).c_str()), atof(y.substr(0, y.find(" ")).c_str())));
		} else if (line[0] == 'v') {
			string x = line.substr(line.find(' ') + 1);
			string y = x.substr(x.find(' ') + 1);
			string z = y.substr(y.find(' ') + 1);
			positions.push_back(Vector3(atof(x.substr(0, x.find(" ")).c_str()), atof(y.substr(0, y.find(" ")).c_str()), atof(z.c_str())));
		} else if (line[0] == 'f') {
			string v1 = line.substr(2, line.find(' ', 2) - 2);
			string v2 = line.substr(v1.length() + 3, line.find(' ', v1.length() + 3) + 1 - v1.length() - 4);
			string v3 = line.substr(line.find_last_of(' '));

			int p1 = atoi(v1.substr(0, v1.find('/')).c_str());
			int t1 = atoi(v1.substr(v1.find('/') + 1, v1.find_last_of('/') - v1.find('/') - 1).c_str());
			int n1 = atoi(v1.substr(v1.find_last_of('/') + 1).c_str());

			int p2 = atoi(v2.substr(0, v2.find('/')).c_str());
			int t2 = atoi(v2.substr(v2.find('/') + 1, v2.find_last_of('/') - v2.find('/') - 1).c_str());
			int n2 = atoi(v2.substr(v2.find_last_of('/') + 1).c_str());

			int p3 = atoi(v3.substr(0, v3.find('/')).c_str());
			int t3 = atoi(v3.substr(v3.find('/') + 1, v3.find_last_of('/') - v3.find('/') - 1).c_str());
			int n3 = atoi(v3.substr(v3.find_last_of('/') + 1).c_str());

			Vertex vertex0 = Vertex(positions[p1 - 1], normals[n1 - 1], texCoords[t1 - 1]);
			Vertex vertex1 = Vertex(positions[p2 - 1], normals[n2 - 1], texCoords[t2 - 1]);
			Vertex vertex2 = Vertex(positions[p3 - 1], normals[n3 - 1], texCoords[t3 - 1]);

			vector<Vertex>::iterator vertex0I = std::find(vertices.begin(), vertices.end(), vertex0);
			if (vertex0I != vertices.end()) {
				//There is already a vertex like that in the buffer.
				indices.push_back(vertex0I - vertices.begin());
			} else {
				vertices.push_back(vertex0);
				indices.push_back((GLuint)vertices.size() - 1);
			}

			vector<Vertex>::iterator vertex1I = std::find(vertices.begin(), vertices.end(), vertex1);
			if (vertex1I != vertices.end()) {
				//There is already a vertex like that in the buffer.
				indices.push_back(vertex1I - vertices.begin());
			} else {
				vertices.push_back(vertex1);
				indices.push_back(vertices.size() - 1);
			}

			vector<Vertex>::iterator vertex2I = std::find(vertices.begin(), vertices.end(), vertex2);
			if (vertex2I != vertices.end()) {
				//There is already a vertex like that in the buffer.
				indices.push_back(vertex2I - vertices.begin());
			} else {
				vertices.push_back(vertex2);
				indices.push_back(vertices.size() - 1);
			}
		}
	}

	processMeshData(vertices, indices);
	object->setMeshData({ vertices, indices });
	objects.push_back(object);
	return objects;
}
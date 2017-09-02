#include "OBJLoader.hpp"
#include "../rendering/geometry/Mesh.hpp"
#include "../util/Vector3.hpp"
#include "../util/Vector2.hpp"
#include "../Resources.hpp"
#include <fstream>
#include <string>

Mesh* OBJLoader::loadFromFile(string filename) {
	Mesh* mesh = new Mesh();

	vector<Vector3> positions = vector<Vector3>();
	vector<Vector3> normals = vector<Vector3>();
	vector<Vector2> texCoords = vector<Vector2>();

	vector<Vertex> vertices = vector<Vertex>();
	vector<GLuint> indices = vector<GLuint>();

	ifstream in(Resources::ROOT_PATH + filename);
	if (!in.is_open()) {
		std::cerr << "Failed to open .obj: " << filename << endl;
		return mesh;
	}

	string line;
	while (getline(in, line)) {
		if (line.length() == 0) continue;

		if (line.substr(0, 2) == "vn") {
			string x = line.substr(line.find(' ') + 1);
			string y = x.substr(x.find(' ')+1);
			string z = y.substr(y.find(' ')+1);
			normals.push_back(Vector3(atof(x.substr(0, x.find(" ")).c_str()), atof(y.substr(0, y.find(" ")).c_str()), atof(z.c_str())));
		}else if (line.substr(0, 2) == "vt") {
			string x = line.substr(line.find(' ') + 1);
			string y = x.substr(x.find(' ') + 1);
			texCoords.push_back(Vector2(atof(x.substr(0, x.find(" ")).c_str()), atof(y.substr(0, y.find(" ")).c_str())));
		}
		else if (line[0] == 'v') {
			string x = line.substr(line.find(' ') + 1);
			string y = x.substr(x.find(' ') + 1);
			string z = y.substr(y.find(' ') + 1);
			positions.push_back(Vector3(atof(x.substr(0, x.find(" ")).c_str()), atof(y.substr(0, y.find(" ")).c_str()), atof(z.c_str())));
		}
		else if (line[0] == 'f') {
			string v1 = line.substr(2, line.find(' ', 2) - 2);
			string v2 = line.substr(v1.length()+3, line.find(' ', v1.length()+3) + 1 - v1.length() - 4);
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

			vertices.push_back(Vertex(positions[p1 - 1], normals[n1 - 1], texCoords[t1 - 1]));
			vertices.push_back(Vertex(positions[p2 - 1], normals[n2 - 1], texCoords[t2 - 1]));
			vertices.push_back(Vertex(positions[p3 - 1], normals[n3 - 1], texCoords[t3 - 1]));

			indices.push_back(vertices.size() - 3);
			indices.push_back(vertices.size() - 2);
			indices.push_back(vertices.size() - 1);
		}
	}

	mesh->fillOut(vertices, indices);
	return mesh;
}
#pragma once

#include <iostream>

using namespace std;

class Mesh;

class OBJLoader {
	public:
		static Mesh* loadFromFile(string filename);
};
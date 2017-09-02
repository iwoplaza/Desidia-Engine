#pragma once

#include <map>
#include <GL/glew.h>

using namespace std;

class Shader;

class ShaderManager {
	public:
		static map<string, Shader*> shaders;
		static Shader* current;

		static void loadResource(string name);
		static void use(string name);
		static void vertexAttribPointer(string name, GLint count, int dimensions, bool flag, GLsizei x, int y);
		static GLuint getAttribute(string name);
		static GLuint getUniform(string name);
};
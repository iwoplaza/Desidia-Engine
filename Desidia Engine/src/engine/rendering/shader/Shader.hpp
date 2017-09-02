#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
using namespace std;

class Shader {
	private:
		enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
		GLuint program;
		int totalShaders;
		GLuint shaders[3];

		string vertexSource;
		string fragmentSource;
	public:
		Shader();
		~Shader();
		void loadFromString(string src);
		void loadFromFile(const string& filename);
		void compile(string source);
		void createAndLinkProgram();
		void use();
		void disable();
		GLuint getAttribute(const string& attribute);
		GLuint getUniform(const string& uniform);
		void destroy();
};
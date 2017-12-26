#pragma once

#include <string>
#include <map>
#include <GL/glew.h>

class Shader {
	private:
		std::string m_name;
		enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
		GLuint program;
		int totalShaders;
		GLuint shaders[3];

		std::string vertexSource;
		std::string fragmentSource;
	public:
		Shader(std::string _name);
		~Shader();
		void loadFromString(std::string src);
		void loadFromFile(const std::string& filename);
		void compile(std::string source);
		void createAndLinkProgram();
		void use();
		void disable();
		void printActiveUniforms();
		std::string getName();
		GLuint getAttribute(const std::string& attribute);
		GLuint getUniform(const std::string& uniform);
		GLuint getUniformBlockIndex(const std::string& blockName);
		void destroy();
};
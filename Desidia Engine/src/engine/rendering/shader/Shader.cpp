#include "Shader.hpp"
#include <iostream>

using namespace std;

Shader::Shader(std::string _name)
{
	m_name = _name;
	totalShaders = 0;
	shaders[VERTEX_SHADER] = 0;
	shaders[FRAGMENT_SHADER] = 0;
	shaders[GEOMETRY_SHADER] = 0;
}

Shader::~Shader()
{
	destroy();
}

void Shader::destroy() {
	glDeleteProgram(program);
}

void Shader::loadFromString(string source) {
	compile(source);

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint status;

	const char * ptmp = vertexSource.c_str();
	glShaderSource(vertex_shader, 1, &ptmp, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(vertex_shader, infoLogLength, NULL, infoLog);
		cerr << "Compile log: " << infoLog << endl;
		delete[] infoLog;
	}
	shaders[VERTEX_SHADER] = vertex_shader;

	ptmp = fragmentSource.c_str();
	glShaderSource(fragment_shader, 1, &ptmp, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(fragment_shader, infoLogLength, NULL, infoLog);
		cerr << "Compile log: " << infoLog << endl;
		delete[] infoLog;
	}
	shaders[FRAGMENT_SHADER] = fragment_shader;
}

void Shader::compile(string source) {
	int mode = 0;
	vertexSource = "#version 330 core";
	fragmentSource = "#version 330 core";
	string remaining = source;
	while (remaining.find('[') != -1) {
		if (mode == 1)
			vertexSource += remaining.substr(0, remaining.find('['));
		else if (mode == 2)
			fragmentSource += remaining.substr(0, remaining.find('['));
		remaining = remaining.substr(remaining.find('[') + 1);
		string command = remaining.substr(0, remaining.find(']'));
		if (command == "VERTEX") {
			mode = 1;
		}
		else if (command == "FRAGMENT") {
			mode = 2;
		}
		remaining = remaining.substr(remaining.find(']') + 1);
	}
	if (mode == 1)
		vertexSource += remaining;
	else if (mode == 2)
		fragmentSource += remaining;
}

void Shader::createAndLinkProgram() {
	program = glCreateProgram();
	if (shaders[VERTEX_SHADER] != 0) {
		glAttachShader(program, shaders[VERTEX_SHADER]);
	}
	if (shaders[FRAGMENT_SHADER] != 0) {
		glAttachShader(program, shaders[FRAGMENT_SHADER]);
	}
	if (shaders[GEOMETRY_SHADER] != 0) {
		glAttachShader(program, shaders[GEOMETRY_SHADER]);
	}

	GLint status;
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
		cerr << "Link log: " << infoLog << endl;
		delete[] infoLog;
	}

	glDeleteShader(shaders[VERTEX_SHADER]);
	glDeleteShader(shaders[FRAGMENT_SHADER]);
	glDeleteShader(shaders[GEOMETRY_SHADER]);
}

void Shader::use() {
	glUseProgram(program);
}

void Shader::disable() {
	glUseProgram(0);
}

void Shader::printActiveUniforms() {
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 50; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length

	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	printf("Active Uniforms: %d\n", count);

	for (i = 0; i < count; i++)
	{
		glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

		printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
	}
}

std::string Shader::getName() {
	return m_name;
}

GLuint Shader::getAttribute(const string& attribute) {
	return glGetAttribLocation(program, attribute.c_str());
}

GLuint Shader::getUniform(const string& uniform) {
	return glGetUniformLocation(program, uniform.c_str());
}

GLuint Shader::getUniformBlockIndex(const std::string& blockName) {
	return glGetUniformBlockIndex(program, blockName.c_str());
}

#include <fstream>
void Shader::loadFromFile(const string& filename) {
	ifstream fp;
	fp.open(filename.c_str(), ios_base::in);
	if (fp) {
		string line = "", buffer = "";
		while (getline(fp, line)) {
			buffer.append(line);
			buffer.append("\r\n");
		}

		loadFromString(buffer);
	}
	else {
		cerr << "And error occured while loading up a shader: " << filename << endl;
	}
}
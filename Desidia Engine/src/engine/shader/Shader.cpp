#include "Shader.hpp"
#include <iostream>

using namespace std;

Shader::Shader()
{
	totalShaders = 0;
	shaders[VERTEX_SHADER] = 0;
	shaders[FRAGMENT_SHADER] = 0;
	shaders[GEOMETRY_SHADER] = 0;
	attributes = map<string, GLuint>();
	uniforms = map<string, GLuint>();
	attributes.clear();
	uniforms.clear();
}

Shader::~Shader()
{
	destroy();
	attributes.clear();
	uniforms.clear();
}

void Shader::destroy() {
	glDeleteProgram(program);
}

void Shader::loadFromString(string source) {
	int mode = 0;
	string vertexShaderSource = "#version 330 core";
	string fragmentShaderSource = "#version 330 core";
	while (source.find('[') != -1) {
		if (mode == 1)
			vertexShaderSource += source.substr(0, source.find('['));
		else if (mode == 2)
			fragmentShaderSource += source.substr(0, source.find('['));
		source = source.substr(source.find('[')+1);
		string command = source.substr(0, source.find(']'));
		cout << "Command: " << command << endl;
		if (command == "VERTEX") {
			mode = 1;
		}
		else if (command == "FRAGMENT") {
			mode = 2;
		}
		source = source.substr(source.find(']')+1);
	}
	if (mode == 1)
		vertexShaderSource += source;
	else if (mode == 2)
		fragmentShaderSource += source;

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint status;

	const char * ptmp = vertexShaderSource.c_str();
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

	ptmp = fragmentShaderSource.c_str();
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

	attributes["vertexPosition"] = glGetAttribLocation(program, "aVertexPosition");
	attributes["vertexNormal"] = glGetAttribLocation(program, "aVertexNormal");
	attributes["vertexTexCoord"] = glGetAttribLocation(program, "aVertexTexCoord");
	uniforms["mMatrix"] = glGetUniformLocation(program, "uMMatrix");
	uniforms["vMatrix"] = glGetUniformLocation(program, "uVMatrix");
	uniforms["pMatrix"] = glGetUniformLocation(program, "uPMatrix");
	uniforms["nMatrix"] = glGetUniformLocation(program, "uNMatrix");
	uniforms["diffuseMap"] = glGetUniformLocation(program, "uDiffuseMap");
}

void Shader::use() {
	glUseProgram(program);
}

void Shader::disable() {
	glUseProgram(0);
}

GLuint Shader::getAttribute(const string& attribute) {
	return attributes[attribute];
}

GLuint Shader::getUniform(const string& uniform) {
	return uniforms[uniform];
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
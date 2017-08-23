#include "ShaderManager.hpp"
#include "Shader.hpp"

map<string, Shader*> ShaderManager::shaders;
Shader* ShaderManager::current;

void ShaderManager::loadResource(string name) {
	Shader* shader = new Shader();
	shader->loadFromFile("res/shaders/"+name+".shader");
	shader->createAndLinkProgram();
	shaders[name] = shader;
}

void ShaderManager::use(string name) {
	current = shaders[name];
	current->use();
}

void ShaderManager::vertexAttribPointer(string name, GLint count, int dimensions, bool flag, GLsizei x, int y) {
	glEnableVertexAttribArray(current->getAttribute(name));
	glVertexAttribPointer(current->getAttribute(name), 3, GL_FLOAT, GL_FALSE, 0, 0);
}

GLuint ShaderManager::getAttribute(string name) {
	return current->getAttribute(name);
}

GLuint ShaderManager::getUniform(string name) {
	return current->getUniform(name);
}
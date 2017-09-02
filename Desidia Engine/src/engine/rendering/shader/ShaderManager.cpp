#include "ShaderManager.hpp"
#include "Shader.hpp"
#include "../../Resources.hpp"
#include <iostream>

map<string, Shader*> ShaderManager::shaders;
Shader* ShaderManager::current;

void ShaderManager::loadResource(string name) {
	cout << "Loading a shader: " << name << endl;

	Shader* shader = new Shader();
	shader->loadFromFile(Resources::ROOT_PATH + name);
	shader->createAndLinkProgram();
	shaders[name] = shader;
}

void ShaderManager::use(string name) {
	if (shaders.find(name) == shaders.end()) {
		std::cerr << "Couldn't use shader '" << name << "'" << std::endl;
		return;
	}
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
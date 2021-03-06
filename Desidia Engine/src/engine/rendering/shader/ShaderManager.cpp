#include "ShaderManager.hpp"
#include "Shader.hpp"
#include "../../Resources.hpp"
#include <iostream>
#include "../../windows/PopUp.hpp"

map<string, Shader*> ShaderManager::shaders;
Shader* ShaderManager::current;

void ShaderManager::loadResource(string name) {
	cout << "Loading a shader: " << name << endl;

	Shader* shader = new Shader(name);
	shader->loadFromFile(Resources::ROOT_PATH + name);
	shader->createAndLinkProgram();
	shaders[name] = shader;
}

void ShaderManager::use(string name) {
	if (shaders.find(name) == shaders.end()) {
		PopUp::error((L"Couldn't use shader '" + std::wstring(name.begin(), name.end()) + L"'").c_str());
		std::cerr << "Couldn't use shader '" << name << "'" << std::endl;
		exit(EXIT_FAILURE);
		return;
	}
	use(shaders[name]);
}

void ShaderManager::use(Shader* _shader) {
	current = _shader;
	current->use();
}

void ShaderManager::vertexAttribPointer(string name, GLint count, int dimensions, bool flag, GLsizei x, int y) {
	glEnableVertexAttribArray(current->getAttribute(name));
	glVertexAttribPointer(current->getAttribute(name), 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void ShaderManager::forEach(std::function<void(Shader*)> callback) {
	for (std::pair<string, Shader*> shader : shaders) {
		callback(shader.second);
	}
}

GLuint ShaderManager::getAttribute(string name) {
	return current->getAttribute(name);
}

GLuint ShaderManager::getUniform(string name) {
	return current->getUniform(name);
}

GLuint ShaderManager::getUniformBlockIndex(string name) {
	return current->getUniformBlockIndex(name);
}
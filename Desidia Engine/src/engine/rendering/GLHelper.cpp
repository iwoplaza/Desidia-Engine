#include "GLHelper.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

GLState GLHelper::currentState = GLState();
vector<GLState> GLHelper::stateStack = vector<GLState>();

GLState::GLState() {
	modelMatrix = glm::mat4();
	viewMatrix = glm::mat4();
	projectionMatrix = glm::mat4();
	normalMatrix = glm::mat4();
}

void GLHelper::identityProjection() {
	currentState.projectionMatrix = glm::mat4();
}

void GLHelper::identityModel() {
	currentState.modelMatrix = glm::mat4();
	currentState.normalMatrix = glm::mat4();
}

void GLHelper::publishMatrixUniforms() {
	glUniformMatrix4fv(ShaderManager::getUniform("uPMatrix"), 1, GL_FALSE, glm::value_ptr(currentState.projectionMatrix));
	glUniformMatrix4fv(ShaderManager::getUniform("uMMatrix"), 1, GL_FALSE, glm::value_ptr(currentState.modelMatrix));
	glUniformMatrix4fv(ShaderManager::getUniform("uVMatrix"), 1, GL_FALSE, glm::value_ptr(currentState.viewMatrix));
	glUniformMatrix4fv(ShaderManager::getUniform("uNMatrix"), 1, GL_FALSE, glm::value_ptr(currentState.normalMatrix));
}

void GLHelper::saveState() {
	stateStack.push_back(currentState);
}

void GLHelper::loadState() {
	currentState = stateStack[stateStack.size()-1];
	stateStack.erase(stateStack.begin() + stateStack.size() - 1);
}

void GLHelper::ortho(float left, float right, float bottom, float top) {
	currentState.projectionMatrix = glm::ortho(left, right, bottom, top);
}

void GLHelper::perspective(float fov, float ratio, float near, float far) {
	currentState.projectionMatrix = glm::perspective(fov, ratio, near, far);
}

void GLHelper::translate(float x, float y, float z) {
	currentState.modelMatrix = glm::translate(currentState.modelMatrix, glm::vec3(x, y, z));
}

void GLHelper::scale(float x, float y, float z) {
	currentState.modelMatrix = glm::scale(currentState.modelMatrix, glm::vec3(x, y, z));
}

void GLHelper::rotate(float angle, float x, float y, float z) {
	currentState.modelMatrix = glm::rotate(currentState.modelMatrix, angle, glm::vec3(x, y, z));
	currentState.normalMatrix = glm::rotate(currentState.normalMatrix, angle, glm::vec3(x, y, z));
}
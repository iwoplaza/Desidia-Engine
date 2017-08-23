#include "GLHelper.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

glm::mat4 GLHelper::modelMatrix = glm::mat4();
glm::mat4 GLHelper::viewMatrix = glm::mat4();
glm::mat4 GLHelper::projectionMatrix = glm::mat4();
glm::mat4 GLHelper::normalMatrix = glm::mat4();

void GLHelper::publishMatrixUniforms() {
	glUniformMatrix4fv(ShaderManager::getUniform("pMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(ShaderManager::getUniform("mMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(ShaderManager::getUniform("vMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(ShaderManager::getUniform("nMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}
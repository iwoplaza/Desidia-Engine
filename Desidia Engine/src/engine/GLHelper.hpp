#pragma once

#include "shader\ShaderManager.hpp"
#include <glm/glm.hpp>
#include <GL\glew.h>

class GLHelper {
	public:
		static glm::mat4 modelMatrix;
		static glm::mat4 viewMatrix;
		static glm::mat4 projectionMatrix;
		static glm::mat4 normalMatrix;

		static void publishMatrixUniforms();
};
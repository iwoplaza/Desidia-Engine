#pragma once

#include "shader\ShaderManager.hpp"
#include <glm/glm.hpp>
#include <GL\glew.h>
#include <vector>

struct GLState {
	GLState();

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 normalMatrix;
};

class GLHelper {
	public:
		static GLState currentState;
		static vector<GLState> stateStack;

		static void identityProjection();
		static void identityModel();
		static void publishMatrixUniforms();
		static void saveState();
		static void loadState();

		static void ortho(float left, float right, float bottom, float top);
		static void perspective(float fov, float ratio, float near, float far);
		static void translate(float x, float y, float z);
		static void scale(float x, float y, float z);
		static void rotate(float angle, float x, float y, float z);
};
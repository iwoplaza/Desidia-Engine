#pragma once

#include "Component.hpp"
#include <string>
#include <glm/glm.hpp>

class ComponentCamera : public Component {
	protected:
		glm::mat4 rotationMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		int mode;
		int targetWidth, targetHeight;
		float ratio, near_plane, far_plane;
		float fov;
	public:
		ComponentCamera();

		void init();
		void activate();
		void updateProjection();
		glm::mat4 getRotationMatrix();
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		float getFOV();
		float getRatio();
		float getNear();
		float getFar();
		const char* getType();
		void setMode(int _mode);
		void setFOV(float _fov);
		void setTargetDimensions(int _width, int _height);

		static vector<ComponentCamera*> cameras;
		static ComponentCamera* activeCamera;
		static Component* parseJSON(const Value&);

		static const int MODE_ORTHOGRAPHIC;
		static const int MODE_PERSPECTIVE;
};
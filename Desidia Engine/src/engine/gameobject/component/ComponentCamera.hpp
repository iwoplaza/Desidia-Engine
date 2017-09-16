#pragma once

#include "Component.hpp"
#include <string>
#include <glm/glm.hpp>

class ComponentCamera : public Component {
	protected:
		
	public:
		ComponentCamera();

		void init();
		void activate();
		glm::mat4 getRotationMatrix();
		glm::mat4 getViewMatrix();
		const char* getType();

		static vector<ComponentCamera*> cameras;
		static ComponentCamera* activeCamera;
		static Component* parseJSON(const Value&);
};
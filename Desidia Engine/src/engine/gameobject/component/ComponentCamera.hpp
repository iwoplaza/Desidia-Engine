#pragma once

#include "Component.hpp"
#include <string>

class ComponentCamera : public Component {
	protected:
		
	public:
		ComponentCamera();

		void activate();
		const char* getType();

		static vector<Component*> cameras;
		static Component* activeCamera;
		static Component* parseJSON(const Value&);
};
#pragma once

#include "Component.hpp"

class ComponentMesh : public Component {
	public:
		ComponentMesh();

		const char* getType();
};
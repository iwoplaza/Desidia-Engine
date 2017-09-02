#pragma once

#include "Component.hpp"
#include <string>

class ComponentMesh : public Component {
	protected:
		std::string model;
		std::string material;
	public:
		ComponentMesh(std::string _model, std::string _material);

		void draw();
		const char* getType();

		static Component* parseJSON(const Value&);
};
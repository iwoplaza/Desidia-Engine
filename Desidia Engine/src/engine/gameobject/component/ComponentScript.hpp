#pragma once

#include "Component.hpp"
#include <string>

class ComponentScript : public Component {
	protected:
		std::string script;
		std::string holderObject;
		std::string metadata;
	public:
		ComponentScript(std::string _script);

		void init();
		void update();
		const char* getType();

		static Component* parseJSON(const Value&);
};
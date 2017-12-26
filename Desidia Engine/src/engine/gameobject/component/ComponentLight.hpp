#pragma once

#include "Component.hpp"
#include "../../util/Color.hpp"

class LightSource;

class ComponentLight : public Component {
	protected:
		Color m_color;
		LightSource* m_lightSource;
	public:
		ComponentLight(Color _color);

		void init();
		void update();
		const char* getType();

		static Component* parseJSON(const Value&);
};
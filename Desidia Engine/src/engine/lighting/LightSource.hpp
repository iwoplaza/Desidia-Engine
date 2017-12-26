#pragma once

#include "../util/Vector3.hpp"
#include "../util/Color.hpp"

class LightSource {
	protected:
		Vector3 m_location;
		Color m_color;

		bool m_enabled;
	public:
		LightSource();
		LightSource(Vector3, Color);
		~LightSource();

		void enable();
		void disable();
		Vector3 getLocation();
		Color getColor();
		void setLocation(const Vector3& _location);
		void setColor(const Color& _color);
};
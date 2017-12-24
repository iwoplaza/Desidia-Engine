#pragma once

class Color {
	public:
		Color(float, float, float, float);
		Color(float, float, float);
		Color();

		float r, g, b, a;

		unsigned int asHex();

		static Color fromHex(unsigned int hex);
};
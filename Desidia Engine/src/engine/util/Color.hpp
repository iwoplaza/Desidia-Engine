#pragma once

class Color {
	public:
		Color();
		Color(float, float, float, float);

		float r, g, b, a;

		unsigned int asHex();

		static Color fromHex(unsigned int hex);
};
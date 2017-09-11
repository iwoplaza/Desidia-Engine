#include "Color.hpp"

Color::Color() : r(0), g(0), b(0), a(0) {}

Color::Color(float _r, float _g, float _b, float _a = 1.0f) 
	: r(_r), g(_g), b(_b), a(_a) {}

unsigned int Color::asHex() {
	int red = (int)(r * 255);
	int green = (int)(g * 255);
	int blue = (int)(b * 255);
	int alpha = (int)(a * 255);
	int hex = 0;
	hex |= red & 0xff;
	hex <<= 8;
	hex |= green & 0xff;
	hex <<= 8;
	hex |= blue & 0xff;
	hex <<= 8;
	hex |= alpha & 0xff;
	return hex;
}

Color Color::fromHex(unsigned int hex) {
	float a = (hex & 0xff) / 255.0f;
	hex >>= 8;
	float b = (hex & 0xff) / 255.0f;
	hex >>= 8;
	float g = (hex & 0xff) / 255.0f;
	hex >>= 8;
	float r = (hex & 0xff) / 255.0f;
	return Color(r, g, b, a);
}
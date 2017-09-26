#pragma once

#include <string>

class FontRenderer {
	public:
		static int fontSize;
		static int letterSpacing;
		static void drawText(std::string _text, std::string _font, std::string _shader);
		static int getTextWidth(std::string _text, std::string _font);
};
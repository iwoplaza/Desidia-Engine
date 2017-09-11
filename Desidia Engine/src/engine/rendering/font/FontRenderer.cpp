#include "FontRenderer.hpp"
#include "../shader/ShaderManager.hpp"
#include "../../Resources.hpp"
#include "../font/Font.hpp"
#include "../GLHelper.hpp"
#include <iostream>

int FontRenderer::fontSize = 17;

void FontRenderer::drawText(std::string _text, std::string _font, std::string _shader) {
	ShaderManager::use(_shader);
	Font* font = Resources::FONT[_font];
	font->bindTexture();
	glUniform1i(ShaderManager::getUniform("uDiffuseMap"), 0);
	GLHelper::saveState();
	float scale = (float)fontSize/font->getSize();
	GLHelper::scale(scale, scale, scale);
	GLHelper::translate(0, font->getLineHeight(), 0);
	for (char c : _text) {
		FontCharacter* character = font->findCharacter(c);
		if (character != nullptr) {
			character->draw();
			GLHelper::translate(character->advanceX, 0 , 0);
		}
	}
	GLHelper::loadState();
}

int FontRenderer::getTextWidth(std::string _text, std::string _font) {
	Font* font = Resources::FONT[_font];
	int width = 0;
	float scale = (float)fontSize / font->getSize();
	for (char c : _text) {
		FontCharacter* character = font->findCharacter(c);
		if (character != nullptr) {
			width += character->advanceX;
		}
	}
	return width*scale;
}
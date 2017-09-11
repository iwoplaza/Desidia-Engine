#pragma once

#include <GL/glew.h>

class FontCharacter {
	protected:
		GLuint vaoID;
		GLuint vboVerticesID;
		GLuint vboIndicesID;
	public:
		FontCharacter();
		~FontCharacter();

		int id;
		int width, height;
		int offsetX, offsetY;
		int advanceX;
		float texX, texY;
		float texW, texH;

		void compile();
		void draw();
};
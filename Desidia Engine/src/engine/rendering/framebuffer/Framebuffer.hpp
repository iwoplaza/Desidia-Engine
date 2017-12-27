#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

class Framebuffer {
	protected:
		int m_width, m_height;

		GLuint m_framebufferId;
		GLuint m_renderTextureId;
		GLuint m_depthRenderbuffer;
	public:
		Framebuffer(int _width, int _height);

		void bind();
		void unbind();
		int getWidth();
		int getHeight();
};
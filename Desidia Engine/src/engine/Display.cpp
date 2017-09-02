#include "Display.hpp"
#include "Engine.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

Display::Display(char* _title, int _width = 800, int _height = 600) {
	title = _title;
	width = _width;
	height = _height;
}

Display::~Display() {

}

void Display::init() {
	glutInitWindowSize(width, height);
	glutCreateWindow(title);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		cerr << "Error: " << glewGetErrorString(err) << endl;
	}
	else {
		if (GLEW_VERSION_3_3) {
			cout << "The driver supports OpenGL 3.3." << endl;
		}
	}
	cout << "Details:" << endl;
	cout << "\tGLEW Library " << glewGetString(GLEW_VERSION);
	cout << "\tProducent: " << glGetString(GL_VENDOR) << endl;
	cout << "\tRenderer: " << glGetString(GL_RENDERER) << endl;
	cout << "\tWersja OpenGL: " << glGetString(GL_VERSION) << endl;
	cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	glClearColor(0.1f, 0.2f, 0.3f, 0);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Display::destroy() {

}

void Display::setWidth(int nw) {
	width = nw;
}

void Display::setHeight(int nh) {
	height = nh;
}

int Display::getWidth() {
	return width;
}

int Display::getHeight() {
	return height;
}
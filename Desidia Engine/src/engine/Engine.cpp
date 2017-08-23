#include "Engine.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Display.hpp"
#include "GLHelper.hpp"
#include "geometry\Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Display* Engine::display;

Mesh mesh;

void Engine::init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);

	glutCloseFunc(onClose);
	glutReshapeFunc(onResize);
	glutIdleFunc(onIdle);
	/*glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutKeyboardFunc(OnKey);
	*/
}

void Engine::destroy() {

}

void Engine::run() {
	glutMainLoop();
}

void Engine::createDisplay(char* _title, int _width, int _height) {
	display = new Display(_title, _width, _height);
	display->init();

	ShaderManager::loadResource("default");
	ShaderManager::use("default");

	vector<Vertex> vertices = vector<Vertex>();
	vertices.push_back(Vertex(0, 0, 0));
	vertices.push_back(Vertex(1, 0, 0));
	vertices.push_back(Vertex(1, 1, 0));
	vertices.push_back(Vertex(0, 1, 0));
	vector<GLuint> indices = vector<GLuint>();
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);
	mesh.fillOut(vertices, indices);

	cout << glGetError() << ": " << gluErrorString(glGetError());
}

void Engine::onIdle() {
	glutPostRedisplay();
}

void Engine::onRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mesh.draw();

	glutSwapBuffers();
}

void Engine::onResize(int nw, int nh) {
	glViewport(0, 0, (GLsizei) nw, (GLsizei) nh);
	GLHelper::projectionMatrix = glm::ortho(-1, 1, -1, 1);
}

void Engine::onClose() {

}
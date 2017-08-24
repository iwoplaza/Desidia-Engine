#include "Engine.hpp"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/ilut.h>
#include <iostream>
#include "Display.hpp"
#include "GLHelper.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "texture\Texture.hpp"
#include "InputManager.hpp"
#include "geometry\Mesh.hpp"
#include "loader/OBJLoader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Display* Engine::display;
Camera* camera = new Camera();

Mesh* testMesh;
float ticks = 0;

int mouseOldX = 0, mouseOldY = 0;

void Engine::init(int argc, char** argv) {
	ilInit();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
}

void Engine::destroy() {

}

void Engine::run() {
	glutMainLoop();
}

void Engine::createDisplay(char* _title, int _width, int _height) {
	display = new Display(_title, _width, _height);
	display->init();

	glutCloseFunc(onClose);
	glutIdleFunc(onIdle);
	//glutKeyboardFunc(OnKey);
	glutReshapeFunc(onResize);
	glutDisplayFunc(onRender);
	glutPassiveMotionFunc(handleMouseMove);
	glutMotionFunc(handleMouseMove);
	glutMouseFunc(handleMouseClicked);
	glutEntryFunc(handleWindowEntry);

	Texture::add("textures/car.png");
	ShaderManager::loadResource("default");
	ShaderManager::use("default");
	glUniform1i(ShaderManager::getUniform("diffuseMap"), 0);

	testMesh = OBJLoader::loadFromFile("res/models/car.obj");

	cout << glGetError() << ": " << gluErrorString(glGetError());
}

void Engine::handleWindowEntry(int state) {
	if (state == GLUT_ENTERED)
		InputManager::onWindowEntry();
	else
		InputManager::onWindowLeft();
}

void Engine::handleMouseMove(int x, int y)
{
	InputManager::handleMouseMove(x, y);

	float mouseSensitivity = 0.01f;
	if (InputManager::mouseState[0]) {
		camera->rotate(-InputManager::mouseMoveY*mouseSensitivity, InputManager::mouseMoveX*mouseSensitivity, 0);
	}
}

void Engine::handleMouseClicked(int button, int state, int x, int y) {
	if(state == GLUT_DOWN)
		InputManager::handleMouseClicked(button, x, y);
	else {
		InputManager::handleMouseReleased(button, x, y);
	}
}

void Engine::onIdle() {
	Time::tick();
	ticks += Time::delta;
	float moveSpeed = 15;

	if (GetAsyncKeyState(0x57) & 0x8000) { // W
		camera->moveForward(moveSpeed*Time::delta);
	}

	if (GetAsyncKeyState(0x53) & 0x8000) { // S
		camera->moveForward(-moveSpeed*Time::delta);
	}

	if (GetAsyncKeyState(0x44) & 0x8000) { // D
		camera->moveRight(moveSpeed*Time::delta);
	}

	if (GetAsyncKeyState(0x41) & 0x8000) { // A
		camera->moveRight(-moveSpeed*Time::delta);
	}

	glutPostRedisplay();
}

void Engine::onRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLHelper::modelMatrix = glm::mat4();
	GLHelper::modelMatrix = glm::translate(GLHelper::modelMatrix, glm::vec3(0.1f, -0.5f, -5));
	GLHelper::modelMatrix = glm::rotate(GLHelper::modelMatrix, 0.0f, glm::vec3(0, 1, 0));

	Texture::bind("textures/car.png");
	testMesh->draw();

	glutSwapBuffers();
}

void Engine::onResize(int nw, int nh) {
	glViewport(0, 0, (GLsizei) nw, (GLsizei) nh);
	GLHelper::projectionMatrix = glm::perspective(45.0f, (float)nw/nh, 0.001f, 100.0f);
	cout << "Resize: "<<nw<<" "<<nh << endl;
}

void Engine::onClose() {

}
#include "Engine.hpp"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/ilut.h>
#include <iostream>
#include "Display.hpp"
#include "rendering/GLHelper.hpp"
#include "util/Time.hpp"
#include "Camera.hpp"
#include "rendering/texture/Texture.hpp"
#include "InputManager.hpp"
#include "rendering/geometry/Mesh.hpp"
#include "loader/OBJLoader.hpp"
#include "Resources.hpp"
#include "rendering/font/FontRenderer.hpp"
#include "debug/DebugConsole.hpp"
#include "script/Scripts.hpp"
#include "scene/Scene.hpp"
#include "gameobject/component/Component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Display* Engine::display;
Camera* camera = new Camera();

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
	Scripts::destroy();
}

void Engine::run() {
	glutMainLoop();
}

void Engine::createDisplay(char* _title, int _width, int _height) {
	display = new Display(_title, _width, _height);
	display->init();

	glutCloseFunc(onClose);
	glutIdleFunc(update);
	glutKeyboardFunc(handleKeyPressed);
	glutKeyboardUpFunc(handleKeyReleased);
	glutSpecialFunc(handleSpecialPressed);
	glutSpecialUpFunc(handleSpecialReleased);
	glutReshapeFunc(onResize);
	glutDisplayFunc(onRender);
	glutPassiveMotionFunc(handleMouseMove);
	glutMotionFunc(handleMouseMove);
	glutMouseFunc(handleMouseAction);
	glutEntryFunc(handleWindowEntry);

	Component::registerAll();
	Scripts::init();

	Resources resourceManagerNative = Resources();
	resourceManagerNative.loadFromFile("_native/resources.json");
	resourceManagerNative.perform();

	Resources resourceManager = Resources();
	resourceManager.loadFromFile("resources.json");
	resourceManager.perform();

	ShaderManager::use("_native/shaders/default.shader");
	DebugConsole::instance.init();

	cout << "GL Error Code: " << glGetError() << " - " << gluErrorString(glGetError()) << endl;
}

void Engine::handleWindowEntry(int state) {
	if (state == GLUT_ENTERED)
		InputManager::onWindowEntry();
	else
		InputManager::onWindowLeft();
}

void Engine::handleKeyPressed(unsigned char key, int x, int y) {
	InputManager::handleKeyPressed(key);
}

void Engine::handleKeyReleased(unsigned char key, int x, int y) {
	InputManager::handleKeyReleased(key);
}

void Engine::handleSpecialPressed(int key, int x, int y) {
	InputManager::handleSpecialPressed(key);
}

void Engine::handleSpecialReleased(int key, int x, int y) {
	InputManager::handleSpecialReleased(key);
}

void Engine::handleMouseMove(int x, int y)
{
	InputManager::handleMouseMove(x, y);

	float mouseSensitivity = 0.01f;
	if (InputManager::mouseState[0]) {
		camera->rotate(-InputManager::mouseMoveY*mouseSensitivity, InputManager::mouseMoveX*mouseSensitivity, 0);
	}
}

void Engine::handleMouseAction(int button, int state, int x, int y) {
	if(state == GLUT_DOWN)
		InputManager::handleMouseClicked(button, x, y);
	else {
		InputManager::handleMouseReleased(button, x, y);
	}
}

void Engine::update() {
	Time::tick();
	ticks += Time::delta;
	Scripts::update();
	float moveSpeed = 15;

	if (InputManager::isKeyDown(87) || InputManager::isKeyDown(119)) { //W
		camera->moveForward(moveSpeed*Time::delta);
	}

	if (InputManager::isKeyDown(83) || InputManager::isKeyDown(115)) { //S
		camera->moveForward(-moveSpeed*Time::delta);
	}

	if (InputManager::isKeyDown(65) || InputManager::isKeyDown(97)) { //A
		camera->moveRight(-moveSpeed*Time::delta);
	}

	if (InputManager::isKeyDown(68) || InputManager::isKeyDown(100)) { //D
		camera->moveRight(moveSpeed*Time::delta);
	}

	Scene::current->update();
	DebugConsole::instance.update();

	glutPostRedisplay();
}

void Engine::onRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLHelper::perspective(45.0f, (float)display->getWidth() / display->getHeight(), 0.001f, 100.0f);
	GLHelper::identityModel();
	GLHelper::translate(0.1f, -0.5f, -5.0f);
	GLHelper::rotate(0.0f, 0, 1, 0);
	GLHelper::currentState.viewMatrix = camera->getViewMatrix();

	ShaderManager::use("_native/shaders/default.shader");
	Texture::bind("textures/car.png");
	//Resources::MODEL["models/car.obj"]->draw();
	
	Scene::current->draw();

	GLHelper::ortho(0, display->getWidth(), 0, display->getHeight());
	GLHelper::identityModel();
	GLHelper::currentState.viewMatrix = glm::mat4();

	GLHelper::saveState();
		GLHelper::identityModel();
		GLHelper::translate(display->getWidth()-50, display->getHeight()-20, 0);
		FontRenderer::fontSize = 16;
		FontRenderer::drawText("v0.1.0", "_native/fonts/Arial.fnt", "_native/shaders/text-default.shader");
	GLHelper::loadState();

	DebugConsole::instance.draw();

	glutSwapBuffers();
}

void Engine::onResize(int nw, int nh) {
	glViewport(0, 0, (GLsizei) nw, (GLsizei) nh);
	display->setWidth(nw);
	display->setHeight(nh);
}

void Engine::onClose() {

}
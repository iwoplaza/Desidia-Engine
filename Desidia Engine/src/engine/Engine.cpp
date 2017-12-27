#include "Engine.hpp"
#include "Display.hpp"
#include "Camera.hpp"
#include "Resources.hpp"
#include "InputManager.hpp"
#include "gameobject/component/Component.hpp"
#include "gameobject/component/ComponentCamera.hpp"
#include "rendering/GLHelper.hpp"
#include "rendering/texture/Texture.hpp"
#include "rendering/geometry/Mesh.hpp"
#include "rendering/font/FontRenderer.hpp"
#include "rendering/framebuffer/Framebuffer.hpp"
#include "physics/collider/Collider.hpp"
#include "script/Scripts.hpp"
#include "loader/OBJLoader.hpp"
#include "debug/DebugConsole.hpp"
#include "scene/Scene.hpp"
#include "util/Time.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/ilut.h>
#include <iostream>

using namespace std;

Display* Engine::display;
Camera* camera = new Camera();
Framebuffer* testFramebuffer;

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
	Collider::registerAll();
	Scripts::init();

	Resources resourceManagerNative = Resources();
	resourceManagerNative.loadFromFile("_native/resources.json");
	resourceManagerNative.perform();

	Resources resourceManager = Resources();
	resourceManager.loadFromFile("resources.json");
	resourceManager.perform();

	ShaderManager::use("_native/shaders/default.shader");
	DebugConsole::instance.init();

	testFramebuffer = new Framebuffer(256, 256);

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

	Scene::current->onMouseMove();
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

	Scripts::update();
	Scene::current->update();
	DebugConsole::instance.update();

	glutPostRedisplay();
}

void Engine::onRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	testFramebuffer->bind();
	glViewport(0, 0, testFramebuffer->getWidth(), testFramebuffer->getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLHelper::perspective(45.0f, (float)display->getWidth() / display->getHeight(), 0.001f, 100.0f);
	GLHelper::identityModel();

	if (ComponentCamera::activeCamera != nullptr) {
		GLHelper::currentState.viewMatrix = ComponentCamera::activeCamera->getViewMatrix();
		GLHelper::currentState.projectionMatrix = ComponentCamera::activeCamera->getProjectionMatrix();
	}
	else {
		GLHelper::currentState.viewMatrix = glm::mat4();
	}

	ShaderManager::use("_native/shaders/default.shader");
	
	Scene::current->draw();

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, testFramebuffer->getWidth(), testFramebuffer->getHeight(), 0, 0, display->getWidth(), display->getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
	testFramebuffer->unbind();

	glViewport(0, 0, display->getWidth(), display->getHeight());
	GLHelper::ortho(0, display->getWidth(), 0, display->getHeight());
	GLHelper::identityModel();
	GLHelper::currentState.viewMatrix = glm::mat4();

	GLHelper::saveState();
	GLHelper::identityModel();
	GLHelper::translate(display->getWidth() - 62, display->getHeight() - 20, 0);
	FontRenderer::fontSize = 16;
	FontRenderer::drawText("v0.1.0", DebugConsole::CODE_FONT, "_native/shaders/text-default.shader");
	GLHelper::loadState();

	DebugConsole::instance.draw();

	glutSwapBuffers();
}

void Engine::onResize(int nw, int nh) {
	glViewport(0, 0, (GLsizei) nw, (GLsizei) nh);
	display->setWidth(nw);
	display->setHeight(nh);

	if (ComponentCamera::activeCamera != nullptr)
		ComponentCamera::activeCamera->updateProjection();
}

void Engine::onClose() {
}
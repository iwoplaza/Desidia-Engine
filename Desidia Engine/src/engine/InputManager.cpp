#include "InputManager.hpp"
#include "debug/DebugConsole.hpp"
#include "scene/Scene.hpp"
#include <iostream>
#include <GL/freeglut.h>

using namespace std;

bool InputManager::keyStates[KEYBOARD_KEYS_COUNT];
int InputManager::mouseLastX = 0,
	InputManager::mouseLastY = 0;
int InputManager::mouseX = 0,
	InputManager::mouseY = 0;
int InputManager::mouseMoveX = 0,
	InputManager::mouseMoveY = 0;
bool InputManager::mouseState[MOUSE_BUTTON_COUNT];

bool InputManager::mouseLocked = false;

void InputManager::init() {
	for (int i = 0; i < KEYBOARD_KEYS_COUNT; i++) {
		keyStates[i] = false;
	}

	for (int i = 0; i < MOUSE_BUTTON_COUNT; i++) {
		mouseState[i] = false;
	}
}

void InputManager::onWindowEntry() {

}

void InputManager::onWindowLeft() {
	InputManager::mouseLocked = false;
}

void InputManager::handleKeyPressed(unsigned char key) {
	if (DebugConsole::instance.handleKeyPressed(key))
		return;

	keyStates[key] = true;
}

void InputManager::handleKeyReleased(unsigned char key) {
	if (DebugConsole::instance.handleKeyReleased(key))
		return;

	keyStates[key] = false;
}


void InputManager::handleSpecialPressed(int key) {
	if (DebugConsole::instance.handleSpecialPressed(key))
		return;

	if (key == GLUT_KEY_F2) {
		DebugConsole::instance.open();
	}

	if (key == GLUT_KEY_F3) {
		Scene::current->reload();
	}
}

void InputManager::handleSpecialReleased(int key) {
	if (DebugConsole::instance.handleSpecialReleased(key))
		return;
}


void InputManager::handleMouseMove(int x, int y) {
	if (mouseLocked == false) {
		mouseLastX = x;
		mouseLastY = y;
		mouseLocked = true;
	}
	
	mouseX = x;
	mouseY = y;
	mouseMoveX = (x - mouseLastX);
	mouseMoveY = (mouseLastY - y);
	mouseLastX = x;
	mouseLastY = y;
}

void InputManager::handleMouseClicked(int button, int x, int y) {
	if (button >= MOUSE_BUTTON_COUNT)
		return;

	mouseState[button] = true;
}

void InputManager::handleMouseReleased(int button, int x, int y) {
	if (button >= MOUSE_BUTTON_COUNT)
		return;

	mouseState[button] = false;
}

bool InputManager::isKeyDown(unsigned char key) {
	return keyStates[key];
}

bool InputManager::isKeyDownCase(unsigned char key) {
	return isKeyDown(key) || isKeyDown(key + 32);
}
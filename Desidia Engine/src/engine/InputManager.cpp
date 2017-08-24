#include "InputManager.hpp"
#include <iostream>

using namespace std;

int InputManager::mouseLastX = 0,
	InputManager::mouseLastY = 0;
int InputManager::mouseX = 0,
	InputManager::mouseY = 0;
int InputManager::mouseMoveX = 0,
	InputManager::mouseMoveY = 0;
bool InputManager::mouseState[MOUSE_BUTTON_COUNT];

bool InputManager::mouseLocked = false;

void InputManager::init() {
	for (int i = 0; i < MOUSE_BUTTON_COUNT; i++) {
		mouseState[i] = false;
	}
}

void InputManager::onWindowEntry() {

}

void InputManager::onWindowLeft() {
	InputManager::mouseLocked = false;
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
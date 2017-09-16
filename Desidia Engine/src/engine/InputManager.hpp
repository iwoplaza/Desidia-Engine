#pragma once
#define MOUSE_BUTTON_COUNT 3
#define KEYBOARD_KEYS_COUNT 256

class InputManager {
	public:
		enum MouseButton { LEFT_MOUSE_BUTTON, MIDDLE_MOUSE_BUTTON, RIGHT_MOUSE_BUTTON };

		static int mouseLastX, mouseLastY;
		static int mouseX, mouseY;
		static int mouseMoveX, mouseMoveY;
		static bool keyStates[KEYBOARD_KEYS_COUNT];
		static bool mouseState[MOUSE_BUTTON_COUNT];
		static bool mouseLocked;

		static void init();
		static void handleKeyPressed(unsigned char key);
		static void handleKeyReleased(unsigned char key);
		static void handleSpecialPressed(int key);
		static void handleSpecialReleased(int key);
		static void handleMouseMove(int x, int y);
		static void handleMouseClicked(int button, int x, int y);
		static void handleMouseReleased(int button, int x, int y);
		static void onWindowEntry();
		static void onWindowLeft();

		static bool isKeyDown(unsigned char key);
		static bool isKeyDownCase(unsigned char key);
};
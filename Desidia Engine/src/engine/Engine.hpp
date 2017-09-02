#pragma once

class Display;

class Engine {
	public:
		static void init(int, char**);
		static void destroy();
		static void createDisplay(char* _title, int _width, int _height);
		static void run();

		static void onRender();
		static void onResize(int nw, int nh);
		/*
			Called everytime the cpu is free from work, so it can perform another step.
			In other words, a tick() function
		*/
		static void update();
		static void onClose();
		static void handleKeyPressed(unsigned char key, int x, int y);
		static void handleKeyReleased(unsigned char key, int x, int y);
		static void handleSpecialPressed(int key, int x, int y);
		static void handleSpecialReleased(int key, int x, int y);
		static void handleMouseMove(int x, int y);
		static void handleMouseAction(int button, int state, int x, int y);
		static void handleWindowEntry(int state);

		static Display* display;
};
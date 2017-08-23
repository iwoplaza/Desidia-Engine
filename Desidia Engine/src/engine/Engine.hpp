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
		static void onIdle();
		static void onClose();

		static Display* display;
};
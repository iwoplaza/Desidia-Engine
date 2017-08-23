#pragma once

class Display {
	protected:
		int width;
		int height;
		char* title;
	public:
		Display(char* _title, int _width, int _height);
		~Display();

		void init();
		void destroy();
		void display();
};
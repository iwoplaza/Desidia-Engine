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

		void setWidth(int);
		void setHeight(int);
		int getWidth();
		int getHeight();
};
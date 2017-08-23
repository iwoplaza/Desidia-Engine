// Desidia Engine.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "engine\Engine.hpp"

#pragma comment(lib, "glew32.lib")

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char** argv)
{
	Engine::init(argc, argv);
	Engine::createDisplay("Desida Engine 0.1.0", WIDTH, HEIGHT);
	Engine::run();

    return 0;
}
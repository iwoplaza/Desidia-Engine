#include "Time.hpp"
#include <GL\freeglut.h>
#include <algorithm>

using namespace std;

int Time::lastTime;
float Time::delta;
float Time::deltaCap = 1.0f / 60.0f;
float Time::fixedDelta = 0.001f;

void Time::tick() {
	int now = glutGet(GLUT_ELAPSED_TIME);
	delta = max(0.0f, min(((float)(now - lastTime)) / 1000.0f, deltaCap));
	lastTime = now;
}
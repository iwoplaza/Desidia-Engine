#pragma once



class Time {
	public:
		static int lastTime;
		static float delta;
		static float deltaCap;

		static void tick();
};
#pragma once



class Time {
	public:
		static int lastTime;
		static float delta;
		static float deltaCap;
		// Delta time used in physics calculations.
		static float fixedDelta;

		static void tick();
};
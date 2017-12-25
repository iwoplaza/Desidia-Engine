#pragma once

#include "../util/Vector3.hpp"
#include <vector>

class PhysicsBody;

/*
	Objects in one space can interact with eachother.
*/
class PhysicsSpace {
	protected:
		std::vector<PhysicsBody*> m_physicsBodies;
		Vector3 m_gravity;
		float m_timer;
		float m_stepSize;

		void simulate();
	public:
		PhysicsSpace();

		void init();
		void update();
		void addBody(PhysicsBody* _physicsBody);
		void removeBody(PhysicsBody* _physicsBody);
		void drawGizmos();

		Vector3 getGravity();
		std::vector<PhysicsBody*> getBodies();
		void setGravity(Vector3 _gravity);
};
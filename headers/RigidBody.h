#pragma once

#include <array>
#include <string>
#include "Vector2d.h"

namespace Engine2d {
	class RigidBody {
	public:
		// std::string name;
		// Vector2d position; // CM position
		// Vector2d dx;
		// float theta;
		// float dtheta;
		// bool collision;

		RigidBody() {};
		virtual ~RigidBody() {};
		virtual void updatePosition() {};
		virtual void update() {};
		virtual void draw() const {};
		virtual void operator=(RigidBody other) {};
	// protected:
	// 	float mass;
	// 	float invMass;
	// 	bool isStatic;
	};
}
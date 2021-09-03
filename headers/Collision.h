#pragma once
#include <vector>
#include "Rectangle.h"

namespace Engine2d {
	namespace collision {
		// Returns true for collision & false for no collision
		bool withRect(Rectangle &rect, Rectangle &other);
		// Returns fraction (0 < returnVal <= 1) by which the velocity vector had to be shortened to prevent collision
		float preventPenetration(Rectangle &rect, Rectangle &other);
		// Returns absolute value of the impulse vector for these inertias
		float absImpulse(const Vector2d vel_a, const Vector2d vel_b,
						 const float invMass_a, const float invMass_b,
						 const float rest_a, const float rest_b);
	}
}
#pragma once
#include <vector>
#include "Rectangle.h"

namespace Engine2d {
	namespace collision {
		bool withRect(Rectangle &rect, Rectangle &other);
		float absImpulse(const Vector2d vel_a, const Vector2d vel_b,
						 const float invMass_a, const float invMass_b,
						 const float rest_a, const float rest_b);
	}
}
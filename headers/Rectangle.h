#pragma once
#include <array>
#include "Vector2d.h"

namespace Engine2d {
	class Rectangle {
	public:
		std::array<Vector2d, 4> P;
		Rectangle(const float x, const float y, const float width, const float height);
		void draw();
		void applyForce(Vector2d F);
	private:
		float width, height;
		float mass;
		float radius;
	};
}
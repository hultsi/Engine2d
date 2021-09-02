#pragma once
#include <array>
#include <string>
#include "Vector2d.h"

namespace Engine2d {
	class Rectangle {
	public:
		std::string name;
		std::array<Vector2d, 4> P;
		Vector2d position; // CM position
		Vector2d dx;
		bool collision;

		Rectangle(const float x, const float y, const float width, const float height, const float angle,
				const bool isStatic, const float mass, std::string name);
		void updatePosition();
		void update();
		void draw() const;
		void applyForce(Vector2d F);
	private:
		float width, height;
		float angle;
		float centerAngle_1; // calculated with lines going from CM to corner points
		float centerAngle_2; // calculated with lines going from CM to corner points
		float mass;
		float invMass;
		float radius;
		bool isStatic;
	};
}
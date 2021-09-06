#pragma once
#include <array>
#include <string>
// #include <tuple>
#include "Vector2d.h"
#include "RigidBody.h"

namespace Engine2d {
	class Rectangle : public RigidBody {
	public:
		std::string name;
		// std::tuple<RigidBody*, Vector2d*> colliders;
		std::array<Vector2d, 4> P;
		Vector2d position; // CM position
		Vector2d dx;
		float theta;
		float dtheta;
		bool collision;

		Rectangle() {};
		Rectangle(const float x, const float y, const float width, const float height, const float theta,
				const bool isStatic, const float mass, std::string name);
		~Rectangle() {};
		void updatePosition();
		void update();
		void draw() const;
		void operator=(Rectangle other);
	private:
		float width, height;
		float centerAngle_1; // calculated with lines going from CM to corner points
		float centerAngle_2; // calculated with lines going from CM to corner points
		float mass;
		float invMass;
		float radius;
		bool isStatic;
	};
}
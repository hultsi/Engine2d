#pragma once
#include <math.h>

class Vector2d {
	public:
		float x = 0;
		float y = 0;
		float angle = 0;

		Vector2d() {};
		Vector2d(float x, float y);

		Vector2d operator+(const Vector2d &other) const;
		Vector2d operator-(const Vector2d &other) const;
		Vector2d operator*(const float scalar) const;
		bool operator==(const Vector2d &other) const;
		bool operator!=(const Vector2d &other) const;
		void operator=(const Vector2d &other);

		float getLength() const;	
		float dot(const Vector2d &other) const;
		Vector2d cross(const Vector2d &other) const;

		void rotate(double radians);
		void normalize();
};
#pragma once
#include <math.h>

class Vector2d {
public:
	float x = 0;
	float y = 0;

	Vector2d() {};
	Vector2d(float x, float y);

	Vector2d operator+(const Vector2d &other) const;
	Vector2d operator-(const Vector2d &other) const;
	Vector2d operator*(const float scalar) const;
	Vector2d operator/(const float scalar) const;
	bool operator==(const Vector2d &other) const;
	bool operator!=(const Vector2d &other) const;
	void operator=(const Vector2d &other);
	Vector2d& operator+=(const Vector2d &other);
	Vector2d& operator-=(const Vector2d &other);

	float getAngle() const;
	float getLength() const;	
	float dot(const Vector2d &other) const;
	Vector2d cross(const Vector2d &other) const;

	void rotate(double radians);
	void normalize();
};

////////////////////////////////////////////////////
// Global operator overloads for scalar*Vector2d //
//////////////////////////////////////////////////
extern Vector2d operator*(const float &scalar, const Vector2d &vec);
extern Vector2d operator/(const float &scalar, const Vector2d &vec);
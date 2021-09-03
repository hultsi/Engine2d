#include "Vector2d.h"

Vector2d::Vector2d(float x, float y) {
    this->x = x;
    this->y = y;
    this->angle = std::atan2(this->y, this->x);
    (this->angle > 0 ? this->angle : (2 * M_PI + this->angle));
}

Vector2d Vector2d::operator+(const Vector2d &other) const {
	return Vector2d(this->x + other.x, this->y + other.y);
}

Vector2d Vector2d::operator-(const Vector2d &other) const {
    return Vector2d(this->x - other.x, this->y - other.y);
}

Vector2d Vector2d::operator*(const float scalar) const {
    return Vector2d(this->x * scalar, this->y * scalar);
}

Vector2d Vector2d::operator/(const float scalar) const {
    return Vector2d(this->x / scalar, this->y / scalar);
}

bool Vector2d::operator==(const Vector2d &other) const {
    if (this->x == other.x && this->y == other.y)
		return true;
    return false;
}

bool Vector2d::operator!=(const Vector2d &other) const {
    if (this->x == other.x && this->y == other.y)
		return false;
    return true;
}

void Vector2d::operator=(const Vector2d &other) {
	this->x = other.x;
	this->y = other.y;
	this->angle = other.angle;
}

float Vector2d::getLength() const {
    return std::sqrt(this->x * this->x + this->y * this->y);
}

float Vector2d::dot(const Vector2d &other) const {
	return this->x*other.x + this->y*other.y;
}

Vector2d Vector2d::cross(const Vector2d &other) const {
    return Vector2d(this->x * other.y, -this->y * other.x);
}

void Vector2d::rotate(double radians) {
	const float len = getLength();
	this->angle += radians;
    this->x = len * std::cos(this->angle);
    this->y = len * std::sin(this->angle);
}

void Vector2d::normalize() {
	const float len = this->getLength();
    this->x = this->x / len;
    this->y = this->y / len;
}

////////////////////////////////////////////////////
// Global operator overloads for scalar*Vector2d //
//////////////////////////////////////////////////
Vector2d operator*(const float &scalar, const Vector2d &vec) {
    return Vector2d(vec.x * scalar, vec.y * scalar);
}
Vector2d operator/(const float &scalar, const Vector2d &vec) {
    return Vector2d(vec.x / scalar, vec.y / scalar);
}
#include "Vector2d.h"

Vector2d::Vector2d(float x, float y) {
    this->x = x;
    this->y = y;
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
}

Vector2d &Vector2d::operator+=(const Vector2d &other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2d &Vector2d::operator-=(const Vector2d &other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

float Vector2d::getAngle() const {
	const float angle = std::atan2(this->y, this->x);
    return (angle > 0 ? angle : (2 * M_PI + angle));
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
	const float angle = getAngle() + radians;
    this->x = len * std::cos(angle);
    this->y = len * std::sin(angle);
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
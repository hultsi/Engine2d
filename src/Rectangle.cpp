#include <string>
#include "Rectangle.h"
#include "Vector2d.h"
#include "glfw3.h"
#include <iostream>

namespace Engine2d {
	Rectangle::Rectangle(const float x, const float y, const float width, const float height,
				const float angle, const bool isStatic, const float mass, std::string name) {
		this->position.x = x;
		this->position.y = y;
		this->radius = std::sqrt(width*width + height*height) / 2;
		this->centerAngle_1 = 2 * std::acos(height / (2*radius));
    	this->centerAngle_2 = M_PI - this->centerAngle_1;
		this->angle = angle;
		this->dx.x = 0;
		this->dx.y = 0;
		this->updatePosition();
		this->isStatic = isStatic;
		this->mass = mass;
		this->invMass = 1/mass;
		this->name = name;
		this->collision = false;
	}

	void Rectangle::updatePosition() {
		this->position = this->position + this->dx;

		this->P[0].x = position.x + radius * std::cos(angle + centerAngle_1 + centerAngle_2 * 3 / 2);
		this->P[0].y = position.y + radius * std::sin(angle + centerAngle_1 + centerAngle_2 * 3 / 2);

		this->P[1].x = position.x + radius * std::cos(angle + 2 * centerAngle_1 + centerAngle_2 * 3 / 2);
		this->P[1].y = position.y + radius * std::sin(angle + 2 * centerAngle_1 + centerAngle_2 * 3 / 2);

		this->P[2].x = position.x + radius * std::cos(angle + centerAngle_2 / 2);
		this->P[2].y = position.y + radius * std::sin(angle + centerAngle_2 / 2);

		this->P[3].x = position.x + radius * std::cos(angle + centerAngle_1 + centerAngle_2 / 2);
		this->P[3].y = position.y + radius * std::sin(angle + centerAngle_1 + centerAngle_2 / 2);
	}

	void Rectangle::update() {
		updatePosition();

	}

	void Rectangle::draw() const {
		GLfloat lineVertices[] = {
			P[0].x, P[0].y,
			P[1].x, P[1].y,
			P[1].x, P[1].y,
			P[2].x, P[2].y,
			P[2].x, P[2].y,
			P[3].x, P[3].y,
			P[3].x, P[3].y,
			P[0].x, P[0].y
		};

		glColor3f(1.0f, 1.0f, 1.0f);
		if (this->collision)
			glColor3f(1.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		glDrawArrays(GL_LINES, 0, 8);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void applyForce(Vector2d F) {

	}
}
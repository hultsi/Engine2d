#include "glfw3.h"
#include "DebugLine.h"
#include <cmath>
#include <iostream>

namespace Engine2d {
	DebugLine::DebugLine(float x1, float y1, float x2, float y2, std::string name) {
		this->name = name;
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	DebugLine::DebugLine(Vector2d &pos, Vector2d &dx, float scale, std::string name) {
		this->name = name;
		this->pos = &pos;
		this->dx = &dx;
		this->scale = scale;
	}

	void DebugLine::draw() {
		if (this->pos != nullptr && this->dx != nullptr) {
			this->x1 = this->pos->x;
			this->y1 = this->pos->y;
			this->x2 = this->pos->x + scale*this->dx->x;
			this->y2 = this->pos->y + scale*this->dx->y;
		}
		GLfloat lineVertices[4] {
			this->x1, this->y1,
			this->x2, this->y2
		};
		glColor3f(1.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		glDrawArrays(GL_LINES, 0, 2);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
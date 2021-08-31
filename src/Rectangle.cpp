#include "Engine2d.h"
#include "Vector2d.h"
#include "glfw3.h"

namespace Engine2d {
	Rectangle::Rectangle(const float x, const float y, const float width, const float height) {
		this->P[0] = Vector2d(x,y);
		this->P[1] = Vector2d(x,y+height);
		this->P[2] = Vector2d(x+width,y+height);
		this->P[3] = Vector2d(x+width,y);
	}

	void Rectangle::draw() {
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
		// if (collision)
		// glColor3f(1.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		glDrawArrays(GL_LINES, 0, 8);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
#include "glfw3.h"
#include "DebugCircle.h"
#include <string>
#include <cmath>

namespace Engine2d {
	DebugCircle::DebugCircle(float x, float y, float radius, std::string name) : x(x), y(y), radius(radius), name(name) {
		float theta = 2 * M_PI / 16;
		for (int i = 0; i < 32; i += 4) {
			lineVertices[i]     = x + radius * std::cos((i / 2) * theta);
			lineVertices[i + 1] = y + radius * std::sin((i / 2) * theta);
			lineVertices[i + 2] = x + radius * std::cos((i / 2 + 2) * theta);
			lineVertices[i + 3] = y + radius * std::sin((i / 2 + 2) * theta);
		}
	}

	void DebugCircle::draw() const {
		glColor3f(1.0f, 0.0f, 0.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		glDrawArrays(GL_LINES, 0, 16);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
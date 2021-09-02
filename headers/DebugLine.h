#pragma once
#include "glfw3.h"
#include <string>

namespace Engine2d {
	class DebugLine
	{
	public:
		float x1, y1, x2, y2;
		std::string name;

		GLfloat lineVertices[4];

		DebugLine(float x1, float y1, float x2, float y2, std::string name = "");

		void draw();
	};
}
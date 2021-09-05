#pragma once
#include "glfw3.h"
#include "Vector2d.h"
#include <string>

namespace Engine2d {
	class DebugLine {
	public:
		float x1, y1, x2, y2;
		float scale = 1;
		Vector2d *pos = nullptr;
		Vector2d *dx = nullptr;
		std::string name;

		DebugLine() {};
		// General form
		DebugLine(float x1, float y1, float x2, float y2, std::string name = "");
		// Useful form for making lines follow an object's position and pointing towards dx
		DebugLine(Vector2d &pos, Vector2d &dx, float scale, std::string name = "");
		void draw();
	};
}
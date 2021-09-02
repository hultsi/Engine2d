#pragma once
#include "glfw3.h"
#include "Engine2d.h"
#include <string>

namespace Engine2d {
	class DebugCircle {
		public:
			std::string name;
			GLfloat lineVertices[32];
			DebugCircle(float x, float y, float radius, std::string name = "");

			void draw() const;
		private:
			float x = 0;
			float y = 0;
			float radius = 0;
	};
}
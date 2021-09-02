#pragma once
#include <vector>
#include "Rectangle.h"
#include "DebugCircle.h"

namespace Engine2d {
	class GameControl {
		public:
			GameControl();
			Rectangle* createObject(Rectangle rect);
			DebugCircle* createObject(DebugCircle dbgCircle);
			void drawAll();
		private:
			unsigned int rectId = 0;
			unsigned int dbgCircleId = 0;
			std::vector<Rectangle> rectangles;
			std::vector<DebugCircle> debugCircles;
	};
}
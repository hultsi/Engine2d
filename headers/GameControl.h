#pragma once
#include <vector>
#include "Rectangle.h"

namespace Engine2d {
	class GameControl {
		public:
			GameControl();
			Rectangle* createObject(Rectangle rect);

			void drawAll();
		private:
			unsigned int rect_id = 0;
			std::vector<Rectangle> rectangles;
	};
}
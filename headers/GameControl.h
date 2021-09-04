#pragma once
#include <vector>
#include "Rectangle.h"
#if DEBUG == 1
	#include "DebugCircle.h"
#endif
namespace Engine2d {
	class GameControl {
		public:
			GameControl();
			Rectangle* createObject(Rectangle rect);
			
			void updateAll();
			void drawAll();

			#if DEBUG == 1
				DebugCircle* createObject(DebugCircle dbgCircle);
			#endif
		private:
			unsigned int rectId = 0;
			std::vector<Rectangle> rectangles;
			
			#if DEBUG==1
				unsigned int dbgCircleId = 0;
				std::vector<DebugCircle> debugCircles;
			#endif
	};
}
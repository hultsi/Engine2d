#pragma once
#include <vector>
#include <array>
#include "Rectangle.h"
#if DEBUG == 1
	#include "DebugCircle.h"
	#include "DebugLine.h"
#endif


namespace Engine2d {
	namespace Control {
		constexpr unsigned int MAX_RECTS = 500;
		extern unsigned int rectId;
		extern std::array<Rectangle, MAX_RECTS> rectangles;
		Rectangle* createObject(Rectangle rect);
		void updateAll();
		void drawAll();

		#if DEBUG == 1
			constexpr unsigned int MAX_DEBUG_CIRCLES = 500;
			constexpr unsigned int MAX_DEBUG_LINES = 2500; // should be at least 4*MAX_RECTS
			extern unsigned int dbgCircleId;
			extern std::array<DebugCircle, MAX_DEBUG_CIRCLES> debugCircles;
			extern unsigned int dbgLineId;
			extern std::array<DebugLine, MAX_DEBUG_LINES> debugLines;
			DebugCircle* createObject(DebugCircle dbgCircle);
			DebugLine* createObject(DebugLine dbgLine);
		#endif
	}
}
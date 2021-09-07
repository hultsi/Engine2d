#include <vector>
#include <array>
#include <string>
#include <memory>
#include "Control.h"
#include "Rectangle.h"
#include "Collision.h"

#if DEBUG == 1
	#include <iostream>
	#include "DebugCircle.h"
	#include "DebugLine.h"
#endif

namespace Engine2d::Control {
	unsigned int rectId = 0;
	std::array<Rectangle, Engine2d::Control::MAX_RECTS> rectangles;

	#if DEBUG == 1
		unsigned int dbgCircleId = 0;
		std::array<DebugCircle, Engine2d::Control::MAX_DEBUG_CIRCLES> debugCircles;
		unsigned int dbgLineId = 0;
		std::array<DebugLine, Engine2d::Control::MAX_DEBUG_LINES> debugLines;
	#endif
}

namespace Engine2d {
	Rectangle* Control::createObject(Rectangle rect) {
		if (rect.name == "")
			rect.name = std::string("rect_") + std::to_string(Engine2d::Control::rectId);
		Engine2d::Control::rectangles[rectId] = rect;
		#if DEBUG == 1
			for (int i = 0; i < 4; ++i)
				Engine2d::Control::createObject(Engine2d::DebugLine(rectangles[rectId].P[i], rectangles[rectId].dx, 30, ""));
		#endif
		++Engine2d::Control::rectId;
		return &rectangles[rectId-1];
	}

	void Control::updateAll() {
		for (int i = 0; i < Engine2d::Control::rectId; ++i)
			rectangles[i].update();

		// Reset collision. Todo: shouldn't be necessary?
		for (int i = 0; i < Engine2d::Control::rectId; ++i)
			Engine2d::Control::rectangles[i].collision = false;

		std::unique_ptr<Vector2d> normal = std::unique_ptr<Vector2d>(new Vector2d(0,0));
		std::unique_ptr<Vector2d> point = std::unique_ptr<Vector2d>(new Vector2d(0,0));
		for (int i = 0; i < Engine2d::Control::rectId - 1; ++i) {
			for (int k = i+1; k < Engine2d::Control::rectId; ++k) {
				const bool collision = Engine2d::collision::withRect(Engine2d::Control::rectangles[i], Engine2d::Control::rectangles[k]);
				if (collision) {
					const float fraction = Engine2d::collision::preventPenetration(Engine2d::Control::rectangles[i], Engine2d::Control::rectangles[k]);
					const float dist = Engine2d::collision::getCollisionNormal(
						Engine2d::Control::rectangles[i], 
						Engine2d::Control::rectangles[k],
						point,
						normal
					);
					std::cout << normal->x << " " << normal->y << "\n";
					// Backtrack every object's position by -velocity*fraction --> probably ?? or not??
					// for (int j = 0; j < Engine2d::Control::rectangles.size(); ++j) {
					// 	if (&Engine2d::Control::rectangles[j] != &Engine2d::Control::rectangles[i] &&
					// 		&Engine2d::Control::rectangles[j] != &Engine2d::Control::rectangles[k]) {
					// 		Engine2d::Control::rectangles[j].position = Engine2d::Control::rectangles[j].position - fraction * Engine2d::Control::rectangles[j].dx;
					// 	}
					// }
					i = -1;
					break;
				}
			}
		}
	}

	void Control::drawAll() {
		for (int i = 0; i < Engine2d::Control::rectId; ++i)
			rectangles[i].draw();

		#if DEBUG == 1
			for (int i = 0; i < Engine2d::Control::dbgCircleId; ++i)
				debugCircles[i].draw();
			for (int i = 0; i < Engine2d::Control::dbgLineId; ++i)
				debugLines[i].draw();
		#endif
	}


	#if DEBUG == 1
		DebugCircle* Control::createObject(DebugCircle dbgCircle) {
			if (dbgCircle.name == "")
				dbgCircle.name = std::string("dbgCircle_") + std::to_string(Engine2d::Control::dbgCircleId);
			Engine2d::Control::debugCircles[dbgCircleId] = dbgCircle;
			++Engine2d::Control::dbgCircleId;
			return &Engine2d::Control::debugCircles[dbgCircleId-1];
		}

		DebugLine* Control::createObject(DebugLine dbgLine) {
			if (dbgLine.name == "")
				dbgLine.name = std::string("dbgLine_") + std::to_string(Engine2d::Control::dbgLineId);
			Engine2d::Control::debugLines[dbgLineId] = dbgLine;
			++Engine2d::Control::dbgLineId;
			return &Engine2d::Control::debugLines[dbgLineId-1];
		}
	#endif
}
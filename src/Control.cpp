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
	std::array<Rectangle, Control::MAX_RECTS> rectangles;

	#if DEBUG == 1
		unsigned int dbgCircleId = 0;
		std::array<DebugCircle, Control::MAX_DEBUG_CIRCLES> debugCircles;
		unsigned int dbgLineId = 0;
		std::array<DebugLine, Control::MAX_DEBUG_LINES> debugLines;
	#endif
}

namespace Engine2d {
	Rectangle* Control::createObject(Rectangle rect) {
		if (rect.name == "")
			rect.name = std::string("rect_") + std::to_string(Control::rectId);
		Control::rectangles[rectId] = rect;
		#if DEBUG == 1
			for (int i = 0; i < 4; ++i)
				Control::createObject(DebugLine(rectangles[rectId].P[i], rectangles[rectId].dx, 30, ""));
		#endif
		++Control::rectId;
		return &rectangles[rectId-1];
	}

	void Control::updateAll() {
		for (int i = 0; i < Control::rectId; ++i)
			rectangles[i].update();

		// Reset collision. Todo: shouldn't be necessary?
		for (int i = 0; i < Control::rectId; ++i)
			Engine2d::Control::rectangles[i].collision = false;

		std::unique_ptr<Vector2d> normal_1 = std::unique_ptr<Vector2d>(new Vector2d(0,0));
		std::unique_ptr<Vector2d> normal_2 = std::unique_ptr<Vector2d>(new Vector2d(0,0));
		std::unique_ptr<Vector2d> point = std::unique_ptr<Vector2d>(new Vector2d(0,0));
		for (int i = 0; i < Control::rectId - 1; ++i) {
			for (int k = i+1; k < Control::rectId; ++k) {
				const bool collision = collision::withRect(Control::rectangles[i], Control::rectangles[k]);
				if (collision) {
					const float fraction = collision::preventPenetration(Control::rectangles[i], Control::rectangles[k]);
					collision::getCollisionNormal(
						Control::rectangles[i], 
						Control::rectangles[k],
						normal_1,
						normal_2,
						point
					);
					// const Rectangle* R2 = &rectangles[k]; // for debugging
					const float impulse = collision::absImpulse(
						Control::rectangles[i].dx,
						Control::rectangles[k].dx,
						Control::rectangles[i].invMass,
						Control::rectangles[k].invMass,
						Control::rectangles[i].restitution,
						Control::rectangles[k].restitution
					);
					Control::rectangles[i].dx = Control::rectangles[i].dx + std::abs(impulse)*(*normal_1)/Control::rectangles[i].mass;
					Control::rectangles[k].dx = Control::rectangles[k].dx + std::abs(impulse)*(*normal_2)/Control::rectangles[k].mass;
					// Backtrack every object's position by -velocity*fraction --> probably ?? or not??
					// for (int j = 0; j < Control::rectangles.size(); ++j) {
					// 	if (&Control::rectangles[j] != &Control::rectangles[i] &&
					// 		&Control::rectangles[j] != &Control::rectangles[k]) {
					// 		Control::rectangles[j].position = Control::rectangles[j].position - fraction * Control::rectangles[j].dx;
					// 	}
					// }
					i = -1;
					break;
				}
			}
		}
	}

	void Control::drawAll() {
		for (int i = 0; i < Control::rectId; ++i)
			rectangles[i].draw();

		#if DEBUG == 1
			for (int i = 0; i < Control::dbgCircleId; ++i)
				debugCircles[i].draw();
			for (int i = 0; i < Control::dbgLineId; ++i)
				debugLines[i].draw();
		#endif
	}


	#if DEBUG == 1
		DebugCircle* Control::createObject(DebugCircle dbgCircle) {
			if (dbgCircle.name == "")
				dbgCircle.name = std::string("dbgCircle_") + std::to_string(Control::dbgCircleId);
			Control::debugCircles[dbgCircleId] = dbgCircle;
			++Control::dbgCircleId;
			return &Control::debugCircles[dbgCircleId-1];
		}

		DebugLine* Control::createObject(DebugLine dbgLine) {
			if (dbgLine.name == "")
				dbgLine.name = std::string("dbgLine_") + std::to_string(Control::dbgLineId);
			Control::debugLines[dbgLineId] = dbgLine;
			++Control::dbgLineId;
			return &Control::debugLines[dbgLineId-1];
		}
	#endif
}
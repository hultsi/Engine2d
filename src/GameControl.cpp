#include <vector>
#include "GameControl.h"
#include "Rectangle.h"
#include "DebugCircle.h"
#include "Collision.h"

namespace Engine2d {
	GameControl::GameControl() {};

	Rectangle* GameControl::createObject(Rectangle rect) {
		if (rect.name == "")
			rect.name = "rect_" + this->rectId;
		++this->rectId;
		this->rectangles.emplace_back(rect);
		return &this->rectangles.back();
	}

	DebugCircle* GameControl::createObject(DebugCircle dbgCircle) {
		if (dbgCircle.name == "")
			dbgCircle.name = "dbgCircle_" + this->dbgCircleId;
		++this->dbgCircleId;
		this->debugCircles.emplace_back(dbgCircle);
		return &this->debugCircles.back();
	}

	void GameControl::updateAll() {
		for (int i = 0; i < this->rectangles.size(); ++i)
			this->rectangles[i].collision = false;
		for (int i = 0; i < this->rectangles.size()-1; ++i) {
			for (int k = i+1; k < this->rectangles.size(); ++k) {
				const bool collision = Engine2d::collision::withRect(this->rectangles[i], this->rectangles[k]);
				if (collision) {
					const float fraction = Engine2d::collision::preventPenetration(this->rectangles[i], this->rectangles[k]);
					// Backtrack every object's position by -velocity*fraction --> probably ?? or not??
					// for (int j = 0; j < this->rectangles.size(); ++j) {
					// 	if (&this->rectangles[j] != &this->rectangles[i] &&
					// 		&this->rectangles[j] != &this->rectangles[k]) {
					// 		this->rectangles[j].position = this->rectangles[j].position - fraction * this->rectangles[j].dx;
					// 	}
					// }
					i = -1;
					k = 0;
				}

			}
		}

		for (Rectangle &rect: this->rectangles)
			rect.update();
	}

	void GameControl::drawAll() {
		for (const Rectangle &rect: this->rectangles)
			rect.draw();
		for (const DebugCircle &dbgCircle: this->debugCircles)
			dbgCircle.draw();
	}
}
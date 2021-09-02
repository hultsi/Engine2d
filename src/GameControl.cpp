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
			for (int k = i+1; k < this->rectangles.size(); ++k)
				Engine2d::collision::withRect(this->rectangles[i], this->rectangles[k]);
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
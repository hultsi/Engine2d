#include <vector>
#include "GameControl.h"
#include "Rectangle.h"

namespace Engine2d {
	GameControl::GameControl() {};

	Rectangle* GameControl::createObject(Rectangle rect) {
		if (rect.name == "")
			rect.name = "rect_" + this->rect_id;
		++this->rect_id;
		this->rectangles.emplace_back(rect);
		return &this->rectangles.back();
	}

	void GameControl::drawAll() {
		for (const Rectangle &rect: this->rectangles)
			rect.draw();
	}
}
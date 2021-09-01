#pragma once
#include <vector>
#include "Rectangle.h"

namespace Engine2d {
	namespace collision {
		// Test for collision between 2 rectangles
		bool withConvex(Rectangle &rect, Rectangle &other);
	}
}
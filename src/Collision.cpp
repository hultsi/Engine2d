#include <vector>
#include "Collision.h"
#include "Rectangle.h"

namespace Engine2d {
	// todo: later on generally for convex objects
	// Separating axis theorem
	bool withRect(Rectangle &rect, Rectangle &other) {
		constexpr int loops = 2; // corners divided by two rounded up --> 2
		
		for (int i = 0; i < loops; ++i) {
			// Create vectors and apply dot product etc.
			
		}
		return false;
	}
}
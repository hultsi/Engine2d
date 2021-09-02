#include <vector>
#include <algorithm>
#include "Collision.h"
#include "Rectangle.h"
#include "Vector2d.h"

#include <iostream>

namespace Engine2d {
	// todo: later on generally for convex objects
	// Separating axis theorem
	bool collision::withRect(Rectangle &rect, Rectangle &other) {
		constexpr int N = 2; // permutations
		constexpr int corners = 4;
		constexpr int maxProjs = 2; // corners divided by two rounded up --> 2

		Rectangle *r0 = &rect;
		Rectangle *r1 = &other;
		float d0[4] = {0,0,0,0};
		float d1[4] = {0,0,0,0};
		float *d0_Max = 0;
		float *d0_Min = 0;
		float *d1_Max = 0;
		float *d1_Min = 0;
		for (int i = 0; i < N; ++i) {
			for (int k = 0; k < maxProjs; ++k) {
				// Create projection vector aligned parallel to r0 kth side
				Vector2d proj(r0->P[k+1].x - r0->P[k].x, r0->P[k+1].y - r0->P[k].y);
				proj.normalize();
				// Calculate corner pos vector projections on this
				for (int j = 0; j < corners; ++j) {
					d0[j] = proj.dot(r0->P[j]);
					d1[j] = proj.dot(r1->P[j]);
				}
				d0_Min = std::min_element(d0, d0+4);
				d0_Max = std::max_element(d0, d0+4);
				d1_Min = std::min_element(d1, d1+4);
				d1_Max = std::max_element(d1, d1+4);
				if ((*d0_Min >= *d1_Max || *d1_Min >= *d0_Max)) {
					return false;
				}
			}
			r0 = &other;
			r1 = &rect;
		}
		rect.collision = true;
		other.collision = true;
		return true;
	}
}
#include <vector>
#include <algorithm>
#include <memory>
#include "Collision.h"
#include "Rectangle.h"
#include "Vector2d.h"
// #include "Engine2d.h"

#if DEBUG == 1
	#include <iostream>
#endif

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
				if ((*d0_Min > *d1_Max || *d1_Min > *d0_Max)) {
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

	// Moves object out of another object but does not reset velocities
	// If you want to _not_ use impulse but just stop objects when they collide
	// set velocities to 0 at the end of this function
	float collision::preventPenetration(Rectangle &rect, Rectangle &other) {
		// Store initial vector lengths
		Vector2d v0 = rect.dx;
		Vector2d v1 = other.dx;
		const float v0Len = v0.getLength();
		const float v1Len = v1.getLength();
		// Binary search
		float scaleFactor = 1;
		bool collision = true;
		float binaryFactor = .5;
		rect.dx = -binaryFactor*rect.dx;
		other.dx = -binaryFactor*other.dx;
		while (true) {
			rect.updatePosition();
			other.updatePosition();
			collision = collision::withRect(rect, other);
			if (collision) {
				// decrease dx
				binaryFactor *= .5;
				rect.dx = rect.dx - binaryFactor * v0;
				other.dx = other.dx - binaryFactor * v1;
			} else {
				// increase dx
				if (binaryFactor*v0.x <= 2 && binaryFactor*v0.y <= 2 &&
					binaryFactor*v1.x <= 2 && binaryFactor*v1.y <= 2) {
					// break loop and reset original velocities for impulse calculation
					if (v0Len != 0)
						scaleFactor = rect.dx.getLength() / v0Len;
					else
						scaleFactor = other.dx.getLength() / v1Len;
					rect.dx = v0;
					other.dx = v1;
					break;
				}
				binaryFactor *= .5;
				rect.dx = rect.dx + binaryFactor * v0;
				other.dx = other.dx + binaryFactor * v1;
			}
		}
		return std::abs(scaleFactor);
	}

	// Returns collision normal pointing away from the rectangle's collision plane
	// towards the collision point of the other rectangle
	Rectangle* collision::getCollisionNormal(Rectangle &rect, Rectangle &other, std::unique_ptr<Vector2d> &point, std::unique_ptr<Vector2d> &normal) {
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
		float dist = -1;
		auto sign = [](float val){ return (float(0) < val) - (val < float(0)); };
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
				if ((*d0_Min > *d1_Max || *d1_Min > *d0_Max)) {
					// Collision plane is formed by r0
					normal->x = -sign(*d1_Min - *d0_Min) * proj.x;
					normal->y = -sign(*d1_Min - *d0_Min) * proj.y;
					// Collision point can thus be found from r1
					// If however, there are duplicate collision points (close to each other)
					// Then we have plane-plane collision
					if (std::abs(*d0_Min - *d1_Max) < std::abs(*d1_Min - *d0_Max)) {
						point->x = r1->P[std::distance(d1, d1_Max)].x;
						point->y = r1->P[std::distance(d1, d1_Max)].y;
					} else {
						point->x = r1->P[std::distance(d0, d0_Max)].x;
						point->y = r1->P[std::distance(d0, d0_Max)].y;
					}
					return r1;
				}
			}
			r0 = &other;
			r1 = &rect;
		}
		return nullptr;
	}
	
	float collision::absImpulse(const Vector2d vel_a, const Vector2d vel_b, const float invMass_a, const float invMass_b,
					 const float rest_a, const float rest_b) {
		const float e = (rest_a < rest_b ? rest_a : rest_b);
		const float xdiff = (vel_b.x - vel_a.x);
		const float ydiff = (vel_b.y - vel_a.y);
		return (-(1 - e) * (std::sqrt(xdiff*xdiff + ydiff*ydiff)) / (invMass_a + invMass_b));
	}
}
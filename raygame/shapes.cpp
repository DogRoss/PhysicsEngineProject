#include "shapes.h"

#include "mathTools.h"
#include "physicsObject.h"

#include <string>

namespace collisionResolution {
/// <summary>
/// checks if collider-Circle 'A' is in collider-Circle 'B' 
/// </summary>
/// <param name="posA"></param>
/// <param name="circleA"></param>
/// <param name="posB"></param>
/// <param name="circleB"></param>
/// <returns></returns>
bool checkCircleCircle(Vector2 posA, circle circleA, Vector2 posB, circle circleB) {
	// get the distance
	Vector2 offset = (posA - posB);
	float distSQ = Vector2DotProduct(offset, offset);
	//get the sum of the radii
	float sum = circleA.radius + circleB.radius;

	return distSQ < (sum* sum);
}

/// <summary>
/// checks if collider-AABB 'A' is in collider-AABB 'B'
/// </summary>
/// <param name="posA"></param>
/// <param name="aabbA"></param>
/// <param name="posB"></param>
/// <param name="aabbB"></param>
/// <returns></returns>
bool checkAABBAABB(Vector2 posA, aabb aabbA, Vector2 posB, aabb aabbB) {
	return posA.x - aabbA.halfExtents.x < posB.x + aabbB.halfExtents.x && // l within r
		posA.x + aabbA.halfExtents.x > posB.x - aabbB.halfExtents.x && // r within l
		posA.y - aabbA.halfExtents.y < posB.y + aabbB.halfExtents.y && // t within b
		posA.y + aabbA.halfExtents.y > posB.y - aabbB.halfExtents.y;   // b within t
}

/// <summary>
/// Checks if collider-Circle is within collider-AABB
/// </summary>
/// <param name="posA"></param>
/// <param name="circ"></param>
/// <param name="posB"></param>
/// <param name="ab"></param>
/// <returns></returns>
bool checkCircleAABB(Vector2 posA, circle circ, Vector2 posB, aabb ab) {
	// find nearest point to AABB in direction towards circle
	//
	// we can do this by clamping center of circle to AABB bounds

	float distX = posA.x - Clamp(posA.x, posB.x - ab.halfExtents.x, posB.x + ab.halfExtents.x);
	float distY = posA.y - Clamp(posA.y, posB.y - ab.halfExtents.y, posB.y + ab.halfExtents.y);

	return ((distX * distX) + (distY * distY)) < (circ.radius * circ.radius);
}

/// <summary>
/// resolves physics objects that are overlapping, calculates penetration and needed forces to depenetrate colliders
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <param name="elasticity"></param>
/// <param name="normal"></param>
/// <param name="pen"></param>
void resolvePhysicsBodies(physicsObject& lhs, class physicsObject& rhs, float elasticity, Vector2 normal, float pen) {
	//TODO: Vector2 -= Vector2 might not work, check when using

	if (Vector2Length(normal) == 0) {
		normal.y = 1.0f;
	}

	// depenetrate objects
	if (!lhs.isStatic) {
		lhs.pos += normal * pen;
	}
	if (!rhs.isStatic)
	{
		rhs.pos -= normal * pen;
	}

	//TODO: add debug
	// calculate resolution impulse
	// nromal and pen are passed by reference and will be updated
	float impulseMag = resolveCollision(lhs.pos, lhs.vel, lhs.mass, rhs.pos, rhs.vel, rhs.mass, elasticity, normal);
	if (lhs.isStatic || rhs.isStatic) { impulseMag *= 2.0f; }
	Vector2 impulse = impulseMag * normal;

	if (!(lhs.isStatic || rhs.isStatic)) {
		pen *= .51f;
	}

	// depenetrate (aka seperate the two objects)
	if (!lhs.isStatic) {
		lhs.addImpulse(impulse);
	}
	if (!rhs.isStatic) {
		rhs.addImpulse(-impulse);
	}

}

/// <summary>
/// calculates needed impulse to seperate colliders from each other based off physical values and normal
/// </summary>
/// <param name="posA"></param>
/// <param name="velA"></param>
/// <param name="massA"></param>
/// <param name="posB"></param>
/// <param name="velB"></param>
/// <param name="massB"></param>
/// <param name="elasticity"></param>
/// <param name="normal"></param>
/// <returns></returns>
float resolveCollision(Vector2 posA, Vector2 velA, float massA, Vector2 posB, Vector2 velB, float massB, float elasticity, Vector2 normal)
{
	if (Vector2Length(normal) == 0) {
		normal.y = 1.0f;
	}

	// calculate the relative velocity
	Vector2 relVel = velA - velB;

	// calculate impulse mag
	float impulseMag = Vector2DotProduct(-(1.0f + elasticity) * relVel, normal) /
		Vector2DotProduct(normal, normal * (1 / massA + 1 / massB));

	//return impulse that applies to both objects
	return impulseMag;
}
}
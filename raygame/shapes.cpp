#include "shapes.h"

bool checkCircleCircle(const Vector2& posA, circle circleA, 
					   const Vector2& posB, circle circleB) 
{
	/* retrieve sum of the radii
	   calculate distance between their centers
	   if distance is less than the sum, they're in-collision
	   
	   ! PERF: you can do this w/o sqrt call if you compare the 
		       squares of these values instead if the actual values */

	float sum = circleA.radius + circleB.radius;

	//get distance between shape centers
	float dist2 = Vector2Distance(posA, posB);

	dist2 *= dist2;

	return dist2 < sum * sum;
}

bool checkCircleCircle(const Vector2& posA, const shape& circleA, const Vector2& posB, const shape& circleB)
{
	return checkCircleCircle(posA, circleA.circleData, posB, circleB.circleData);
}

bool checkAABBAABB(const Vector2& posA, aabb aabbA, const Vector2& posB, aabb aabbB)
{

	// y pos is top edge
	// x pos is left edge
	float a_rightEdge = posA.x + aabbA.size, a_topEdge = posA.y + aabbA.size;
	float b_rightEdge = posB.x + aabbB.size, b_topEdge = posB.y + aabbB.size;

	if (a_rightEdge >= posB.x && // a_rightEdge passes b_leftEdge
		posA.x <= b_rightEdge && // a_leftEdge passes b_rightEdge
		a_topEdge >= posB.y && // a_topEdge passes b_bottomEdge
		posA.y <= b_topEdge) { // a_bottomEdge passes b_topEdge
		std::cout << "COLLISION" << std::endl;
		return true;
	}
	return false;
}

bool checkAABBAABB(const Vector2& posA, const shape& aabbA, const Vector2& posB, const shape& aabbB)
{
	return checkAABBAABB(posA, aabbA.aabbData, posB, aabbB.aabbData);
}

bool checkCircleAABB(const Vector2& posCircle, circle circle, const Vector2& posAABB, aabb aabb)
{
	float testX = posCircle.x, testY = posCircle.y;

	if (posCircle.x < posAABB.x) //left edge
		testX = posAABB.x;
	else if (posCircle.x > posAABB.x + aabb.size) //right edge
		testX = posAABB.x + aabb.size;

	if (posCircle.y < posAABB.y) //top edge
		testY = posAABB.y;
	else if (posCircle.y > posAABB.y + aabb.size) //bottom edge
		testY = posAABB.y + aabb.size;

	float distX = posCircle.x - testX;
	float distY = posCircle.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= circle.radius) {
		return true;
	}
	return false;
}

bool checkCircleAABB(const Vector2& posCircle, const shape& circle, const Vector2& posAABB, const shape& aabb)
{
	return checkCircleAABB(posCircle, circle.circleData, posAABB, aabb.aabbData);
}

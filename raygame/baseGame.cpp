#include "baseGame.h"

#include "raylib.h"

#include <iostream>
#include <limits>
#include <cassert>

#include "enumUtil.h"
#include "mathTools.h"

bool checkCircleCircle(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB);
bool checkAABBAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB);
bool checkCircleAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB);

Vector2 depenetrateCircleCircle(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen);
Vector2 depenetrateAABBAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen);
Vector2 depenetrateCircleAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen);

collisionMap setupCollisionChecks() {
	collisionMap map;

	map[static_cast<uint8_t>(shapeType::CIRCLE | shapeType::CIRCLE)] = checkCircleCircle;
	map[static_cast<uint8_t>(shapeType::AABB | shapeType::AABB)] = checkAABBAABB;
	map[static_cast<uint8_t>(shapeType::CIRCLE | shapeType::AABB)] = checkCircleAABB;

	return map;
}

depenetrationMap setupDepenetrator() {
	depenetrationMap map;

	map[static_cast<uint8_t>(shapeType::CIRCLE | shapeType::CIRCLE)] = depenetrateCircleCircle;
	map[static_cast<uint8_t>(shapeType::AABB | shapeType::AABB)] = depenetrateAABBAABB;
	map[static_cast<uint8_t>(shapeType::CIRCLE | shapeType::AABB)] = depenetrateCircleAABB;

	return map;
}

collisionMap baseGame::collisionCheckers = setupCollisionChecks();
depenetrationMap baseGame::collisionDepenetrators = setupDepenetrator();

bool checkCircleCircle(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB) {
	return checkCircleCircle(posA, shapeA.circleData, posB, shapeB.circleData);
}

bool checkAABBAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB) {
	return checkAABBAABB(posA, shapeA.aabbData, posB, shapeB.aabbData);
}

bool checkCircleAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB) {
	return checkCircleAABB(posA, shapeA.circleData, posB, shapeB.aabbData);
}

// Returns mtv direction
// Out penetration depth stored in 'pen'
Vector2 depenetrateCircleCircle(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen) {
	float dist = Vector2Length(posA - posB);
	float sum = shapeA.circleData.radius + shapeB.circleData.radius;

	pen = sum - dist;

	return Vector2Normalize(posA - posB);
}

Vector2 depenetrateAABBAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen) {
	float mtvDist = 0.0f;
	Vector2 mtvAxis = {};

	Vector2 rawOffset = posB - posA;
	Vector2 offset = { abs(rawOffset.x), abs(rawOffset.y) };

	float xPen = shapeA.aabbData.halfExtents.x + shapeB.aabbData.halfExtents.x - offset.x;
	if (xPen < 0.0f) { pen = 0.0f; return {}; }
	float yPen = shapeA.aabbData.halfExtents.y + shapeB.aabbData.halfExtents.y - offset.y;
	if (yPen < 0.0f) { pen = 0.0f; return {}; }

	if (xPen < yPen) {
		pen = xPen;
		mtvAxis.x = copysign(1.0f, -rawOffset.x);
	}
	else {
		pen = yPen;
		mtvAxis.y = copysign(1.0f, -rawOffset.y);
	}

	return mtvAxis;
}

Vector2 depenetrateCircleAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen) {
	Vector2 circConstrained = Vector2
}
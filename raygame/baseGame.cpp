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

//TODO: Vec2DotProduct() might not work correct, same with Vec2Absolute()
Vector2 depenetrateCircleAABB(const Vector2& posA, const shape& shapeA, const Vector2& posB, const shape& shapeB, float& pen) {
	Vector2 circConstrained = Vector2Clamp(posA, posB - shapeB.aabbData.halfExtents, posB + shapeB.aabbData.halfExtents);
	Vector2 circOffset = circConstrained - posA;
	float distSQ = Vector2DotProduct(circOffset, circOffset);
	std::cout << "distSQ dot product return value: " << distSQ << std::endl;
	float radiusSQ = shapeA.circleData.radius * shapeA.circleData.radius;

	if (distSQ < radiusSQ) {
		// center of circle isnt in aabb
		if (distSQ != 0.0f) {
			float dist = sqrt(distSQ);
			pen = shapeA.circleData.radius - dist;
			return Vector2Normalize(-circOffset);
		}
		// center of circle is in aabb
		else {
			Vector2 offset = posA - posB;
			Vector2 offsetAbs = Vector2Absolute(offset);

			Vector2 overlap = shapeB.aabbData.halfExtents - offsetAbs;

			Vector2 mtv = {};

			if (overlap.x < overlap.y) {
				pen = overlap.x;
				mtv.x = copysign(1.0f, offset.x);
			}
			else {
				pen = overlap.y;
				mtv.y = copysign(1.0f, offset.y);
			}

			pen += shapeA.circleData.radius;
			return Vector2Normalize(mtv);
		}
	}
	else {
		// not penetrating
		pen = 0.0f;
		return {};
	}
}

baseGame::baseGame() {
	targetFixedStep = 1.0f / 30.0f;
	accumulatedFixedTime = 0.0f;
	gravityScale = 1.0f;
	useGravity = true;
	useWrapping = false;
}

void baseGame::init() {
	// Initialization
	//--------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	//--------------------------------------------------------

	onInit();
}

void baseGame::tick() {
	// update
	accumulatedFixedTime += GetFrameTime();

	onTick();
}

void baseGame::tickFixed() {
	// do physics
	accumulatedFixedTime -= targetFixedStep;

	float fWidth = (float)GetScreenWidth();
	float fHeight = (float)GetScreenHeight();

	for (auto& i : physicsObjects) {
		if (useGravity && i.useGravity) {
			i.addAccel(Vector2{ 0, 9.81f } *gravityScale);
		}
		i.tickPhys(targetFixedStep);

		// position wrap
		if (useWrapping) {
			i.pos.x = wrap(i.pos.x, fWidth);
			i.pos.y = wrap(i.pos.y, fHeight);
		}
	}

	for (size_t i = 0; i < 5; i++) {
		bool isClean = true;
		for (auto& i : physicsObjects) {
			for (auto& j : physicsObjects) {
				// skip self collision
				if (&i == &j) { continue; }
				if (i.collider.type == shapeType::NONE || j.collider.type == shapeType::NONE) { continue; }
				if (i.isStatic) { continue; }

				// collider type w/ lower number should always be left
				auto* lhs = &i;
				auto* rhs = &j;

				if (static_cast<uint8_t>(i.collider.type) > static_cast<uint8_t>(j.collider.type)) {
					lhs = &j;
					rhs = &i;
				}

				bool collision = false;
				auto pairType = static_cast<collisionPair>(lhs->collider.type | rhs->collider.type);
				collision = collisionCheckers[pairType](lhs->pos, lhs->collider, rhs->pos, rhs->collider);

				if (collision) {
					isClean = false;

					float pen = 0.0f;
					Vector2 normal = collisionDepenetrators[pairType](lhs->pos, lhs->collider, rhs->pos, rhs->collider, pen);
					// edge-case: what if two objects are on top of each other?
					//			  we'll get a zero vector which will result in
					//			  degenerate floating point values
					if (lhs->pos == rhs->pos) { normal = { 0, 1 }; }
					// TODO: DEBUG HERE
					// DEBUG HERE
					float debugLength = Vector2Length(normal);
					std::cout << "debugLength: " << debugLength << std::endl;
					//assert((float)abs(debugLength - 1.0f) < FLT_EPSILON * 100);

					resolvePhysicsBodies(*lhs, *rhs, 1.0f, normal, pen);
				}
			}
		}
		if (isClean) { break; }
	}
	
	onTickPhys();
}

void baseGame::draw() const {
	// Draw 
	//------------------------------------------------------------------------
	BeginDrawing();
	ClearBackground(RAYWHITE);

	for (const auto& i : physicsObjects) {
		i.draw();
	}

	onDraw();

	EndDrawing();
	//------------------------------------------------------------------------
}

void baseGame::exit() {
	onExit();

	// De-Initialization
	//------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//------------------------------------------------------------------------
}

bool baseGame::shouldClose() const {
	return WindowShouldClose();
}

bool baseGame::shouldTickFixed() const {
	return accumulatedFixedTime >= targetFixedStep;
}
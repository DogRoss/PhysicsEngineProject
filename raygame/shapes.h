#pragma once

#include <stdint.h>
#include <iostream>
#include "raymath.h"

struct circle {
	//TODO: local offset
	float radius;
};
struct aabb {
	Vector2 halfExtents;
};


enum class shapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct shape {
	// an enum for the shape type
	shapeType type;

	// storage* for those shape types
	union {
		circle circleData;
		aabb aabbData;
	};
};

bool checkCircleCircle(Vector2 posA, circle circleA, Vector2 posB, circle circleB);
bool checkAABBAABB(Vector2 posA, aabb aabbA, Vector2 posB, aabb aabbB);
bool checkCircleAABB(Vector2 posA, circle circ, Vector2 posB, aabb ab);

void resolvePhysicsBodies(class physicsObject& lhs, class physicsObject& rhs, float elasticity, Vector2 normal, float pen);

float resolveCollision(Vector2 posA, Vector2 velA, float massA,
	Vector2 posB, Vector2 velB, float massB,
	float elasticity, Vector2 normal);















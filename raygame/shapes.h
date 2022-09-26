#pragma once

#include <stdint.h>
#include <iostream>
#include "raymath.h"

struct circle {
	//TODO: local offset
	float radius;
};
struct aabb {
	//TODO: local offset
	float size;
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

bool checkCircleCircle(const Vector2& posA, circle circleA,
					   const Vector2& posB, circle circleB);

// wrapper for the circle circle collision
bool checkCircleCircle(const Vector2& posA, const shape& circleA,
					   const Vector2& posB, const shape& circleB);

//check bounding box (AABB)
bool checkAABBAABB(const Vector2& posA, aabb aabbA,
				   const Vector2& posB, aabb aabbB);

// wrapper for the AABB/AABB collision
bool checkAABBAABB(const Vector2& posA, const shape& aabbA,
				   const Vector2& posB, const shape& aabbB);

//check circle AABB
bool checkCircleAABB(const Vector2& posCircle, circle circle,
				     const Vector2& posAABB, aabb aabb);

// wrapper for the circle/AABB collision
bool checkCircleAABB(const Vector2& posCircle, const shape& circle,
				     const Vector2& posAABB, const shape& aabb);















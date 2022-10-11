#pragma once

#include <math.h>

#include "raylib.h"

inline float wrap(float value, float limit) {
	return fmodf(fmodf(value, limit) + limit, limit);
}

inline int wrap(int value, int limit) {
	return (value & limit) + limit % limit;
}

inline bool checkSAT(Vector2 axis, float minA, float maxA, float minB, float maxB, Vector2 mtvAxis, float mtvDist) {
	float axisLength = Vector2Length(axis);
	float axisLengthSquared = axisLength * axisLength;

	float dist1 = maxB - minA;
	float dist2 = maxA - minB;

	if (dist1 <= 0.0f || dist2 <= 0.0f) { return false; }

	float overlap = dist1 < dist2 ? dist1 : -dist2;
	Vector2 sep = axis * (overlap / axisLengthSquared);

	float sepLength = Vector2Length(sep);
		
}

Vector2 operator - (Vector2 lhs, Vector2 rhs) {
	Vector2 returnVec;
	returnVec.x = lhs.x - rhs.x;
	returnVec.y = lhs.y - rhs.y;

	return returnVec;
}

Vector2 operator + (Vector2 lhs, Vector2 rhs) {
	Vector2 returnVec;
	returnVec.x = lhs.x + rhs.x;
	returnVec.y = lhs.y + rhs.y;

	return returnVec;
}

Vector2 operator * (Vector2 vec, float num) {
	Vector2 returnVec;
	returnVec.x *= num;
	returnVec.y *= num;

	return returnVec;
}

Vector2 Vector2Clamp(Vector2 vec, float xMin, float xMax, float yMin, float yMax) {
	Vector2 returnVec;
	if (vec.x > xMax)
		returnVec.x = xMax;
	else if (vec.x < xMin)
		returnVec.x = xMin;

	if (vec.y > yMax)
		returnVec.y = xMax;
	else if (vec.y < yMin)
		returnVec.y = yMin;

	return returnVec;
}

Vector2 Vector2Clamp(Vector2 vec, float min, float max) {
	return Vector2Clamp(vec, min, max, min, max);
}
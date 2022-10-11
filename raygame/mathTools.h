#pragma once

#include <math.h>

#include "mathTools.h"
#include "raylib.h"



inline Vector2 operator - (Vector2 lhs, Vector2 rhs) {
	Vector2 returnVec = lhs;
	returnVec.x = lhs.x - rhs.x;
	returnVec.y = lhs.y - rhs.y;

	return returnVec;
}

inline Vector2 operator + (Vector2 lhs, Vector2 rhs) {
	Vector2 returnVec = lhs;
	returnVec.x = lhs.x + rhs.x;
	returnVec.y = lhs.y + rhs.y;

	return returnVec;
}

inline Vector2 operator * (Vector2 vec, float num) {
	Vector2 returnVec = vec;
	returnVec.x *= num;
	returnVec.y *= num;

	return returnVec;
}
inline Vector2 operator * (float num, Vector2 vec) {
	Vector2 returnVec = vec;
	returnVec.x *= num;
	returnVec.y *= num;

	return returnVec;
}

inline Vector2 operator - (Vector2 vec) {
	return Vector2{ -vec.x, -vec.y };
}

inline void operator *= (Vector2& lhs, float rhs) {
	lhs.x *= rhs;
	lhs.y *= rhs;
}

inline void operator -= (Vector2& lhs, Vector2 rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
}

inline void operator += (Vector2& lhs, Vector2 rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
}

inline bool operator == (Vector2 lhs, Vector2 rhs) {
	if (lhs.x != rhs.x || lhs.y != rhs.y)
		return false;
	else
		return true;
}

inline Vector2 Vector2Clamp(Vector2 vec, float xMin, float xMax, float yMin, float yMax) {
	Vector2 returnVec = vec;
	if (vec.x > xMax)
		returnVec.x = xMax;
	else if (vec.x < xMin)
		returnVec.x = xMin;

	if (vec.y > yMax)
		returnVec.y = yMax;
	else if (vec.y < yMin)
		returnVec.y = yMin;

	return returnVec;
}

inline Vector2 Vector2Clamp(Vector2 vec, float min, float max) {
	return Vector2Clamp(vec, min, max, min, max);
}

inline Vector2 Vector2Clamp(Vector2 vec, Vector2 min, Vector2 max) {
	return Vector2Clamp(vec, min.x, max.x, min.y, max.y);
}

inline Vector2 Vector2Absolute(Vector2 vec) {
	return Vector2{ vec.x >= 0 ? vec.x : -vec.x,
					vec.y >= 0 ? vec.y : -vec.y };
}

inline Vector2 Vector2Absolute(float x, float y) {
	return Vector2{ x >= 0 ? x : -x,
					y >= 0 ? y : -y };
}




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
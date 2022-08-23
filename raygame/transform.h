#pragma once

#include"raylib.h"

class transform
{
public:
	transform();
	transform(float x, float y);
	transform(Vector2 pos);

	Vector2 position;

	void translate(float newX, float newY);
	void translate(Vector2 newPos);
};


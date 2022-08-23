#pragma once

//includes go here
#include"transform.h"

class collider
{
public:
	collider();
	collider(bool isActive);
	collider(float radiusLength, bool isCircleCollider);
	collider(float radiusLength, bool isCircleCollider, bool isActive);

	bool enabled;
	bool circleCol; //decides if collider is a circle collider
	float radius; //decides length from center bounds go out to, for box cols, it is the length from object center a face is

	void collision();
};


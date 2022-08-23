#pragma once

#include "collider.h"

class physics
{
public:
	physics(); //default constructor
	physics(float gravityForce); //gravity constructor

	static Vector2 gravity;
	
	void checkCollisions();
};


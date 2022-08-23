#pragma once

#include "physics.h"

class rigidBody
{
public:
	rigidBody();

	Vector2 position;
	Vector2 velocity;

	float mass;
	bool isStatic;
	bool useGravity;

	void applyForces();
};


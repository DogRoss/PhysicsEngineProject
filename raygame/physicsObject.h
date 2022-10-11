#pragma once

#include "raylib.h"
#include "shapes.h"

class physicsObject
{
public:
	Vector2 pos;
	Vector2 vel;

	Vector2 forces;

	physicsObject();

	float mass;
	float drag;

	bool useGravity;
	bool isStatic;

	shape collider;

	void tickPhys(Vector2 force);
	void draw() const;

	// Add continous force in relation to mass
	void addForce(Vector2 force);
	// Add instant force in relation to mass
	void addImpulse(Vector2 impulse);

	// Accelerates without relation to mass
	void addAccel(Vector2 accel);
	// sets velocity
	void addVelocityChange(Vector2 delta);

	float getMomentum() const;
};


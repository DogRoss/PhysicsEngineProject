#pragma once

#include "raylib.h"
#include "shapes.h"

class physicsObject
{
public:
	physicsObject();

	shape collider;

	//rigidbody physics
	float mass;
	float drag;
	float gravity;
	bool isStatic;

	//positional data
	Vector2 position;
	Vector2 velocity;
	Vector2 forces;

	//TODO: Add shape/collider functionality

	//---------
	void setupObj();
	void draw();

	void physicsTick(float delta);

	void translate(float newX, float newY);
	void translate(Vector2 newPos);
	void applyForces(Vector2 direction, float force);
	void applyForces(Vector2 force);
	void applyForcesToActor(physicsObject* otherActor, Vector2 force);

	void displaceFromActor(physicsObject* otherActor);
	void resolveCollision(physicsObject* otherActor);

	//TODO: Add functions for applying/getting force
};


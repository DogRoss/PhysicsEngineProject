#include "physicsObject.h"

#include <iostream>

physicsObject::physicsObject() {

}

void physicsObject::setupObj()
{
	velocity = { 0,0 };
	gravity = 1;
	mass = 1;
	drag = 0;
	isStatic = false;
}

void physicsObject::draw() {
	//this will depend on the shape of the physics object
	switch (collider.type) {
	case shapeType::CIRCLE:
		DrawCircle(position.x, position.y, collider.circleData.radius, RED);
		break;
	case shapeType::AABB:
		DrawRectangle(position.x, position.y, collider.aabbData.size, collider.aabbData.size, GREEN);
		//DrawRectangle(position.x - (collider.aabbData.size / 2), position.y - (collider.aabbData.size / 2), collider.aabbData.size, collider.aabbData.size, GREEN);
		DrawCircle(position.x + (collider.aabbData.size / 2), position.y + (collider.aabbData.size / 2), 1, BLACK);
		break;
	}
}

void physicsObject::physicsTick(float delta)
{
	/* checks collision and physics and updates values and position */

	//check collision
	//translate based off velocity
	//TODO: add drag that takes off of velocity
	//add gravity acceleration / gravity interruption on collision

	
	if (!isStatic) {
		//---------------------------------------------------------------------------------------------------------
		/* GRAVITY APPLICATION */
		velocity.y += (mass * gravity) * delta;

		//---------------------------------------------------------------------------------------------------------
		/* DRAG APPLICATION */
		if (velocity.y > 0.1f) { // y axis
			velocity.y -= drag * delta;
		}
		else if (velocity.y < 0.1f) {
			velocity.y += drag * delta;
		}
		if (velocity.x > 0.1f) { // x axis
			velocity.x -= drag * delta;
		}
		else if (velocity.x < 0.1f) {
			velocity.x += drag * delta;
		}

		//apply change in velocity
		translate(position.x + velocity.x, position.y + velocity.y);
	}
}

void physicsObject::translate(float newX, float newY)
{
	/* sets position to new values */
	position = { newX, newY };
}

void physicsObject::translate(Vector2 newPos)
{
	/* sets position to new values */
	position = newPos;
}

void physicsObject::applyForces(Vector2 direction, float force)
{
	/* applies current velocity and translates player */
	velocity.x += direction.x * force;
	velocity.y += direction.y * force;

	if (isStatic)
		velocity = { 0,0 };
}

void physicsObject::applyForces(Vector2 force)
{
	velocity.x += force.x;
	velocity.y += force.y;

	if (isStatic)
		velocity = { 0,0 };
}

/// <summary>
/// CALLED WHEN COLLISION IS RESOLVED:
/// Applies forces to both this actor(TA) and colliding actor(CA),
/// CA gets 'force' applied to it to represent collision
/// TA gets '-force' applied to it to represent the forces applied in the opposite direction
/// </summary>
/// <param name="otherActor"></param>
/// <param name="force"></param>
void physicsObject::applyForcesToActor(physicsObject* otherActor, Vector2 force)
{
	Vector2 oppositeForce = {-force.x, -force.y};

	velocity.x += oppositeForce.x; velocity.y += oppositeForce.y;
	otherActor->velocity.x += force.x; otherActor->velocity.y += force.y;

	if (isStatic)
		velocity = { 0,0 };

	if (otherActor->isStatic)
		otherActor->velocity = { 0,0 };
}


void physicsObject::displaceFromActor(physicsObject* otherActor)
{
	/*
	-get direction towards other actor.
	-get distance from other actor.
	-compare distance with thisActor.radius + otherActor.radius.
	-if less than, record the difference.
	-take the difference and displace both objects in opposite directions by
	half the difference.
	*/

	Vector2 dir = {otherActor->position.x - position.x,
				  otherActor->position.y - position.y};
	dir = Vector2Normalize(dir);

	float distance = Vector2Distance(otherActor->position, position);
	float minDist = 0;
	float cornerCenterDist = 0;

	Vector2 thisDir = {0,0};
	Vector2 otherDir;

	switch (collider.type) {
	case shapeType::AABB:

		if (dir.y > 0) {
			if (dir.x > 0) {
				std::cout << "below and to the right" << std::endl;
				thisDir = {(position.x + collider.aabbData.size) - (position.x + (collider.aabbData.size / 2)),
							(position.y + collider.aabbData.size) - (position.y + (collider.aabbData.size / 2))};
			}
			else {
				std::cout << "below and to the left" << std::endl;
				thisDir = { position.x - (position.x + (collider.aabbData.size / 2)),
							(position.y + collider.aabbData.size) - (position.y + (collider.aabbData.size / 2)) };
			}
		}
		else {
			if (dir.x > 0) {
				std::cout << "above and to the right" << std::endl;
				thisDir = { (position.x + collider.aabbData.size) - (position.x + (collider.aabbData.size / 2)),
							position.y - (position.y + (collider.aabbData.size / 2)) };
			}
			else {
				std::cout << "above and to the left" << std::endl;
				thisDir = { position.x - (position.x + (collider.aabbData.size / 2)),
							position.y - (position.y + (collider.aabbData.size / 2)) };
			}
		}

		switch (otherActor->collider.type) {
		case shapeType::AABB:
			//AABB to other-AABB
			cornerCenterDist = sqrt(collider.aabbData.size * 2) / 2;
			
			break;
		case shapeType::CIRCLE:
			//AABB to other-CIRCLE

			break;
		}
		break;

	case shapeType::CIRCLE:
		switch (otherActor->collider.type) {
		case shapeType::AABB:
			//CIRCLE to other-AABB
			break;
		case shapeType::CIRCLE:
			//CIRCLE to other-CIRCLE
			minDist = collider.circleData.radius + otherActor->collider.circleData.radius;
			break;
		}
		break;
	}

	Vector2 startPos = { position.x + (collider.aabbData.size / 2), position.y + (collider.aabbData.size / 2) };
	Vector2 endPos = { startPos.x + thisDir.x, startPos.y + thisDir.y};
	DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, BLUE);


	if (distance < minDist) {
		float dif = minDist - distance;
		if (!otherActor->isStatic) {
			otherActor->position.x += dir.x * (dif / 2);
			otherActor->position.y += dir.y * (dif / 2);
		}

		if (!isStatic) {
			position.x -= dir.x * (dif / 2);
			position.y -= dir.y * (dif / 2);
		}
	}
}

/// <summary>
/// CALLED WHEN COLLISION BETWEEN OBJECTS IS DETECTED:
/// 
/// </summary>
/// <param name="otherActor"></param>
void physicsObject::resolveCollision(physicsObject* otherActor)
{
	//get normal of collision
	Vector2 normal = { otherActor->position.x - position.x, // x axis
					  otherActor->position.y - position.y}; // y Axis

	normal = Vector2Normalize(normal);
	Vector2 relativeVelocity = {otherActor->velocity.x - velocity.x,
							   otherActor->velocity.y - velocity.y};

	float elasticity = 1;
	Vector2 dotVec = { relativeVelocity.x * -(1 + elasticity),
					  relativeVelocity.y * -(1 + elasticity)};
	float impulseMagnitude = Vector2DotProduct(dotVec, normal) /
						  ((1 / mass) + (1 / otherActor->mass));

	Vector2 force = normal;
	force.x *= impulseMagnitude; force.y *= impulseMagnitude;

	applyForcesToActor(otherActor, force);
}












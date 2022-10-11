#include "physicsObject.h"

#include "mathTools.h"

#include "raylib.h"

physicsObject::physicsObject() {
	pos = { 0,0 };
	vel = { 0,0 };
	forces = { 0,0 };
	collider = shape{ shapeType::NONE };

	mass = 1.0f;
	drag = 1.0f;
	isStatic = false;
	useGravity = true;
}

void physicsObject::tickPhys(float delta) {
	if (isStatic) { return; }

	// integrating forces into velocity
	vel += forces * delta;
	forces = { 0,0 };

	// integrate linear drag into velocity
	vel *= 1.0f - delta * drag;

	// integrating velocity into position
	pos += vel * delta;
}

void physicsObject::draw() const {
	switch (collider.type) {
	case shapeType::NONE:
		DrawPixel(pos.x, pos.y, RED);
		break;
	case shapeType::CIRCLE:
		DrawCircleLines(pos.x, pos.y, collider.circleData.radius, RED);
		break;
	case shapeType::AABB:
		DrawRectangleLines(pos.x - collider.aabbData.halfExtents.x, pos.y - collider.aabbData.halfExtents.y,
						   collider.aabbData.halfExtents.x * 2.0f, collider.aabbData.halfExtents.y * 2.0f, RED);
		break;
	default:
		break;
	}
}

void physicsObject::addForce(Vector2 force) {
	forces += force * (1.0f / mass);
}

void physicsObject::addAccel(Vector2 accel) {
	forces += accel;
}

void physicsObject::addImpulse(Vector2 impulse) {
	vel += impulse * (1.0f / mass);
}

void physicsObject::addVelocityChange(Vector2 delta) {
	vel += delta;
}

float physicsObject::getMomentum() const {
	return Vector2Length(vel * mass);
}

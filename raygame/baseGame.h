#pragma once

#include <vector>
#include <unordered_map>

#include "physicsObject.h"

using collisionPair = uint8_t;
using collisionFunc = bool(*)(const Vector2&, const shape&, const Vector2&, const shape&);
using collisionMap = std::unordered_map<collisionPair, collisionFunc>;

using depenetrationFunc = Vector2(*)(const Vector2&, const shape&, const Vector2&, const shape&, float& pen);
using depenetrationMap = std::unordered_map <collisionPair, depenetrationFunc>;

class baseGame {
	float accumulatedFixedTime;

	std::vector<physicsObject> physicsObjects;
	static collisionMap collisionCheckers;
	static depenetrationMap collisionDepenetrators;

	void virtual onInit() { }
	void virtual onTick() { }
	void virtual onTickPhys() { }
	void virtual onDraw() const { }
	void virtual onExit() { }
public:
	baseGame();

	void init();
	void tick();
	void tickFixed();
	void draw() const;
	void exit();

	bool shouldClose() const;
	bool shouldTickFixed() const;

	float targetFixedStep;
	float gravityScale;

	bool useGravity;
	bool useWrapping;
};

#pragma once

#include "physicsObject.h"

#include <vector>

class baseGame
{
public:
	baseGame(); //default constructor

	float targetFixedStep; //amount of time used for fixedDeltaTime
	float accumulatedFixedTime; //time since start of program
	int screenWidth;
	int screenHeight;
	bool useWrapping;

	std::vector<physicsObject> physObjs;

	void init();
	void tick();
	void fixedTick();
	void draw();

	void virtual onInit() {} //initialization
	void virtual onTick() {} //update
	void virtual onFixedTick() {} //physics update
	void virtual onDraw() {}
	void exit();

	bool shouldFixedUpdate();

};

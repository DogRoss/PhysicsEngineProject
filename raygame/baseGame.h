#pragma once

#include "physicsObject.h"

class baseGame
{
public:
	baseGame(); //default constructor

	float targetFixedStep; //amount of time used for fixedDeltaTime
	float accumulatedFixedTime; //time since start of program

	void init(); //initialization
	void update();
	void fixedUpdate();

	bool shouldFixedUpdate();

};

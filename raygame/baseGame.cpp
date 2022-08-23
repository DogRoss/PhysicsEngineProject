#include "baseGame.h"

baseGame::baseGame() {
	accumulatedFixedTime = .0f;
	targetFixedStep = 1.0f / 30.0f; //30fps

}

void baseGame::init() {
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	//TODO: add any other initialization here
	physics phys = *new physics();
}

void baseGame::update() {
	//regular update (happens every frame)
	accumulatedFixedTime += GetFrameTime();

	//--------------------------------------------------------------------
	//TODO: add behaviour that needs to be updated every frame here
	//--------------------------------------------------------------------
}
void baseGame::fixedUpdate() {
	accumulatedFixedTime -= targetFixedStep;

	//--------------------------------------------------------------------
	//TODO: update physics behaviour here
	
	//--------------------------------------------------------------------
}

bool baseGame::shouldFixedUpdate() {
	return accumulatedFixedTime >= targetFixedStep;
}
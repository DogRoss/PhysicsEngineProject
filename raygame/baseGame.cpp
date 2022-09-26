#include "baseGame.h"
#include "enumUtil.h"

#include <iostream>
#include <unordered_map>

// a type alias to make things more readable
using collisionPair = uint8_t;

// a type alias for the func sig for a collision detection func
using collisionFunc = bool(*)(const Vector2&, const shape&, 
							  const Vector2&, const shape&);

//a type alias for a map <collision paie, the collision func>
using collisionMap = std::unordered_map<collisionPair, collisionFunc>;

collisionMap detectionMap;

baseGame::baseGame() {
	accumulatedFixedTime = .0f;
	targetFixedStep = 1.0f / 30.0f; //30fps

}

bool baseGame::shouldFixedUpdate() {
	return accumulatedFixedTime >= targetFixedStep;
}

void baseGame::init()
{
	screenWidth = 800;
	screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	//TODO: add any other initialization here

	//physics list initialization
	useWrapping = true;

	detectionMap[static_cast<uint8_t>(shapeType::CIRCLE | shapeType::CIRCLE)] = checkCircleCircle;
	detectionMap[static_cast<uint8_t>(shapeType::AABB | shapeType::AABB)] = checkAABBAABB;
	detectionMap[static_cast<uint8_t>(shapeType::CIRCLE | shapeType::AABB)] = checkCircleAABB;

	onInit();
}

void baseGame::tick()
{
	// regular update(happens every frame)
	accumulatedFixedTime += GetFrameTime();

	draw();
	onTick();
}

void baseGame::fixedTick()
{
	accumulatedFixedTime -= targetFixedStep;

	//--------------------------------------------------------------------
	//TODO: update physics behaviour here
	for (physicsObject& obj : physObjs) {
		obj.physicsTick(GetFrameTime());

		if (useWrapping) {
			if (obj.position.x > screenWidth) {
				std::cout << "0 overlapping right side" << std::endl;
				obj.position.x = 0 + obj.collider.circleData.radius;
			}
			if (obj.position.x < 0) {
				std::cout << "1 overlapping left side" << std::endl;
				obj.position.x = screenWidth - obj.collider.circleData.radius;
			}
			if (obj.position.y > screenHeight) {
				std::cout << "2 overlapping top side" << std::endl;
				obj.position.y = 0 + obj.collider.circleData.radius;
			}
			if (obj.position.y < 0) {
				std::cout << "3 overlapping bottom side" << std::endl;
				obj.position.y = screenHeight - obj.collider.circleData.radius;
			}
		}
	}
	//--------------------------------------------------------------------

	for (physicsObject& i : physObjs) {
		for (physicsObject& j : physObjs) {
			//skip self collision
			if (&i == &j) { continue; }

			physicsObject* lhs = &i;
			physicsObject* rhs = &j;

			//are objects in incorrect order, if so, swap
			if (static_cast<uint8_t>(i.collider.type) > static_cast<uint8_t>(j.collider.type)) {
				//swap here
				lhs = &j;
				rhs = &i;
			}

			// create the collision and test for collision

			bool isColliding = false;
			if (!lhs->isStatic || !rhs->isStatic) {
				collisionPair pair = static_cast<collisionPair>(lhs->collider.type | rhs->collider.type);
				isColliding = detectionMap[pair](lhs->position, lhs->collider, rhs->position, rhs->collider);
			}

			if (isColliding) {
				//TODO: collision interaction
				std::cout << "collision detected!" << std::endl;
				i.displaceFromActor(&j);
				//i.resolveCollision(&j);
			}
		}
	}

	onFixedTick();
}

void baseGame::draw()
{
	for (physicsObject& obj : physObjs) {
		obj.draw();
	}

	onDraw();
}

void baseGame::exit() {

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}
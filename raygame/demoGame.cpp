#include <iostream>

#include "demoGame.h"

#include "raylib.h"

void demoGame::onTick() {
	//left click => spawn circle
	bool mb0 = IsMouseButtonPressed(0); //lmb
	bool mb1 = IsMouseButtonPressed(1); //rmb
	bool mb2 = IsMouseButtonPressed(2); //mmb

	if (mb0) {
		std::cout << "mouse down" << std::endl;

		physObjs.emplace_back();

		//reference newly created object
		physicsObject& babyPhys = physObjs.back();
		Vector2 mousePos = GetMousePosition();
		babyPhys.position = { mousePos };
		babyPhys.setupObj();
		

		shape babyCircle;
		babyCircle.type = shapeType::CIRCLE;
		babyCircle.circleData.radius = 25.0f;
		babyPhys.collider = babyCircle;
	}

	if (mb1) {
		physObjs.emplace_back();

		//reference newly created object
		physicsObject& babyPhys = physObjs.back();
		Vector2 mousePos = GetMousePosition();
		babyPhys.position = { mousePos };
		babyPhys.setupObj();

		shape babySquare;
		babySquare.type = shapeType::AABB;
		babySquare.aabbData.size = 25.0f;
		babyPhys.collider = babySquare;
	}

	if (mb2) {
		std::cout << "mmb down" << std::endl;

		physObjs.emplace_back();

		//reference newly created object
		physicsObject& babyPhys = physObjs.back();
		Vector2 mousePos = GetMousePosition();
		babyPhys.position = { mousePos };
		babyPhys.setupObj();
		babyPhys.isStatic = true;

		shape babySquare;
		babySquare.type = shapeType::AABB;
		babySquare.aabbData.size = 50.0f;
		babyPhys.collider = babySquare;
	}
}


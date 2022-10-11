#include "demoGame.h"

#include "raylib.h"

#include <iostream>
#include <limits>

void demoGame::onTick() {
	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);
	bool mb2 = IsMouseButtonPressed(2);

	if (mb0 || mb1 || mb2) {
		physicsObjects.emplace_back();
		std::cout << "Physics object placed." << std::endl;

		auto& babyPhys = physicsObjects[physicsObjects.size() - 1];
		auto mousePos = GetMousePosition();
		babyPhys.pos = { mousePos.x, mousePos.y };

		if (mb0) {
			shape circS;
			circS.type = shapeType::CIRCLE;
			circS.circleData = circle { 25.0f };
			babyPhys.collider = circS;
		}
		else if (mb1) {
			shape aabbS;
			aabbS.type = shapeType::AABB;
			aabbS.aabbData = aabb{ Vector2{ 50.0f / 2.0f , 25.0f / 2.0f  } };
			babyPhys.collider = aabbS;
			babyPhys.isStatic = false;
		}
		else if (mb2) {
			shape aabbS;
			aabbS.type = shapeType::AABB;
			aabbS.aabbData = aabb{ Vector2 {30.0f, 30.0f} };
			babyPhys.collider = aabbS;
			babyPhys.isStatic = true;
		}
	}
}

void demoGame::onDraw() const {
	DrawText("Left-click to add a dynamic ball to the scene.", 5, 5, 20, BLACK);
	DrawText("Right-click to add a small dynamic box to the scene.", 5, 25, 20, BLACK);
	DrawText("Middle-click to add a static box to the scene.", 5, 45, 20, BLACK);
}
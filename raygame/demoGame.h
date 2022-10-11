#pragma once

#include "baseGame.h" // inheriting from base game

class demoGame : baseGame {
public:
	void onTick() override;
	void onDraw() const override;
};
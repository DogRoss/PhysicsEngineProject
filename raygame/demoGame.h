#pragma once

#include "baseGame.h" // inheriting from base game

class demoGame : public baseGame {
public:
	void onTick() override;
	void onDraw() const override;
};
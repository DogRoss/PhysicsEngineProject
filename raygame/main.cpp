/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "demoGame.h"

int main()
{
	baseGame* app = new demoGame();
	app->init();
	app->targetFixedStep = 1.0f / 100.0f;
	app->gravityScale = 50.0f;
	app->useGravity = true;
	app->useWrapping = true;

	while (!app->shouldClose()) {
		app->tick();

		while (app->shouldTickFixed())
			app->tickFixed();

		app->draw();
	}

	app->exit();

	delete app;

	return 0;
}
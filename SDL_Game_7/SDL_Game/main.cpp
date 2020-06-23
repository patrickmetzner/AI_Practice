#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"



Game* game = nullptr;

int main(int argc, char* argv[])
{
	//setting frame rate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("First Game", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}
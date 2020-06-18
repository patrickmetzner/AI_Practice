#include "SDL.h"
#include <iostream>
#include "game.h"

Game *game = nullptr;

int main(int argc, char* argv[]) 
{
	game = new Game();

	game->init("First Game", 800, 600, false);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	game->clean();

	return 0;
}
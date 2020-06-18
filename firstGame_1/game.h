#ifndef game_h
#define game_h

#include "SDL.h"
#include <iostream>


class Game
{
public:
	Game();
	~Game();

	void init(const char *title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

private:
	int cnt=0;
	bool isRunning=false;
	SDL_Window *window;
	SDL_Renderer* renderer;
};


#endif //game_h





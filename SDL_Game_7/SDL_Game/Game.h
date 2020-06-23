#ifndef game_h
#define game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"



class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Renderer* renderer;

private:
	int cnt = 0;
	bool isRunning = false;
	SDL_Window* window;
};


#endif //game_h





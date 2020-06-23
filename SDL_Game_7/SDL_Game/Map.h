#ifndef Map_h
#define Map_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "game.h"
#include "TextureManager.h"
#include "ECS.h"



class Map
{
public:
	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25];
};

#endif // Map_h
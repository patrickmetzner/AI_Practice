#ifndef TextureManager_h
#define TextureManager_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "game.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS.h"



class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest);
};

#endif //TextureManager_h




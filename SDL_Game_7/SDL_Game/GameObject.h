#ifndef GameObject_h
#define GameObject_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"




class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};

#endif //GameObject_h
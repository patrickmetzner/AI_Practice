#pragma once

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
	int levelCounter = 0;
	bool isRunning = false;
	SDL_Window* window;
};


class CarObject
{
public:
	CarObject(const char* texturesheet, int h, int w);
	~CarObject();

	void Update();
	void Render();
	int getX();
	int getY();
	int getH();
	int getW();
	void checkForCollision();
	void setStatus(bool carRunning);
	bool running();
	Uint32 getCollisionTime();

private:
	int xpos, ypos, height, width;
	bool isRunning = true;
	Uint32 collisionTime;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};

class ObstacleObject
{
public:
	ObstacleObject(const char* texturesheet, int h, int w);
	~ObstacleObject();

	void Update();
	void Render();
	void setX(int x);
	void setY(int y);
	void setH(int h);
	void setW(int w);
	int getX();
	int getY();
	int getH();
	int getW();

private:
	int xpos, ypos, height, width; 
	

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};


class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};



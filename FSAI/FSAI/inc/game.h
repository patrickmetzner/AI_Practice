#pragma once

#include "NeuralNetwork.h"

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
	bool isRunning = false;
	SDL_Window* window;
};

class CarObject
{
public:
	CarObject(const char* texturesheet, int h, int w);
	~CarObject();

	void Update();
	void moveCar();
	void checkForCollision();
	void Render();
	int getX();
	int getY();
	int getH();
	int getW();
	void setRunningStatus(bool carRunning);
	bool running();
	void setRunningTime();
	void resetRunningTime();
	Uint32 getRunningTime();

	NeuralNetwork* NeuralNetwork;

private:
	double xpos, ypos;
	int	height, width;
	bool isRunning = true;
	bool isAutonomous = false;
	Uint32 runningTime = 0;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Point imageRotationPoint, carCenter, left, front, right, rear, frontLeft, frontRight, rearLeft, rearRight;
	double rotationAngle = 0;

	
	double NeuralNetwork_InputArray[7];
	double NeuralNetwork_OutputArray[2];
};

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

void generateRandomArray(double* Array, int size);

void startNewGame();

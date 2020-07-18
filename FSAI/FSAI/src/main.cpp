#include <iostream>
#include <time.h>				// time(0)
#include "SDL.h"
#include "SDL_image.h" 
#include "game.h"
#include "NeuralNetwork.h"

#define windowHeight	650
#define windowWidth		500

Game* game = nullptr;
CarObject* car;
ObstacleObject* obstacle1;
ObstacleObject* obstacle2;
SDL_Renderer* Game::renderer = nullptr;
const Uint8* KeyboardState;

const int numberOfInputNeurons = 7 + BIAS;
const int numberOfHiddenLayers = 2;
const int numberOfHiddenNeurons = 4 + BIAS;
const int numberOfOutputNeurons = 2;
double NeuralNetwork_HiddenWeights[((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons];
double NeuralNetwork_OutputWeights[numberOfOutputNeurons * numberOfHiddenNeurons];

int main(int argc, char* argv[]) {
	srand((int)time(0));

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("FSAI", windowWidth, windowHeight, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		//controlarCarros();
		
		//verificarFimDePartida();

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



//////////////////////////////////
//								//
//			Game				//
//								//
//////////////////////////////////

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialised..." << std::endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;

	}
	else {
		isRunning = false;
	}

	car = new CarObject("images/car.png", 180, 90);
	obstacle1 = new ObstacleObject("images/obstacle.png", 20, rand() % 100 + 100);
	obstacle1->setY(windowHeight / 2);
	obstacle2 = new ObstacleObject("images/obstacle.png", 20, rand() % 100 + 100);

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	car->checkForCollision();
	if (car->running() == false) {
		SDL_Delay(1000);
		car->setStatus(true);
	}

	car->Update();
	obstacle1->Update();
	obstacle2->Update();

	if (obstacle1->getY() >= windowHeight) {
		obstacle1->setY(0);
		obstacle1->setW(rand() % 100 + 100);
		obstacle1->setX(rand() % (windowWidth - obstacle1->getW()));
	}

	if (obstacle2->getY() >= windowHeight) {
		obstacle2->setY(0);
		obstacle2->setW(rand() % 100 + 100);
		obstacle2->setX(rand() % (windowWidth - obstacle2->getW()));
	}

	levelCounter++;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	car->Render();
	obstacle1->Render();
	obstacle2->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

bool Game::running()
{
	return isRunning;
}



//////////////////////////////////
//								//
//			CarObject			//
//								//
//////////////////////////////////

CarObject::CarObject(const char* texturesheet, int h, int w) {
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = windowWidth / 2 - w / 2;
	ypos = windowHeight - h;
	height = h;
	width = w;

}

CarObject::~CarObject() {

}

void CarObject::Update() {
	KeyboardState = SDL_GetKeyboardState(NULL);
	if (KeyboardState[SDL_SCANCODE_LEFT] && xpos >= 0)
		xpos -= 5;

	if (KeyboardState[SDL_SCANCODE_RIGHT] && xpos <= windowWidth - width)
		xpos += 5;

	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}

void CarObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

int CarObject::getX() {
	return xpos;
}

int CarObject::getY() {
	return ypos;
}

int CarObject::getH() {
	return height;
}

int CarObject::getW() {
	return width;
}

void CarObject::checkForCollision() {

	if ((obstacle1->getY() + obstacle1->getH()) >= windowHeight - height) {
		if ((obstacle1->getX() - width) <= xpos && xpos <= (obstacle1->getX() + obstacle1->getW()))
			isRunning = false;
	}

	if ((obstacle2->getY() + obstacle2->getH()) >= windowHeight - height) {
		if ((obstacle2->getX() - width) <= xpos && xpos <= (obstacle2->getX() + obstacle2->getW()))
			isRunning = false;
	}
}

void CarObject::setStatus(bool carRunning) {
	isRunning = carRunning;
}

bool CarObject::running() {
	return isRunning;
}

Uint32 CarObject::getCollisionTime() {
	return collisionTime;
}



//////////////////////////////////
//								//
//		ObstacleObject			//
//								//
//////////////////////////////////

ObstacleObject::ObstacleObject(const char* texturesheet, int h, int w) {
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = rand() % 400;
	ypos = 0;
	height = h;
	width = w;

	std::cout << "Obstacle created" << std::endl;
}

ObstacleObject::~ObstacleObject() {
	std::cout << "Obstacle destroyed" << std::endl;
}

void ObstacleObject::Update() {
	ypos += 2;

	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
}

void ObstacleObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void ObstacleObject::setX(int x) {
	xpos = x;
}

void ObstacleObject::setY(int y) {
	ypos = y;
}

void ObstacleObject::setH(int h) {
	height = h;
}

void ObstacleObject::setW(int w) {
	width = w;
}

int ObstacleObject::getX() {
	return xpos;
}

int ObstacleObject::getY() {
	return ypos;
}

int ObstacleObject::getH() {
	return height;
}

int ObstacleObject::getW() {
	return width;
}



//////////////////////////////////
//								//
//			Functions			//
//								//
//////////////////////////////////

int getUpperObstacleX() {
	int upperObstacleX;
	if (obstacle1->getY() < obstacle2->getY()) {
		upperObstacleX = obstacle1->getX();
	}
	else {
		upperObstacleX = obstacle2->getX();
	}

	return upperObstacleX;
}

int getUpperObstacleY() {
	int upperObstacleY;
	if (obstacle1->getY() < obstacle2->getY()) {
		upperObstacleY = obstacle1->getY();
	}
	else {
		upperObstacleY = obstacle2->getY();
	}

	return upperObstacleY;
}

int getUpperObstacleW() {
	int upperObstacleW;
	if (obstacle1->getY() < obstacle2->getY()) {
		upperObstacleW = obstacle1->getW();
	}
	else {
		upperObstacleW = obstacle2->getW();
	}

	return upperObstacleW;
}

int getLowerObstacleX() {
	int lowerObstacleX;
	if (obstacle1->getY() > obstacle2->getY()) {
		lowerObstacleX = obstacle1->getX();
	}
	else {
		lowerObstacleX = obstacle2->getX();
	}

	return lowerObstacleX;
}

int getLowerObstacleY() {
	int lowerObstacleY;
	if (obstacle1->getY() > obstacle2->getY()) {
		lowerObstacleY = obstacle1->getY();
	}
	else {
		lowerObstacleY = obstacle2->getY();
	}

	return lowerObstacleY;
}

int getLowerObstacleW() {
	int lowerObstacleW;
	if (obstacle1->getY() > obstacle2->getY()) {
		lowerObstacleW = obstacle1->getW();
	}
	else {
		lowerObstacleW = obstacle2->getW();
	}

	return lowerObstacleW;
}



//////////////////////////////////
//								//
//		TextureManager			//
//								//
//////////////////////////////////

SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

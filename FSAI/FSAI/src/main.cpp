#include <iostream>
#include <time.h>				// time(0)
#include "SDL.h"
#include "SDL_image.h" 
#include "game.h"
#include "NeuralNetwork.h"
#include <math.h>
#pragma warning(disable : 4996)	// fopen and sprintf

#define windowHeight			650
#define windowWidth				650

#define numberOfInputNeurons	(7 + BIAS)
#define numberOfHiddenLayers	(2)
#define numberOfHiddenNeurons	(4 + BIAS)
#define numberOfOutputNeurons	(2)
#define numberOfCars			1

Game* game = nullptr;
CarObject* car[numberOfCars];
SDL_Renderer* Game::renderer = nullptr;
const Uint8* KeyboardState;

double NeuralNetwork_HiddenWeights[((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons];
double NeuralNetwork_OutputWeights[numberOfOutputNeurons * numberOfHiddenNeurons];

int numberOfCrashedCars = 0;
int numberOfCrashedCars_old = 0;

Uint32 trainingClock = 0;
Uint32 endOfLastTrainingSession = 0;

int main(int argc, char* argv[]) {
	srand((int)time(0));

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	int counter_PrintTime = 0;

	game = new Game();
	game->init("FSAI", windowWidth, windowHeight, false);
	endOfLastTrainingSession = SDL_GetTicks();

	while (game->running()) {
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();

		/*
		KeyboardState = SDL_GetKeyboardState(NULL);
		if (numberOfCrashedCars >= (numberOfCars - 1) || (KeyboardState[SDL_SCANCODE_N])) {
			startNewGame();
			SDL_Delay(1000);
			numberOfCrashedCars_old = 0;
			endOfLastTrainingSession = SDL_GetTicks();
		}

		if (counter_PrintTime == 10 * FPS) {
			counter_PrintTime = 0;
			std::cout << "Time = " << (double)trainingClock / 1000 << "\n";
		}
		counter_PrintTime++;
		*/

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		else {
			std::cout << "Time Out!\n";
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

	for (int i = 0; i < numberOfCars; i++) {
		car[i] = new CarObject("images/car.png", 180, 90);
	}
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
	trainingClock = SDL_GetTicks() - endOfLastTrainingSession;

	numberOfCrashedCars = 0;
	for (int i = 0; i < numberOfCars; i++) {
		car[i]->checkForCollision();
		if (car[i]->running() == true) {
			car[i]->Update();
		}
		else {
			numberOfCrashedCars++;
		}
	}

	if (numberOfCrashedCars > numberOfCrashedCars_old) {
		numberOfCrashedCars_old = numberOfCrashedCars;
		std::cout << "Time = " << (double)trainingClock/1000 << "\t || \t" << numberOfCrashedCars << " Cars crashed.\n";
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (int i = 0; i < numberOfCars; i++) {
		if (car[i]->running() == true) {
			car[i]->Render();
		}
	}

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

	height = h;
	width = w;
	xpos = windowWidth/2 - width/2;
	ypos = windowHeight - h;

	imageRotationPoint.x = width / 2;
	imageRotationPoint.y = height * 3/4;

	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h;
	destRect.w = srcRect.w;

	NeuralNetwork = NeuralNetwork_CreateNeuralNetwork(numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons);
}

CarObject::~CarObject() {

}

void CarObject::Update() {
	runningTime = trainingClock;

	moveCar();

	checkForCollision();
}

void CarObject::moveCar() {
	if (isAutonomous == false) {
		KeyboardState = SDL_GetKeyboardState(NULL);
		if (KeyboardState[SDL_SCANCODE_LEFT] && (KeyboardState[SDL_SCANCODE_UP] || KeyboardState[SDL_SCANCODE_DOWN])) {
			rotationAngle -= 5;
		}

		if (KeyboardState[SDL_SCANCODE_RIGHT] && (KeyboardState[SDL_SCANCODE_UP] || KeyboardState[SDL_SCANCODE_DOWN])) {
			rotationAngle += 5;
		}

		if (KeyboardState[SDL_SCANCODE_UP]) {
			xpos += 10 * sin(rotationAngle * M_PI / 180);
			ypos -= 10 * cos(rotationAngle * M_PI / 180);
		}

		if (KeyboardState[SDL_SCANCODE_DOWN]) {
			xpos -= 5 * sin(rotationAngle * M_PI / 180);
			ypos += 5 * cos(rotationAngle * M_PI / 180);
		}
	}
	else {
		/*
		NeuralNetwork_InputArray[0] = (double)getUpperObstacleY();
		NeuralNetwork_InputArray[1] = (double)getUpperObstacleX();
		NeuralNetwork_InputArray[2] = (double)windowWidth - (double)getUpperObstacleX() - (double)getUpperObstacleW();
		NeuralNetwork_InputArray[3] = (double)getLowerObstacleY();
		NeuralNetwork_InputArray[4] = (double)getLowerObstacleX();
		NeuralNetwork_InputArray[5] = (double)windowWidth - (double)getLowerObstacleX() - (double)getLowerObstacleW();
		NeuralNetwork_InputArray[6] = (double)xpos;

		NeuralNetwork_CalculateOutput(NeuralNetwork, NeuralNetwork_InputArray, NeuralNetwork_OutputArray);
		if (NeuralNetwork_OutputArray[0] > 0 && xpos >= 0) {
			xpos -= 5;
		}

		if (NeuralNetwork_OutputArray[1] > 0 && xpos <= windowWidth - width) {
			xpos += 5;
		}
		*/
	}

	destRect.x = xpos;
	destRect.y = ypos;
}

void CarObject::checkForCollision() {
	carCenter.x = xpos + imageRotationPoint.x + (imageRotationPoint.y - height / 2) * sin(rotationAngle * M_PI / 180);
	carCenter.y = ypos + imageRotationPoint.y - (imageRotationPoint.y - height / 2) * cos(rotationAngle * M_PI / 180);

	front.x = carCenter.x + (height / 2) * sin(rotationAngle * M_PI / 180);
	front.y = carCenter.y - (height / 2) * cos(rotationAngle * M_PI / 180);

	rear.x = carCenter.x - (height / 2) * sin(rotationAngle * M_PI / 180);
	rear.y = carCenter.y + (height / 2) * cos(rotationAngle * M_PI / 180);

	left.x = carCenter.x - (width / 2) * cos(rotationAngle * M_PI / 180);
	left.y = carCenter.y - (width / 2) * sin(rotationAngle * M_PI / 180);

	right.x = carCenter.x + (width / 2) * cos(rotationAngle * M_PI / 180);
	right.y = carCenter.y + (width / 2) * sin(rotationAngle * M_PI / 180);

	double frontLeftAngle = (rotationAngle - (atan((double)((double)width / (double)height)) * 180 / M_PI));
	frontLeft.x = carCenter.x + hypot((height / 2), (width / 2)) * sin(frontLeftAngle * M_PI / 180);
	frontLeft.y = carCenter.y - hypot((height / 2), (width / 2)) * cos(frontLeftAngle * M_PI / 180);

	double frontRightAngle = (rotationAngle + (atan((double)((double)width / (double)height)) * 180 / M_PI));
	frontRight.x = carCenter.x + hypot((height / 2), (width / 2)) * sin(frontRightAngle * M_PI / 180);
	frontRight.y = carCenter.y - hypot((height / 2), (width / 2)) * cos(frontRightAngle * M_PI / 180);

	double rearLeftAngle = (rotationAngle + (atan((double)((double)width / (double)height)) * 180 / M_PI));
	rearLeft.x = carCenter.x - hypot((height / 2), (width / 2)) * sin(rearLeftAngle * M_PI / 180);
	rearLeft.y = carCenter.y + hypot((height / 2), (width / 2)) * cos(rearLeftAngle * M_PI / 180);

	double rearRightAngle = (rotationAngle - (atan((double)((double)width / (double)height)) * 180 / M_PI));
	rearRight.x = carCenter.x - hypot((height / 2), (width / 2)) * sin(rearRightAngle * M_PI / 180);
	rearRight.y = carCenter.y + hypot((height / 2), (width / 2)) * cos(rearRightAngle * M_PI / 180);
	
	if (
		front.x < 0 || front.x > windowWidth || front.y < 0 || front.y > windowHeight ||
		rear.x < 0 || rear.x > windowWidth || rear.y < 0 || rear.y > windowHeight ||
		left.x < 0 || left.x > windowWidth || left.y < 0 || left.y > windowHeight ||
		right.x < 0 || right.x > windowWidth || right.y < 0 || right.y > windowHeight ||
		frontLeft.x < 0 || frontLeft.x > windowWidth || frontLeft.y < 0 || frontLeft.y > windowHeight ||
		frontRight.x < 0 || frontRight.x > windowWidth || frontRight.y < 0 || frontRight.y > windowHeight ||
		rearLeft.x < 0 || rearLeft.x > windowWidth || rearLeft.y < 0 || rearLeft.y > windowHeight ||
		rearRight.x < 0 || rearRight.x > windowWidth || rearRight.y < 0 || rearRight.y > windowHeight
		) 
	{
		std::cout << "Collision!\n";
	}
	else {
		std::cout << "No collision!\n";
	}
}

void CarObject::Render() {
	SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, rotationAngle, &imageRotationPoint, SDL_FLIP_NONE);
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

void CarObject::setRunningStatus(bool carRunning) {
	isRunning = carRunning;
}

bool CarObject::running() {
	return isRunning;
}

void CarObject::setRunningTime() {
	runningTime = trainingClock;
}

void CarObject::resetRunningTime() {
	runningTime = 0;
}

Uint32 CarObject::getRunningTime() {
	return runningTime;
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



//////////////////////////////////
//								//
//			Functions			//
//								//
//////////////////////////////////

void generateRandomArray(double* Array, int size) {
	for (int i = 0; i < size; i++) {
		Array[i] = (double)(rand() % 2000 - (double)1000) / 1000;
	}
}

void startNewGame() {
	int bestCarIndex = 0;
	Uint32 bestRunningTime = 0;

	for (int i = 0; i < numberOfCars; i++) {
		if (car[i]->getRunningTime() > bestRunningTime) {
			bestRunningTime = car[i]->getRunningTime();
			bestCarIndex = i;
		}
	}

	char fileName[1000];
	sprintf(fileName, "trainingFiles\\%.3f - [%d][%.4f][%d, %d, %d, %d].txt",
		(double)car[bestCarIndex]->getRunningTime() / 1000, bestCarIndex, learningRate, (numberOfInputNeurons - BIAS), numberOfHiddenLayers, (numberOfHiddenNeurons - BIAS), numberOfOutputNeurons);

	NeuralNetwork_CopyNeuralNetworkToArrays(car[bestCarIndex]->NeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);
	NeuralNetwork_CopyArraysToFile(fileName, numberOfInputNeurons, numberOfHiddenLayers, numberOfHiddenNeurons, numberOfOutputNeurons, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);

	for (int i = 0; i < numberOfCars; i++) {
		NeuralNetwork_CopyArraysToNeuralNetwork(car[i]->NeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);
		car[i]->setRunningStatus(true);
		car[i]->resetRunningTime();
	}

	int sizeOfHiddenWeightsArray = ((numberOfHiddenLayers - 1) * numberOfHiddenNeurons * numberOfHiddenNeurons) + numberOfInputNeurons * numberOfHiddenNeurons;
	int sizeOfOutputWeightsArray = numberOfOutputNeurons * numberOfHiddenNeurons;
	int sizeOfNeuralNetwork = sizeOfHiddenWeightsArray + sizeOfOutputWeightsArray;
	{
		int numberOfMutations = ceil(learningRate * (double)(sizeOfNeuralNetwork));
		std::cout << "Number Of Mutations: \t" << numberOfMutations << "\n";
	}

	for (int i = 1; i < (int)(numberOfCars / 2); i++) {
		NeuralNetwork_RandomMutations(car[i]->NeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);
	}

	for (int i = (int)(numberOfCars / 2) + 1; i < numberOfCars; i++) {
		generateRandomArray(NeuralNetwork_HiddenWeights, sizeOfHiddenWeightsArray);
		generateRandomArray(NeuralNetwork_OutputWeights, sizeOfOutputWeightsArray);
		NeuralNetwork_CopyArraysToNeuralNetwork(car[i]->NeuralNetwork, NeuralNetwork_HiddenWeights, NeuralNetwork_OutputWeights);
	}
}
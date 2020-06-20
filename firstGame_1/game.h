#ifndef game_h
#define game_h

#include "SDL.h"
#include <iostream>

// Os arquivos .h contém os protótipos das classes e funções utilizadas ao longo dos programas em C ou C++.
/* 
Esse arquivo é destinado aos protótipos das funções da classe Game, 
assim como declarar os valores inciais dos argumentos dessas funções (quando houver).
*/
/*
Observe que no fim do arquivo são criados os ponteiros para "window" e "renderer".
A alocação dinâmica de memória desses objetos é feita em game.cpp -- dentro do if(SDL_Init(SDL_INIT_EVERYTHING)==0)
*/

/*
Os protótipos das funções devem conter as variáveis necessárias para a execução da funcão, 
mas não descrevem o que a função de fato faz.
*/


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





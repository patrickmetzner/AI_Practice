#ifndef game_h
#define game_h

#include "SDL.h"
#include <iostream>

// Os arquivos .h cont�m os prot�tipos das classes e fun��es utilizadas ao longo dos programas em C ou C++.
/* 
Esse arquivo � destinado aos prot�tipos das fun��es da classe Game, 
assim como declarar os valores inciais dos argumentos dessas fun��es (quando houver).
*/
/*
Observe que no fim do arquivo s�o criados os ponteiros para "window" e "renderer".
A aloca��o din�mica de mem�ria desses objetos � feita em game.cpp -- dentro do if(SDL_Init(SDL_INIT_EVERYTHING)==0)
*/

/*
Os prot�tipos das fun��es devem conter as vari�veis necess�rias para a execu��o da func�o, 
mas n�o descrevem o que a fun��o de fato faz.
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





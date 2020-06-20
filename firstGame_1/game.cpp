#include "SDL.h"
#include <iostream>
#include "game.h"

// Esse arquivo "complementa" o arquivo game.h
// Aqui ser�o descritas as rotinas realizadas por cada uma das fun��es prototipadas em game.h
// At� este ponto do c�digo algumas fun��es ainda est�o vazias.

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title,  int width, int height, bool fullscreen)
{
	int flags = 0; //apenas criando uma vari�vel 

	if (fullscreen) //if (fullscreen) � apenas uma forma mais compacta de escrever if (fullscreen==1) 
	{
		flags = SDL_WINDOW_FULLSCREEN;  
	}
	/*
	Dentro da biblioteca SDL, quando SDL_WINDOW_FULLSCREEN (linha 25) � passado como o �ltimo argumento da fun��o
	SDL_CreateWindow (dentro do "if" abaixo), a janela criada no jogo ocupa a tela toda do PC. 
	Caso o �ltimo argumento da fun��o seja zero, a janela � criada com tamanho equivalente �s vari�veis "width" e "height".
	"width" e "height" s�o passadas como argumentos da fun��o init() da classe Game.
	*/


	/*
	A fun��o SDL_Init() retorna ZERO quando ela � executada com sucesso.

	escrever if(SDL_Init(SDL_INIT_EVERYTHING) == 0) � um jeito compacto de verificar se a fun��o foi executada com sucesso. 
	*/
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialised..." << std::endl;//apenas escreve na tela
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		
		//Ao passar o mouse em cima da fun��o SDL_CreateWindow acima, pode-se ver que ela retorna NULL caso algo errado aconte�a
		if (window) //Verificando se a vari�vel "window" (retorno da func�o SDL_CreateWindow) � diferente de NULL
		{
			std::cout << "Window created!" << std::endl;
		}

		//Mesma ideia do "if" acima, dessa vez para a renderiza��o da tela do jogo.
		//Passando o mouse por cima das fun��es, vc pode ver um resuminho do que elas fazem.
		renderer = SDL_CreateRenderer(window, -1, 0); 
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;//vari�vel que faz o loop do programa acontecer repetidamente (linha 43 de main.cpp)

	}
	else {//quando (SDL_Init(SDL_INIT_EVERYTHING) == 0) n�o � verdadeiro significa que algo deu errado e o programa para
		isRunning = false;
	}
}

//Por enquanto essa fun��o apenas verifica se n�o h� nada mandando o programa parar (SDL_QUIT)
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

//Por enquanto essa fun��o apenas "imprime" um contador na janela de comandos. int cnt foi declarado no fim de game.h
void Game::update()
{
	cnt++;
	std::cout << cnt << std::endl;
}

//Cada vez que essa fun��o � chamada, ela limpa a tela e renderiza novamente, ap�s atualizar o estado de cada "coisa"
void Game::render()
{
	SDL_RenderClear(renderer);
	// this is where we will add stuff to render
	SDL_RenderPresent(renderer);
}

/*visto que na linha 28 de main.cpp foi realizada a aloca��o din�mica de mem�ria para criar o objeto game,
ao finalizar o programa precisamos liberar o espa�o do HEAP da mem�ria para que ela possa ser usada para outras coisas*/
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

//apenas retorna o valor da vari�vel "isRunning"
//visto que "isRunning" � uma vari�vel privada, a fun��o running() � necess�ria para que ela seja acessada pela main().
bool Game::running()
{
	return isRunning;
}




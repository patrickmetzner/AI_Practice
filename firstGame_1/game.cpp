#include "SDL.h"
#include <iostream>
#include "game.h"

// Esse arquivo "complementa" o arquivo game.h
// Aqui serão descritas as rotinas realizadas por cada uma das funções prototipadas em game.h
// Até este ponto do código algumas funções ainda estão vazias.

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title,  int width, int height, bool fullscreen)
{
	int flags = 0; //apenas criando uma variável 

	if (fullscreen) //if (fullscreen) é apenas uma forma mais compacta de escrever if (fullscreen==1) 
	{
		flags = SDL_WINDOW_FULLSCREEN;  
	}
	/*
	Dentro da biblioteca SDL, quando SDL_WINDOW_FULLSCREEN (linha 25) é passado como o último argumento da função
	SDL_CreateWindow (dentro do "if" abaixo), a janela criada no jogo ocupa a tela toda do PC. 
	Caso o último argumento da função seja zero, a janela é criada com tamanho equivalente às variáveis "width" e "height".
	"width" e "height" são passadas como argumentos da função init() da classe Game.
	*/


	/*
	A função SDL_Init() retorna ZERO quando ela é executada com sucesso.

	escrever if(SDL_Init(SDL_INIT_EVERYTHING) == 0) é um jeito compacto de verificar se a função foi executada com sucesso. 
	*/
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems initialised..." << std::endl;//apenas escreve na tela
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		
		//Ao passar o mouse em cima da função SDL_CreateWindow acima, pode-se ver que ela retorna NULL caso algo errado aconteça
		if (window) //Verificando se a variável "window" (retorno da funcão SDL_CreateWindow) é diferente de NULL
		{
			std::cout << "Window created!" << std::endl;
		}

		//Mesma ideia do "if" acima, dessa vez para a renderização da tela do jogo.
		//Passando o mouse por cima das funções, vc pode ver um resuminho do que elas fazem.
		renderer = SDL_CreateRenderer(window, -1, 0); 
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;//variável que faz o loop do programa acontecer repetidamente (linha 43 de main.cpp)

	}
	else {//quando (SDL_Init(SDL_INIT_EVERYTHING) == 0) não é verdadeiro significa que algo deu errado e o programa para
		isRunning = false;
	}
}

//Por enquanto essa função apenas verifica se não há nada mandando o programa parar (SDL_QUIT)
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

//Por enquanto essa função apenas "imprime" um contador na janela de comandos. int cnt foi declarado no fim de game.h
void Game::update()
{
	cnt++;
	std::cout << cnt << std::endl;
}

//Cada vez que essa função é chamada, ela limpa a tela e renderiza novamente, após atualizar o estado de cada "coisa"
void Game::render()
{
	SDL_RenderClear(renderer);
	// this is where we will add stuff to render
	SDL_RenderPresent(renderer);
}

/*visto que na linha 28 de main.cpp foi realizada a alocação dinâmica de memória para criar o objeto game,
ao finalizar o programa precisamos liberar o espaço do HEAP da memória para que ela possa ser usada para outras coisas*/
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

//apenas retorna o valor da variável "isRunning"
//visto que "isRunning" é uma variável privada, a função running() é necessária para que ela seja acessada pela main().
bool Game::running()
{
	return isRunning;
}




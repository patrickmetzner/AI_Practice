#include "SDL.h"
#include <iostream>
#include "game.h"

/*
Esse programa apenas cria uma tela inicial do nosso jogo, mas acho que ele é uma base importante pro projeto FSAI.

Acho que o jeito mais fácil de acompanhar esse código e os comentáios é começar por:
1- main.cpp
2- game.h
3- game.cpp
*/


//Cria um ponteiro vazio para o novo objeto game. O objeto game é da classe Game. 
Game *game = nullptr;

//argc = numero de comandos enviados pela linha de comando quando o arquivo .exe é executado
//argv[] = vetor com o conteúdo de cada comando enviado pela linha de comando quando o arquivo .exe é executado
//O arquivo SDL2main.lib usa esses parametros então eles precisam ser criados. 
int main(int argc, char* argv[])
{
	/*	
	cria o novo objeto game (da classe Game). 
	A palavra "new" é utilizada para que uma variável (neste caso um objeto) seja armazenana na memória HEAP (alocação dinâmica de memória).
	Utilizar alocação dinâmica de memória otimiza a utilização da memória do PC.
	*/
	game = new Game(); 

	//Chama a função init() do objeto game.
	//game->init(); é equivalente a escrever *game.init();
	//Visto que game é um ponteiro (criado na linha 16 deste código), game->init(); é mais conveniente.
	game->init("First Game", 800, 600, false);


	
	/*
	No arquivo game.cpp é possivel ver que a função running(), da classe Game, retorna o valor da variável "isRunning".
	O valor "true", ou seja, 1, é atribuido à essa variável "isRunning" na função init() da classe Game, quando tudo 
	acontece de acordo com o planejado.
	Escrever while (game->running()) é equivalente a escrever while (1) quando tudo ocorre conforme o planejado.
	*/
	while (game->running()) //Esse loop vai rodar continuamente enquanto o programa estiver sendo executado.
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	/*visto que na linha 28 foi realizada a alocação dinâmica de memória para criar o objeto game, 
	ao finalizar o programa precisamos liberar o espaço do HEAP da memória para que ela possa ser usada para outras coisas*/
	game->clean();

	//a função main() deve retornar um resultado do tipo int, então é padrão terminar o código com "return 0"
	return 0;
}
#include "SDL.h"
#include <iostream>
#include "game.h"

/*
Esse programa apenas cria uma tela inicial do nosso jogo, mas acho que ele � uma base importante pro projeto FSAI.

Acho que o jeito mais f�cil de acompanhar esse c�digo e os coment�ios � come�ar por:
1- main.cpp
2- game.h
3- game.cpp
*/


//Cria um ponteiro vazio para o novo objeto game. O objeto game � da classe Game. 
Game *game = nullptr;

//argc = numero de comandos enviados pela linha de comando quando o arquivo .exe � executado
//argv[] = vetor com o conte�do de cada comando enviado pela linha de comando quando o arquivo .exe � executado
//O arquivo SDL2main.lib usa esses parametros ent�o eles precisam ser criados. 
int main(int argc, char* argv[])
{
	/*	
	cria o novo objeto game (da classe Game). 
	A palavra "new" � utilizada para que uma vari�vel (neste caso um objeto) seja armazenana na mem�ria HEAP (aloca��o din�mica de mem�ria).
	Utilizar aloca��o din�mica de mem�ria otimiza a utiliza��o da mem�ria do PC.
	*/
	game = new Game(); 

	//Chama a fun��o init() do objeto game.
	//game->init(); � equivalente a escrever *game.init();
	//Visto que game � um ponteiro (criado na linha 16 deste c�digo), game->init(); � mais conveniente.
	game->init("First Game", 800, 600, false);


	
	/*
	No arquivo game.cpp � possivel ver que a fun��o running(), da classe Game, retorna o valor da vari�vel "isRunning".
	O valor "true", ou seja, 1, � atribuido � essa vari�vel "isRunning" na fun��o init() da classe Game, quando tudo 
	acontece de acordo com o planejado.
	Escrever while (game->running()) � equivalente a escrever while (1) quando tudo ocorre conforme o planejado.
	*/
	while (game->running()) //Esse loop vai rodar continuamente enquanto o programa estiver sendo executado.
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	/*visto que na linha 28 foi realizada a aloca��o din�mica de mem�ria para criar o objeto game, 
	ao finalizar o programa precisamos liberar o espa�o do HEAP da mem�ria para que ela possa ser usada para outras coisas*/
	game->clean();

	//a fun��o main() deve retornar um resultado do tipo int, ent�o � padr�o terminar o c�digo com "return 0"
	return 0;
}
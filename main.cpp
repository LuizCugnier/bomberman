/**
 * 
 * Bomberman
 * Versão: 1.0
 * Luiz Augusto Cugnier Neto
 * Lucas Carvalho de Borba
*/

#include <time.h>
#include "game.h"


using namespace std;

int main(){
    //Declara do layout do mapa do jogo
    int gameMap[15][15];

    Game game; //Inicia a struct referente ao jogo
    
    game.mainLoop(gameMap); //Chama a função principal do jogo passando o mapa 

    return 0;
}
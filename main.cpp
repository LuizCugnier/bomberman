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
    int gameMap[15][15]={       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,0,0,0,0,0,2,2,2,0,0,0,0,0,1,
                                1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,
                                1,0,0,0,0,0,2,2,2,2,2,0,0,0,1,
                                1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,
                                1,0,0,2,0,2,2,2,2,2,2,2,0,0,1,
                                1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
                                1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
                                1,2,1,0,1,2,1,2,1,0,1,2,1,2,1,
                                1,0,0,0,2,2,2,2,2,2,2,2,0,0,1,
                                1,0,1,0,1,2,1,2,1,2,1,2,1,0,1,
                                1,0,0,0,0,2,2,2,2,2,2,2,0,0,1,
                                1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,
                                1,0,0,0,0,0,2,2,2,2,0,0,0,0,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };

    Game game; //Inicia a struct referente ao jogo
    
    game.mainLoop(gameMap); //Chama a função principal do jogo passando o mapa 

    return 0;
}
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

    Game game; //Inicia a struct referente ao jogo
    Map map; //Cria a struct map (no momento apenas tem a função para imprimir o mapa pois o mapa é declarado na main e passado como parâmetro)
    
    game.mainLoop(map); //Chama a função principal do jogo passando o mapa 

    map.deleteMap();

    return 0;
}
/**
 * 
 * Bomberman
 * Versão: 2.0
 * Luiz Augusto Cugnier Neto
 * Lucas Carvalho de Borba
*/

#include <time.h>
#include "game.h"


using namespace std;
 
int main(){

    Game game; //Inicia a struct referente ao jogo

    Map map; //Cria a struct map (no momento apenas tem a função para imprimir o mapa pois o mapa é declarado na main e passado como parâmetro)
    Config config; //Cria a struct das configurações
    Menu menu; //Cria a struct do menu 
    Input input; // Cria a struct das entradas do usuário
    
    game.mainLoop(config, map, menu, input); //Chama a função principal do jogo passando o mapa 
    
    

    return 0;
}
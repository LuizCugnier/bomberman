#include "menu.h"
#include "input.h"
#include "map.h"
#include "config.h"

using namespace std;

Config config; //Cria a struct das configurações
Map map; //Cria a struct map (no momento apenas tem a função para imprimir o mapa pois o mapa é declarado na main e passado como parâmetro)
Menu menu; //Cria a struct do menu 
Input input; // Cria a struct das entradas do usuário


struct Game //Struct do jogo
{
    bool gameRunning = true; //Variável que indica se o jogo está rodando

    //Loop principal do jogo
    void mainLoop(int (&gameMap)[15][15]){
        
        menu.mainMenu(); //Chama a função para imprimir o menu

        switch (input.menuChoise())
        {
        case 1:
            newGame(gameMap);//Começa um novo jogo
            break;
        case 2:
            //Continua um jogo ativo
            break;
        case 3:
            menu.sobreMenu();
            break;
        default:
            break;
        }


    }

    //Função que inicia um novo jogo
    void newGame(int (&gameMap)[15][15]){
        gameLoop(gameMap); //Chama o loop do jogo
    }

    //Funcão do loop do jogo
    void gameLoop(int (&gameMap)[15][15]){
        system("cls");

        while (gameRunning)
        {
            config.setCursor(0, 0); //Chama a função dentro da struct config, que configura o cursor
            map.printMap(gameMap); //Chama a função para imprimir o mapa
            input.moviments(gameMap, gameRunning); //Chama função que verifica as entradas do usuário
            input.bombExplode(gameMap); //Chama a função que cuida da explosão da bomba
            gameLogic(gameMap); // Chama a função que cuida da lógica do jogo
        }
    }
    
    //Função que cuida da lógica do jogo
    void gameLogic(int (&gameMap)[15][15]){
        pEnemy->enemyMoveCounter++;
        //cout << pEnemy->enemyMoveCounter;

        //Delay dos movimentos dos inimigos
        if (pEnemy->enemyMoveCounter == 50){
            input.enemyMoviments(gameMap, pEnemy->enemy1X, pEnemy->enemy1Y);
            input.enemyMoviments(gameMap, pEnemy->enemy2X, pEnemy->enemy2Y);
            pEnemy->enemyMoveCounter = 0;
        }

        if (gameMap[pPlayer->playerX][pPlayer->playerY] == 4) { // condição de fim : explodiu com a bomba
            gameRunning = false;
        }
        if ((pPlayer->playerX == pEnemy->enemy1X && pPlayer->playerY == pEnemy->enemy1Y) || (pPlayer->playerX == pEnemy->enemy2X && pPlayer->playerY == pEnemy->enemy2Y)) {
            gameRunning = false; // o jogador colidiu com um inimigo
        }
        if (gameMap[pEnemy->enemy1X][pEnemy->enemy1Y] == 4) {
            pEnemy->enemy1X = -1; // o primeiro inimigo foi atingido pela explosão da bomba
        }
        if (gameMap[pEnemy->enemy2X][pEnemy->enemy2Y] == 4) {
            pEnemy->enemy2X = -1; // o segundo inimigo foi atingido pela explosão da bomba
        }
        if (pEnemy->enemy1X == -1 && pEnemy->enemy2X == -1) {
            cout << "\nVOCÊ VENCEU!"; 
            gameRunning = false; // verifica se o jogador matou todos os inimigos  
        }
    }

};

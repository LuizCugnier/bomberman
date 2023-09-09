#include "menu.h"
#include "input.h"
#include "map.h"
#include "config.h"

using namespace std;

Config config;
Map map;
Menu menu;
Input input;


struct Game
{
    bool gameRunning = true;

    void mainLoop(int (&gameMap)[15][15]){
        //Loop principal do jogo
        menu.mainMenu();

        switch (input.menuChoise())
        {
        case 1:
            newGame(gameMap);
            break;
        
        default:
            break;
        }


    }

    void newGame(int (&gameMap)[15][15]){
        //inicia um novo jogo
        gameLoop(gameMap);
    }

    void gameLoop(int (&gameMap)[15][15]){
        //loop do jogo
        system("cls");

        while (gameRunning)
        {
            config.setCursor(0, 0);
            map.printMap(gameMap);
            input.moviments(gameMap, gameRunning);
            input.bombExplode(gameMap);
            gameLogic(gameMap);
        }
    }
    
    void gameLogic(int (&gameMap)[15][15]){
        pEnemy->enemyMoveCounter++;
        cout << pEnemy->enemyMoveCounter;
        if (pEnemy->enemyMoveCounter == 100){
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

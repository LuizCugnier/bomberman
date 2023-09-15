#ifndef GAME_H
#define GAME_H


using namespace std;

#include "map.h"


struct Game //Struct do jogo
{
    bool menuRunning = true;
    bool gameRunning = true; //Variável que indica se o jogo está rodando

    //Loop principal do jogo
    void mainLoop(Config config, Map map, Menu menu, Input input, int (&gameMap)[15][15]){
        
        menu.mainMenu(); //Chama a função para imprimir o menu

        while (menuRunning){
            if (_kbhit()){  
                input.inputMenu = _getch();

                switch (input.inputMenu)
                {
                    case '0':
                        menu.mainMenu(); //Imprime o menu 
                        break;
                    case '1':
                        newGame(config, map, menu, input, gameMap);//Começa um novo jogo
                        break;
                    case '2':
                        //Continua um jogo ativo
                        break;
                    case '3':
                        menu.sobreMenu();//Informações do jogo
                        break;
                    case '4':
                        //função termina jogo
                        endGame();
                    default:
                        break;
                }
            }
        }


    }

    void endGame(){
        menuRunning = false; //Termina o jogo
        system("cls");
    }

    //Função que inicia um novo jogo
    void newGame(Config config, Map map, Menu menu, Input input, int (&gameMap)[15][15]){
        gameRunning = true;
        gameLoop(config, map, menu, input, gameMap); //Chama o loop do jogo
    }

    //Funcão do loop do jogo
    void gameLoop(Config config, Map map, Menu menu, Input input, int (&gameMap)[15][15]){
        system("cls");

        while (gameRunning)
        {
            config.setCursor(0, 0); //Chama a função dentro da struct config, que configura o cursor
            map.printMap(gameMap); //Chama a função para imprimir o mapa
            input.moviments(menu, gameMap, gameRunning); //Chama função que verifica as entradas do usuário
            input.bombExplode(gameMap); //Chama a função que cuida da explosão da bomba
            gameLogic(input, gameMap); // Chama a função que cuida da lógica do jogo
        }
    }
    
    //Função que cuida da lógica do jogo
    void gameLogic(Input input, int (&gameMap)[15][15]){
        pEnemy->enemyMoveCounter++;
        //cout << pEnemy->enemyMoveCounter;

        //Delay dos movimentos dos inimigos
        if (pEnemy->enemyMoveCounter == 50){
            input.enemyMoviments(gameMap, pEnemy->enemy1X, pEnemy->enemy1Y);
            input.enemyMoviments(gameMap, pEnemy->enemy2X, pEnemy->enemy2Y);
            pEnemy->enemyMoveCounter = 0;
        }

        if (gameMap[pPlayer->playerX][pPlayer->playerY] == 4) { // condição de fim : explodiu com a bomba
            cout << "\nVOce Perdeu!!!!";
            Sleep(2000);
            gameRunning = false;
        }
        if ((pPlayer->playerX == pEnemy->enemy1X && pPlayer->playerY == pEnemy->enemy1Y) || (pPlayer->playerX == pEnemy->enemy2X && pPlayer->playerY == pEnemy->enemy2Y)) {
            cout << "\nVOce Perdeu!!!!";
            Sleep(2000);
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
#endif

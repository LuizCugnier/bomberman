#include "menu.h"
#include "input.h"
#include "map.h"
#include "config.h"

using namespace std;

Config config; //Cria a struct das configurações

Menu menu; //Cria a struct do menu 
Input input; // Cria a struct das entradas do usuário


struct Game //Struct do jogo
{
    bool gameRunning = true; //Variável que indica se o jogo está rodando
    bool menuRunning = true; //Cuida do menu

    //Loop principal do jogo
    void mainLoop(Map map){
        
        menu.mainMenu(); //Chama a função para imprimir o menu

        while (menuRunning){
            config.setCursor(0, 0); //Chama a função dentro da struct config, que configura o cursor
            switch (input.inputMenuOptions())
            {
            case '1':
                newGame(map);//Começa um novo jogo
                break;
            case '2':
                //Continua um jogo existente
                break;
            case '3':
                menu.sobreMenu();
                break;
            case '4':
                menuRunning = false; //Termina o jogo
                break;
            case '0':
                menu.mainMenu();
                break;
            default:
                break;
            }
        }
    }

    //Função que inicia um novo jogo
    void newGame(Map map){
        gameRunning = true;
        map.loadMap();
        gameLoop(map); //Chama o loop do jogo
    }

    //Funcão do loop do jogo
    void gameLoop(Map map){
        system("cls");

        while (gameRunning)
        {
            config.setCursor(0, 0); //Chama a função dentro da struct config, que configura o cursor
            map.printMap(); //Chama a função para imprimir o mapa
            input.moviments(map.gameMap, gameRunning, map, menu); //Chama função que verifica as entradas do usuário
            input.bombExplode(map.gameMap); //Chama a função que cuida da explosão da bomba
            gameLogic(map.gameMap); // Chama a função que cuida da lógica do jogo
        }
    }
    
    //Função que cuida da lógica do jogo
    void gameLogic(int **gameMap){
        pEnemy->enemyMoveCounter++;
        
        // condição de fim : matou todos os inimigos
        enemyHit(pEnemy->enemy1Alive, pEnemy->enemy1X, pEnemy->enemy1Y, gameMap);
        enemyHit(pEnemy->enemy2Alive, pEnemy->enemy2X, pEnemy->enemy2Y, gameMap);

        //Delay dos movimentos dos inimigos
        if (pEnemy->enemyMoveCounter == 50 ){
            input.enemyMoviments(gameMap, pEnemy->enemy1X, pEnemy->enemy1Y);
            input.enemyMoviments(gameMap, pEnemy->enemy2X, pEnemy->enemy2Y);
            pEnemy->enemyMoveCounter = 0;
        }

        if (gameMap[pPlayer->playerX][pPlayer->playerY] == 4) { // condição de fim : explodiu com a bomba
            gameRunning = false;
            menu.mainMenu();
        }
        if ((pPlayer->playerX == pEnemy->enemy1X && pPlayer->playerY == pEnemy->enemy1Y && pEnemy->enemy1Alive) || (pPlayer->playerX == pEnemy->enemy2X && pPlayer->playerY == pEnemy->enemy2Y && pEnemy->enemy2Alive)) {
            gameRunning = false; // o jogador colidiu com um inimigo
            menu.mainMenu();
        }

       

        if (pEnemy->enemy1Alive == false && pEnemy->enemy2Alive == false) {
            cout << "\nVOCÊ VENCEU!"; 
            gameRunning = false; // verifica se o jogador matou todos os inimigos
            menu.mainMenu();  
        }
    }

    void enemyHit(bool &enemyAlive, int &enemyX, int &enemyY, int **gameMap){
        if (gameMap[enemyX][enemyY] == 4) {
            enemyAlive = false;
        }
    }

};

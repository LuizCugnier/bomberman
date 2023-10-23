#include "menu.h"
#include "input.h"
#include "map.h"
#include "config.h"

using namespace std;


struct Game //Struct do jogo
{
    bool gameRunning = true; //Variável que indica se o jogo está rodando
    bool menuRunning = true; //Variável que indica se o jogo está rodando
    bool gameStarted = false; //Variável que indica se o jogo já começou

    //Loop principal do jogo
    void mainLoop(Config config, Map &map, Menu &menu, Input input){
        
        menu.mainMenu(); //Chama a função para imprimir o menu

        while (menuRunning){
            config.setCursor(0, 0); //Chama a função dentro da struct config, que configura o cursor
            switch (input.inputMenuOptions())
            {
            case '1':
                newGame(config, map, input, menu);//Começa um novo jogo
                break;
            case '2':
                continueGame(config, map, input, menu);//Continua um jogo existente
                break;
            case '3':
                menu.sobreMenu(); //Imprime o menu sobre
                break;
            case '4':
                map.deleteMap();
                menuRunning = false; //Termina o jogo
                menu.endGame(); //Imprime a mensagem de fim de jogo 
                break;
            case '0':
                menu.mainMenu(); //Volta para o menu principal
                break;
            default:
                break;
            }
        }
    }

    //Função que inicia um novo jogo
    void newGame(Config config, Map &map, Input input, Menu &menu){
        newGameSetup();
        map.loadMap("maps/map.txt");
        gameLoop(config, map, input, menu); //Chama o loop do jogo
    }

    void newGameSetup(){
        gameRunning = true;
        pEnemy->enemy1Alive = true;
        pEnemy->enemy2Alive = true;
        gameStarted = true;

    }

    void continueGame(Config config, Map &map, Input input, Menu &menu){
        if (gameStarted){
            gameRunning = true;
            map.loadMap("maps/continueMap.txt");
            gameLoop(config, map, input, menu); //Chama o loop do jogo
        } else {
            system("cls");
            menu.noGameFound(); //Imprime a mensagem de erro
            Sleep(1000);
            menu.mainMenu();
        }
    }

    //Funcão do loop do jogo
    void gameLoop(Config config, Map &map, Input input, Menu &menu){
        system("cls");

        while (gameRunning)
        {
            config.setCursor(0, 0); //Chama a função dentro da struct config, que configura o cursor
            map.printMap(map.gameMap); //Chama a função para imprimir o mapa
            input.moviments(map.gameMap, gameRunning, map, menu); //Chama função que verifica as entradas do usuário
            input.bombExplode(map.gameMap); //Chama a função que cuida da explosão da bomba
            gameLogic(menu, input, map.gameMap); // Chama a função que cuida da lógica do jogo
        }
    }
    
    //Função que cuida da lógica do jogo
    void gameLogic(Menu &menu, Input input, int **gameMap){
        pEnemy->enemyMoveCounter++;
        
        //Verifica se o enimigo foi atingido pela explosão
        enemyHit(pEnemy->enemy1Alive, pEnemy->enemy1X, pEnemy->enemy1Y, gameMap);
        enemyHit(pEnemy->enemy2Alive, pEnemy->enemy2X, pEnemy->enemy2Y, gameMap);

        //Delay dos movimentos dos inimigos
        if (pEnemy->enemyMoveCounter == 50 ){
            input.enemyMoviments(gameMap, pEnemy->enemy1X, pEnemy->enemy1Y);
            input.enemyMoviments(gameMap, pEnemy->enemy2X, pEnemy->enemy2Y);
            pEnemy->enemyMoveCounter = 0;
        }

        // condição de fim : explodiu com a bomba
        if (gameMap[pPlayer->playerX][pPlayer->playerY] == 4) { 
            gameRunning = false;
            menu.mainMenu();
        }
        // condição de fim : o jogador colidiu com um inimigo
        if ((pPlayer->playerX == pEnemy->enemy1X && pPlayer->playerY == pEnemy->enemy1Y && pEnemy->enemy1Alive) || (pPlayer->playerX == pEnemy->enemy2X && pPlayer->playerY == pEnemy->enemy2Y && pEnemy->enemy2Alive)) {
            gameRunning = false; 
            menu.mainMenu();
        }

       
        // condição de fim : verifica se o jogador matou todos os inimigos
        gameWin(menu);
    }

    void gameWin(Menu &menu){
        if (!pEnemy->enemy1Alive && !pEnemy->enemy2Alive) {
            gameRunning = false; 
            system("cls");    
            menu.gameWin();
            Sleep(1000); 
            menu.mainMenu();  
        }
    }

    void enemyHit(bool &enemyAlive, int &enemyX, int &enemyY, int **gameMap){
        if (gameMap[enemyX][enemyY] == 4) {
            enemyAlive = false;
        }
    }

};

#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <conio.h>

#include "map.h"

using namespace std;



struct Input //Struct para as entradas do usuário
{   
    clock_t startTime, endTime, totalTime, powerUpCollectTime, currentTime; //Declaração das entidades de contagem de tempo para armazenar inicio e fim do período da bomba
    char inputKey; //Variável para a entrada do usuário
    bool isGamePaused = false; // Adicione essa variável para rastrear o estado de pausa do jogo

    void collectPowerUp(int **gameMap){
        if (gameMap[pPlayer->playerX][pPlayer->playerY] == 5) {
            pPlayer->hasExplosionPowerUp = true;
            powerUpCollectTime = clock();
            gameMap[pPlayer->playerX][pPlayer->playerY] = 0;
        }
    }

    void explode(int **gameMap, int x, int y) {
        gameMap[x][y] = 4;
        if (pPlayer->hasExplosionPowerUp) {
            // Aumente o raio da explosão aqui
            spreadExplosion(gameMap, x, y, 2); // Raio maior (2 em vez de 1)
        } else {
            spreadExplosion(gameMap, x, y, 1); // Raio normal
        }
    }

    void removeExplosion(int **gameMap, int x, int y) {
        gameMap[x][y] = 0;
        if (pPlayer->hasExplosionPowerUp) {
            // Remova a explosão expandida
            removeSpreadExplosion(gameMap, x, y, 2); // Raio maior
        } else {
            removeSpreadExplosion(gameMap, x, y, 1); // Raio normal
        }
        bomb.flagBomb = false;
    }

    void checkPowerUpExpiration() {
        if (pPlayer->hasExplosionPowerUp && !isGamePaused) {
            currentTime = clock();
            double elapsedTime = (double)(currentTime - powerUpCollectTime) / CLOCKS_PER_SEC;
            cout << "PowerUp Timer =" << elapsedTime << endl;
            cout << currentTime << powerUpCollectTime;	
            if (elapsedTime >= 20.0) { // Se passaram 15 segundos
                pPlayer->hasExplosionPowerUp = false; // Redefina o poder coletado  
                elapsedTime = 0; // Redefina o tempo decorrido
            }
        }
    }

    void spreadExplosion(int **gameMap, int x, int y, int radius) {
        // Espalhe verticalmente
        for (int i = 1; i <= radius; i++) {
            if (gameMap[x - i][y] == 0 || gameMap[x - i][y] == 2) {
                gameMap[x - i][y] = 4;
            }
            if (gameMap[x + i][y] == 0 || gameMap[x + i][y] == 2) {
                gameMap[x + i][y] = 4;
            }
        }

        // Espalhe horizontalmente
        for (int i = 1; i <= radius; i++) {
            if (gameMap[x][y - i] == 0 || gameMap[x][y - i] == 2) {
                gameMap[x][y - i] = 4;
            }
            if (gameMap[x][y + i] == 0 || gameMap[x][y + i] == 2) {
                gameMap[x][y + i] = 4;
            }
        }
    }

    void removeSpreadExplosion(int **gameMap, int x, int y, int radius) {
        // Remova a explosão verticalmente
        for (int i = 1; i <= radius; i++) {
            if (gameMap[x - i][y] == 4) {
                gameMap[x - i][y] = 0;
            }
            if (gameMap[x + i][y] == 4) {
                gameMap[x + i][y] = 0;
            }
        }

        // Remova a explosão horizontalmente
        for (int i = 1; i <= radius; i++) {
            if (gameMap[x][y - i] == 4) {
                gameMap[x][y - i] = 0;
            }
            if (gameMap[x][y + i] == 4) {
                gameMap[x][y + i] = 0;
            }
        }
    }


    //Função que posiciona uma bomba no mapa
    void placeBomb(int **gameMap, int x, int y, bool *flagbomb){
        //cout << "teste";
        if (!*flagbomb && !isGamePaused){
            //cout << "teste1";
            *flagbomb = true;
            gameMap[x][y] = 3;
            startTime = clock();
            pBomb->bombX = pPlayer->playerX;
            pBomb->bombY = pPlayer->playerY;
            
        }

        pBomb->bombCount++;
    }

    //Função que cuida da logica de explosão da bomba
    void bombExplode(int **gameMap, bool &gameRunning){
        if (bomb.flagBomb && gameRunning && !isGamePaused) {
            endTime = clock();
            totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
            cout << totalTime;
            if (totalTime == 3) {
                explode(gameMap, pBomb->bombX, pBomb->bombY);
            }

            if (totalTime == 4) {
                removeExplosion(gameMap, pBomb->bombX, pBomb->bombY);
                totalTime = 0;
            }
        }
    }

    //Função para verificar colisões no mapa
    bool enemyCollisionCheck(int **gameMap, int x, int y) {
        if (gameMap[x][y] == 0 || gameMap[x][y] == 4) {
            return true;
        } else {
            return false;
        }
    }

    bool playerCollisionCheck(int **gameMap, int x, int y) {
        if (gameMap[x][y] == 0 || gameMap[x][y] == 4 || gameMap[x][y] == 5) {
            return true;
        } else {
            return false;
        }
    }

    //Função para os movimentos dos inimigos
    void enemyMoviments(int **gameMap, int &enemyX, int &enemyY) {
        int dir = rand() % 4; // escolhe uma direção aleatória
        
        if (dir == 0 && enemyCollisionCheck(gameMap, enemyX - 1, enemyY)) {
            enemyX--;
        } else if (dir == 1 && enemyCollisionCheck(gameMap, enemyX + 1, enemyY)) {
            enemyX++;
        } else if (dir == 2 && enemyCollisionCheck(gameMap, enemyX, enemyY - 1)) {
            enemyY--;
        } else if (dir == 3 && enemyCollisionCheck(gameMap, enemyX, enemyY + 1)) {
            enemyY++;
        } 
    }
    
    void pauseGame(Map map, Menu menu, bool &gameRunning){
        isGamePaused = true; // Defina o jogo como pausado
        map.saveMap("maps/continueMap.txt");
        gameRunning = false; //Termina o jogo
        menu.mainMenu();
    }

    //Função que recebe as entradas do usuário e movimenta de acordo
    void moviments(int **gameMap, bool &gameRunning, Map map, Menu menu){
        if (_kbhit()){
            inputKey = _getch();

            switch(inputKey)
            {
                case 72: case 'w': ///cima
                    if (playerCollisionCheck(gameMap, pPlayer->playerX-1, pPlayer->playerY)){
                        pPlayer->playerX--;

                    }
                break;
                case 80: case 's': ///baixo
                    if (playerCollisionCheck(gameMap, pPlayer->playerX+1, pPlayer->playerY)){
                       pPlayer->playerX++;

                    }

                break;
                case 75:case 'a': ///esquerda
                    if (playerCollisionCheck(gameMap, pPlayer->playerX, pPlayer->playerY-1)){
                        pPlayer->playerY--;

                    }
                break;
                case 77: case 'd': ///direita
                    if (playerCollisionCheck(gameMap, pPlayer->playerX, pPlayer->playerY+1)) {
                      pPlayer->playerY++;

                    }
                break;

                case 32:
                    placeBomb(gameMap, pPlayer->playerX, pPlayer->playerY, &bomb.flagBomb);
                break;

                case '0':
                    pauseGame(map, menu, gameRunning);
                break;
            }
        }
    }

    char inputMenuOptions(){
        char inputMenu; //Opção do menu principal
        if (_kbhit()){
            inputMenu = _getch();  
        }
        return inputMenu;
    }

};
#endif
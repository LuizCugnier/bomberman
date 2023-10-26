#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <conio.h>

#include "map.h"

using namespace std;



struct Input //Struct para as entradas do usuário
{   
    clock_t startTime, endTime, totalTime; //Declaração das entidades de contagem de tempo para armazenar inicio e fim do período da bomba
    char inputKey; //Variável para a entrada do usuário
    bool isGamePaused = false; // Adicione essa variável para rastrear o estado de pausa do jogo

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
    }


    //Função que cuida da logica de explosão da bomba
    void bombExplode(int **gameMap, bool &gameRunning){
        if (bomb.flagBomb && gameRunning && !isGamePaused) {
            endTime = clock();
            totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
            cout << totalTime;
            if ( totalTime == 3) {
                gameMap[pBomb->bombX][pBomb->bombY] = 4;
                if (gameMap[pBomb->bombX+1][pBomb->bombY]==0 || gameMap[pBomb->bombX+1][pBomb->bombY]==2) gameMap[pBomb->bombX+1][pBomb->bombY] = 4;
                if (gameMap[pBomb->bombX-1][pBomb->bombY]==0 || gameMap[pBomb->bombX-1][pBomb->bombY]==2) gameMap[pBomb->bombX-1][pBomb->bombY] = 4;
                if (gameMap[pBomb->bombX][pBomb->bombY+1]==0 || gameMap[pBomb->bombX][pBomb->bombY+1]==2) gameMap[pBomb->bombX][pBomb->bombY+1] = 4;
                if (gameMap[pBomb->bombX][pBomb->bombY-1]==0 || gameMap[pBomb->bombX][pBomb->bombY-1]==2) gameMap[pBomb->bombX][pBomb->bombY-1] = 4;
            }

            if (totalTime == 4) {
                gameMap[pBomb->bombX][pBomb->bombY] = 0;
                if (gameMap[pBomb->bombX+1][pBomb->bombY]!=1) gameMap[pBomb->bombX+1][pBomb->bombY] = 0;
                if (gameMap[pBomb->bombX-1][pBomb->bombY]!=1) gameMap[pBomb->bombX-1][pBomb->bombY] = 0;
                if (gameMap[pBomb->bombX][pBomb->bombY+1]!=1) gameMap[pBomb->bombX][pBomb->bombY+1] = 0;
                if (gameMap[pBomb->bombX][pBomb->bombY-1]!=1) gameMap[pBomb->bombX][pBomb->bombY-1] = 0;
                bomb.flagBomb = false;
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
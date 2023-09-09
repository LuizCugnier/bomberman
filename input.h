#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <conio.h>

#include "map.h"

using namespace std;

clock_t inicio, fim; //declaração das entidades de contagem de tempo para armazenar inicio e fim do período da bomba

struct Input
{
    char inputKey;

    

    int menuChoise(){
        int inputKey;
        cin >> inputKey;
        return inputKey;
    }

    void placeBomb(int (&map)[15][15], int x, int y, bool *flagbomb){
        //cout << "teste";
        if (!*flagbomb){
            //cout << "teste1";
            *flagbomb = true;
            map[x][y] = 3;
        }
    }

    void bombExplode(int (&gameMap)[15][15]){
        if (bomb.flagBomb) {
            fim = clock();
            if ((fim-inicio)/CLOCKS_PER_SEC == 3) {
                gameMap[pBomb->bombX][pBomb->bombY] = 4;
                if (gameMap[pBomb->bombX+1][pBomb->bombY]==0 || gameMap[pBomb->bombX+1][pBomb->bombY]==2) gameMap[pBomb->bombX+1][pBomb->bombY] = 4;
                if (gameMap[pBomb->bombX-1][pBomb->bombY]==0 || gameMap[pBomb->bombX-1][pBomb->bombY]==2) gameMap[pBomb->bombX-1][pBomb->bombY] = 4;
                if (gameMap[pBomb->bombX][pBomb->bombY+1]==0 || gameMap[pBomb->bombX][pBomb->bombY+1]==2) gameMap[pBomb->bombX][pBomb->bombY+1] = 4;
                if (gameMap[pBomb->bombX][pBomb->bombY-1]==0 || gameMap[pBomb->bombX][pBomb->bombY-1]==2) gameMap[pBomb->bombX][pBomb->bombY-1] = 4;
            }

            if ((fim-inicio)/CLOCKS_PER_SEC == 4) {
                gameMap[pBomb->bombX][pBomb->bombY] = 0;
                if (gameMap[pBomb->bombX+1][pBomb->bombY]!=1) gameMap[pBomb->bombX+1][pBomb->bombY] = 0;
                if (gameMap[pBomb->bombX-1][pBomb->bombY]!=1) gameMap[pBomb->bombX-1][pBomb->bombY] = 0;
                if (gameMap[pBomb->bombX][pBomb->bombY+1]!=1) gameMap[pBomb->bombX][pBomb->bombY+1] = 0;
                if (gameMap[pBomb->bombX][pBomb->bombY-1]!=1) gameMap[pBomb->bombX][pBomb->bombY-1] = 0;
                bomb.flagBomb = false;
            }
        }
    }

    bool collisionCheck(int map[15][15], int x, int y) {
        if (map[x][y] == 0 || map[x][y] == 4) {
            return true;
        } else {
            return false;
        }
    }

    void enemyMoviments(int m[15][15], int &enemyX, int &enemyY) {
        int dir = rand() % 4; // escolhe uma direção aleatória
        int passo = rand() % 3 + 1; // escolhe um número aleatório de passos
        
        for (int i = 0; i < passo; i++) {
            if (dir == 0 && collisionCheck(m, enemyX - 1, enemyY)) {
                enemyX--;
            } else if (dir == 1 && collisionCheck(m, enemyX + 1, enemyY)) {
                enemyX++;
            } else if (dir == 2 && collisionCheck(m, enemyX, enemyY - 1)) {
                enemyY--;
            } else if (dir == 3 && collisionCheck(m, enemyX, enemyY + 1)) {
                enemyY++;
            } else {
                break;
            }
        }
    }

    

    void moviments(int (&gameMap)[15][15], bool &gameRunning){
        if (_kbhit()){
            inputKey = _getch();

            switch(inputKey)
            {
                case 72: case 'w': ///cima
                    if (collisionCheck(gameMap, pPlayer->playerX-1, pPlayer->playerY)){
                        pPlayer->playerX--;

                    }
                break;
                case 80: case 's': ///baixo
                    if (collisionCheck(gameMap, pPlayer->playerX+1, pPlayer->playerY)){
                       pPlayer->playerX++;

                    }

                break;
                case 75:case 'a': ///esquerda
                    if (collisionCheck(gameMap, pPlayer->playerX, pPlayer->playerY-1)){
                        pPlayer->playerY--;

                    }
                break;
                case 77: case 'd': ///direita
                    if (collisionCheck(gameMap, pPlayer->playerX, pPlayer->playerY+1)) {
                      pPlayer->playerY++;

                    }
                break;

                case 32:
                    //coloca bomba
                    if (!bomb.flagBomb){
                        inicio = clock();
                        pBomb->bombX = pPlayer->playerX;
                        pBomb->bombY = pPlayer->playerY;
                    }
                    placeBomb(gameMap, pPlayer->playerX, pPlayer->playerY, &bomb.flagBomb);
                break;

                case '0':
                    gameRunning = false;
                break;
            }
        }
    }
};
#endif
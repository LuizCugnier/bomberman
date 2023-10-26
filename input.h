#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <conio.h>

#include "map.h"

using namespace std;

clock_t inicio, fim; //Declaração das entidades de contagem de tempo para armazenar inicio e fim do período da bomba

struct Input //Struct para as entradas do usuário
{
    char inputKey; //Variável para a entrada do usuário

    //Função que posiciona uma bomba no mapa
    void placeBomb(int **gameMap, int x, int y, bool *flagbomb){
        //cout << "teste";
        if (!*flagbomb){
            //cout << "teste1";
            *flagbomb = true;
            gameMap[x][y] = 3;
            inicio = clock();
            pBomb->bombX = pPlayer->playerX;
            pBomb->bombY = pPlayer->playerY;
        }
    }


    //Função que cuida da logica de explosão da bomba
    void bombExplode(int **gameMap){
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

    //Função para verificar colisões no mapa
    bool collisionCheck(int **gameMap, int x, int y) {
        if (gameMap[x][y] == 0 || gameMap[x][y] == 4) {
            return true;
        } else {
            return false;
        }
    }

    //Função para os movimentos dos inimigos
    void enemyMoviments(int **gameMap, int &enemyX, int &enemyY) {
        int dir = rand() % 4; // escolhe uma direção aleatória
        
        if (dir == 0 && collisionCheck(gameMap, enemyX - 1, enemyY)) {
            enemyX--;
        } else if (dir == 1 && collisionCheck(gameMap, enemyX + 1, enemyY)) {
            enemyX++;
        } else if (dir == 2 && collisionCheck(gameMap, enemyX, enemyY - 1)) {
            enemyY--;
        } else if (dir == 3 && collisionCheck(gameMap, enemyX, enemyY + 1)) {
            enemyY++;
        } 
    }
    

    //Função que recebe as entradas do usuário e movimenta de acordo
    void moviments(int **gameMap, bool &gameRunning, Map map, Menu menu){
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
                    placeBomb(gameMap, pPlayer->playerX, pPlayer->playerY, &bomb.flagBomb);
                break;

                case '0':
                    map.saveMap("maps/continueMap.txt");
                    gameRunning = false; //Termina o jogo
                    menu.mainMenu();
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
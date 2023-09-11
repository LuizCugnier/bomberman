#ifndef MAP_H
#define MAP_H


#include "entities.h"

using namespace std;

Player player;
Player* pPlayer = &player;
Enemy enemy;
Enemy * pEnemy = &enemy;
Bomb bomb;
Bomb* pBomb = &bomb;

struct Map
{
    int mapX = 15;
    int mapY = 15;

    

    void printMap(int (&map)[15][15]){
        for(int i=0;i<mapX;i++){
            for(int j=0;j<mapY;j++){
                if(i==pPlayer->playerX && j==pPlayer->playerY){
                    cout<<char(2); //personagem
                } else if (i == pEnemy->enemy1X && j == pEnemy->enemy1Y) {
                    cout<<char(5); // primeiro inimigo
                } else if (i == pEnemy->enemy2X && j == pEnemy->enemy2Y) {
                    cout<<char(6); // segundo inimigo
                } else {
                    switch (map[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<"#"; break; //parede quebrável
                        case 3: cout<<char(207); break; //bomba
                        case 4: cout<<"*"; break; //explosão da bomba
                        //default: cout<<"-"; //erro
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa
        cout << "Aperte '0' para sair\n";
    }
};
#endif
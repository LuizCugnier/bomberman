#ifndef MAP_H
#define MAP_H


#include "entities.h"

#include <fstream>

using namespace std;

Player player; //Cria a struct do jogador
Player* pPlayer = &player; //Cria um ponteiro para o jogador
Enemy enemy; //Cria a struct do inimigo
Enemy * pEnemy = &enemy; //Cria um ponteiro para o inimigo
Bomb bomb; //Cria a struct da bomba
Bomb* pBomb = &bomb; //Cria um ponteiro para a bomba


struct Map
{   
    //Variáveis para guardar o tamanho do mapa
    int mapX, mapY;
    int **gameMap;

    void createMap(){
        gameMap = new int*[mapX];

        for (int i=0; i < mapX; i++){
            gameMap[i] = new int[mapY];
        }
    }

    void deleteMap(){
        for(int i = 0; i < mapX; i++){
            delete gameMap[i];
        }
        delete gameMap;
    }

    //Função para carregar o mapa
    void loadMap(){
        string mapFile = "map.txt";
        ifstream file;

        file.open(mapFile);

        if (file.is_open()){
            file >> mapX >> mapY;
            file >> pPlayer->playerX >> pPlayer->playerY;
            file >> pEnemy->enemy1X >> pEnemy->enemy1Y;
            file >> pEnemy->enemy2X >> pEnemy->enemy2Y;

            createMap();

            for (int i = 0; i < mapX; i++){
                for (int j = 0;j < mapY; j++){
                    char c;
                    file >> c;
                    gameMap[i][j] = (int)c - 48;

                }
            }
            file.close();
        } else {
            cout << "Erro ao carregar";
        }   
        
    }
    
    //Função que imprime o mapa no jogo
    void printMap(){
        for(int i=0;i<mapX;i++){
            for(int j=0;j<mapY;j++){
                if(i==pPlayer->playerX && j==pPlayer->playerY){
                    cout<<char(2); //personagem
                } else if (i == pEnemy->enemy1X && j == pEnemy->enemy1Y && pEnemy->enemy1Alive) {
                    cout<<char(5); // primeiro inimigo
                } else if (i == pEnemy->enemy2X && j == pEnemy->enemy2Y && pEnemy->enemy2Alive) {
                    cout<<char(6); // segundo inimigo
                } else {
                    switch (gameMap[i][j]){
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
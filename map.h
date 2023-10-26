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

    //Cria e reserva o espaço necessário na memória para o mapa
    void createMap(){
        gameMap = new int*[mapX];

        for (int i=0; i < mapX; i++){
            gameMap[i] = new int[mapY];
        }
    }

    //Deleta o a memória alocada
    void deleteMap(){
        for(int i = 0; i < mapX; i++){
            delete gameMap[i];
        }
        delete gameMap;
    }

    //Seleciona um mapa 
    string selectMap(Menu menu){
        int randomMap = rand() % 3 + 1;
        int mapChoice;
        
        menu.mapChoice(mapChoice);

        if (mapChoice == 4) {
            mapChoice = randomMap;
        }

        switch (mapChoice)
        {
        case 1:
            return "maps/map.txt";
            break;
        case 2:
            return "maps/map2.txt";
            break;
        case 3:
            return "maps/map3.txt"; 
            break;
        default:
            break;
        }
    }

    //Salva o mapa num arquivo separado ao voltar pro menu
    void saveMap(string mapFile){
        ofstream file;

        file.open(mapFile); //Abre o arquivo

        if (file.is_open()){ //Verifica se o arquivo está aberto
            file << mapX << " " << mapY << "\n";                            //Salva o tamanho do mapa
            file << pPlayer->playerX << " " << pPlayer->playerY << "\n";    //Salva a posição do jogador
            file << pEnemy->enemy1X << " " << pEnemy->enemy1Y << "\n";      //Salva a posição do inimigo um
            file << pEnemy->enemy2X << " " << pEnemy->enemy2Y << "\n";      //Salva a posição do inimigo dois

            //Salva o mapa 
            for (int i = 0; i < mapX; i++){
                for (int j = 0;j < mapY; j++){
                    file << gameMap[i][j];
                }
                file << "\n";
            }
            file.close();
        } else {
            cout << "Erro ao salvar";
        }
    }

    //Função para carregar o mapa
    void loadMap(string mapFile){
        
        ifstream file;

        file.open(mapFile); //Abre o arquivo

        if (file.is_open()){ //Verifica se o arquivo está aberto
            file >> mapX >> mapY;                           //Carrega o tamanho do mapa
            file >> pPlayer->playerX >> pPlayer->playerY;   //Carrega a posição do jogador
            file >> pEnemy->enemy1X >> pEnemy->enemy1Y;     //Carrega a posição do inimigo um
            file >> pEnemy->enemy2X >> pEnemy->enemy2Y;     //Carrega a posição do inimigo dois

            createMap(); //Chama a função que cria o mapa 

            //Carrega o mapa na matriz criada
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
    void printMap(int **gameMap){
        for(int i=0;i<mapX;i++){
            for(int j=0;j<mapY;j++){
                if(i==pPlayer->playerX && j==pPlayer->playerY){
                    cout<<char(2); //personagem
                } else if (i == pEnemy->enemy1X && j == pEnemy->enemy1Y && pEnemy->enemy1Alive) {
                    cout<<char(5); // primeiro inimigo
                } else if (i == pEnemy->enemy2X && j == pEnemy->enemy2Y && pEnemy->enemy2Alive) {
                    cout<<char(6); // segundo inimigo
                } else {
                    //cout << "teste";
                    switch (gameMap[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<"#"; break; //parede quebrável
                        case 3: cout<<char(207); break; //bomba
                        case 4: cout<<"*"; break; //explosão da bomba
                        case 5: cout<<char(224); break; // coletável aumento de explosão
                        //default: cout<<"-"; //erro
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa
        cout << "Aperte '0' para sair\n";
        cout << "Numero de bombas: " << pBomb->bombCount;
    }
};
#endif
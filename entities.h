#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <Windows.h>

struct Player //Struct para o jogador
{
    //Posição inicial donjogador
    int playerX, playerY;


};

struct Enemy //Struct para o inimigo
{
    //Posição inicial dos inimigos
    int enemy1X, enemy1Y;
    int enemy2X, enemy2Y;

    bool enemy1Alive = true;
    bool enemy2Alive = true;

    int enemyMoveCounter; //Variável para contar os movimentos do inimigo
};

struct Bomb //Struct para a bomba
{
    bool flagBomb = false; //Variável para verificar se já existe bomba
    int bombX, bombY; //localização da bomba
    clock_t savedEndTime, savedStartTime; //Variáveis para armazenar o tempo da bomba
    bool powerUpFlag = false; //Variável para verificar se já existe power up   
};






#endif
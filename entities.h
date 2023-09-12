#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <Windows.h>

struct Player //Struct para o jogador
{
    //Posição inicial donjogador
    int playerX = 1; 
    int playerY = 2;


};

struct Enemy //Struct para o inimigo
{
    //Posição inicial dos inimigos
    int enemy1X = 1, enemy1Y = 1;
    int enemy2X = 13, enemy2Y = 13;

    int enemyMoveCounter; //Variável para contar os movimentos do inimigo
};

struct Bomb //Struct para a bomba
{
    bool flagBomb = false; //Variável para verificar se já existe bomba
    int bombX, bombY; //localização da bomba
};



#endif
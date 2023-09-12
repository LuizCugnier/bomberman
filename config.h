#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct Config //Struct para guardar as configurações do jogo
{
    //Função que configura o display do jogo e retorna a posição do cursor
    bool setCursor(int x, int y){
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; 
        SetConsoleCursorInfo(out, &cursorInfo);
        
        COORD coord;
        coord.X = x;
        coord.Y = y;
        return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

   
};

#endif
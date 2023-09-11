#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <Windows.h>

using namespace std;

struct Menu
{
    void mainMenu(){
    system("cls");
    cout << "=======================\n";
    cout << "     BOMBERMAN\n";
    cout << "=======================\n";
    cout << "[1] Novo Jogo\n";
    cout << "[2] Continua\n";
    cout << "[3] Sobre\n";
    cout << "[4] Sair\n";


}
};
#endif
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "player.h"
#include "input.h"
#include "map.h"
#include "menu.h"
#include "game.h"
#include "loop.h"



using namespace std;

int main(){
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    //IN�CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.

    Loop loop;
    Player player;
    Player* pointerPlayer = &player;
    Menu menu;
    Input input;
    Map map;
    Game game;

    menu.imprime_menu();
    loop.mainLoop(coord, menu, input, pointerPlayer, map, game);



    return 0;
}
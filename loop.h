using namespace std;

struct Loop {
    
    void mainLoop(COORD coord, Menu menu, Input input, Player* player, Map map, Game game){

        while(menu.mainLoop){
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            if (_kbhit()){
                input.key = _getch();

                switch (input.key)
                {
                case '1':
                    //começa novo jogo
                    game.newGame(map, player);
                    break;
                case '2':
                    //continua um jogo
                    break;
                case '3':
                    //mostra informações do jogo
                    break;
                case '4':
                    system("cls");
                    cout << "FIM DE JOGO!!!\n";
                    Sleep(2000);
                    menu.mainLoop = false;
                    break;
                default:
                    system("cls");
                    cout << "Tecla invalida";
                    Sleep(500);
                    menu.imprime_menu();
                    break;
                }
            }
        }
    }
};
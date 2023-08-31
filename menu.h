using namespace std;

struct Menu{
    bool mainLoop = true;
    
    void imprime_menu(){
        system("cls");
        cout << "============\n";
        cout << " BOMBERMAN\n";
        cout << "============\n";    
        cout << "[1] Novo Jogo\n";
        cout << "[2] Continuar\n";
        cout << "[3] Sobre\n";
        cout << "[4] Fim\n";
    }
};

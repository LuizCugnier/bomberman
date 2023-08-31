using namespace std;

struct Map{
    int mX, mY = 13;
    int mj[13][13] = {  1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,1,0,0,4,0,0,1,1,0,1,
                        1,0,0,1,0,0,0,0,0,0,1,0,1,
                        1,0,0,1,0,0,0,0,0,1,1,0,1,
                        1,0,0,1,0,0,0,0,0,0,0,0,1,
                        1,0,0,1,1,1,0,0,1,1,1,0,1,
                        1,0,0,0,0,0,0,0,0,0,1,0,1,
                        1,0,0,0,0,0,0,0,0,0,1,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1 };

    void printMap(Player* player){

        for (int i = 0; i < mX; i++) {
            for (int j = 0; j < mY; j++) {
                if (i == player->pX && j == player->pY) {
                    cout << char(2); //personagem
                    cout << "teste";
                }
                
                else {
                    switch (mj[i][j]) {
                    case 0: cout << " "; break; //caminho
                    case 1: cout << char(219); break; //parede
                    case 2: cout << " "; break; //espa�o vazio de fora
                    case 3: cout << "."; break; //ponto final
                    case 4: cout << "#"; break; //caixa
                        default: cout<<"-"; //erro
                    } //fim switch

                }
            
        }
        cout << "\n";
    } //fim for mapa[

    cout << "\nAperte '0' para voltar";
    }

    void testeMapa(){
        for(int i=0; i<mX; i++){
            for(int j=0; j<mY; j++){
                switch (mj[i][j]) {
                    case 0: cout << " "; break; //caminho
                    case 1: cout << char(219); break; //parede
                    case 2: cout << " "; break; //espa�o vazio de fora
                    case 3: cout << "."; break; //ponto final
                    case 4: cout << "#"; break; //caixa
                        default: cout<<"-"; //erro
                    } //fim switc
            }
        }
    }
};

#include <iostream>
#include "MatrizAdjacencia.h"

using namespace std;

int main(){
    Digrafo* grafo = inicializarDigrafo(6);

    inserirArco(grafo,0,2);
    inserirArco(grafo,0,3);
    inserirArco(grafo,0,4);
    inserirArco(grafo,2,1);
    inserirArco(grafo,2,4);
    inserirArco(grafo,3,4);
    inserirArco(grafo,3,5);
    inserirArco(grafo,4,1);
    inserirArco(grafo,4,5);
    inserirArco(grafo,5,1);

    /*int n, s, t;
    cout << "Digite o numero de testes: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Digite os vertices a serem testados: ";
        cin >> s >> t;
        if(existeCaminho(grafo,s,t)){
            cout << "Existe caminho!" << endl;
        }else{
            cout << "Nao existe caminho!" << endl;
        }
        if(existeCaminho2(grafo,s,t)){
            cout << "Existe caminho2!" << endl;
        }else{
            cout << "Nao existe caminho2!" << endl;
        }
        
    }*/
    if(existeCaminhoIterativo(grafo,0,5))
        cout << "existe caminho iterativo funcionando!" << endl;

    return 0;
}
#include <iostream>
#include "MatrizAdjacencia.h"

using namespace std;

static int lbl[maxV]; //label (rotulo) - marca os vertices como -1 se nao visitado e 0 como visitado
static int parnt[maxV]; //vetor de pais - parnt[w] eh o pai de w

//A funcao alocarArco recebe dois vertices v e w e devolve um arco com ponta inicial v e ponta final w
Arco* alocarArco(Vertex v, Vertex w){
    Arco* arco = (Arco*) malloc(sizeof(Arco));
    arco->v = v;
    arco->w = w;

    return arco;
}

/*--------------------------------------------------------
-------------------------GRAFOS---------------------------
--------------------------------------------------------*/
//Um grafo eh um digrafo simetrico
//Uma aresta eh um par de arcos anti-paralelos


/*--------------------------------------------------------
------------------MATRIZ DE ADJACENCIA--------------------
--------------------------------------------------------*/

/*
Matriz de adjacencia de um DIGRAFO tem linhas e colunas indexadas por vertices
    adj[v][w] = 1   se v-w eh um arco
    adj[v][w] = 0   caso contrario
*/

/*
Matriz de adjacencia de um GRAFO tem linhas e colunas indexadas por vertices
    adj[v][w] = 1   se v-w eh uma aresta
    adj[v][w] = 0   caso contrario
*/

//Consumo de espaco de uma matriz de adjacencia: Theta(V^2)

//Aloca uma matriz com r-1 linhas e c-1 colunas
int** alocarMatriz(int r, int c, int val){ // r - linhas / c - colunas
    Vertex i, j;
    int** m = (int**) malloc(sizeof(int*)*r);

    for(i = 0; i < r; i++){
        m[i] = (int*) malloc(sizeof(int)*c); 
    }

    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++){
            m[i][j] = val;
        }
    }

    return m;
}

//Devolve o endereco de um novo digrafo com v vertices e nenhum arco
Digrafo* inicializarDigrafo(int V){
    Digrafo* g = (Digrafo*) malloc(sizeof(Digrafo));
    g->V = V;
    g->A = 0;
    g->adj = alocarMatriz(V,V,0);

    return g;
}

//Insere um arco v-w no digrafo g
void inserirArco(Digrafo* g, Vertex v, Vertex w){
    if(v == w || g->adj[v][w] == 1) return; //nao permite laços

    g->adj[v][w] = 1;
    g->A++;
}

//Remove do digrafo g o arco v-w
void removerArco(Digrafo* g, Vertex v, Vertex w){
    if(g->adj[v][w] != 1) return;

    g->adj[v][w] = 0;
    g->A--;
}

//Para cada vertice v de g, imprime, em uma linha, os vertices adjacentes a v
void exibirDigrafo(Digrafo* g){
    Vertex v, w;
    for(v = 0; v < g->V; v++){
        printf("%2d:",v);
        for(w = 0; w < g->V; w++){
            if(g->adj[v][w] == 1)
                printf("%2d", w);
        }
        printf("\n");
    }
}

//Funcao que insere uma aresta v-w no grafo g
void inserirAresta(Digrafo* g, Vertex v, Vertex w){
    inserirArco(g,v,w);
    inserirArco(g,w,v);
}

//Funcao que remove uma aresta v-w no grafo g
void removerAresta(Digrafo* g, Vertex v, Vertex w){
    removerArco(g,v,w);
    removerArco(g,w,v);
}

/*--------------------------------------------------------
--------------------CAMINHOS EM DIGRAFOS------------------
--------------------------------------------------------*/
/*
Um caminho num digrafo eh qualquer sequencia da forma v0--v1--v2-...--vk-1-vp, onde vk-1--vk eh um arco para k = 1,...,p
Um caminho eh simples se nao ha vertices repetidos
*/

//(Funcao auxiliar) Visita todos os vertices que podem ser atingidos a partir de v
void caminhoRecursivo(Digrafo* g, Vertex v){
    Vertex w;
    lbl[v] = 0;
    for(w = 0; w < g->V; w++){
        if(g->adj[v][w]){
            if(lbl[w] == -1){
                caminhoRecursivo(g,w);
            }
        }
    }
} //O(v^2)

//Dado um digrafo g, verifica se existe um caminho entre os vertices s e t
bool existeCaminho(Digrafo* g, Vertex s, Vertex t){
    Vertex v;
    for(v = 0; v < g->V; v++){
        lbl[v] = -1;
    }

    caminhoRecursivo(g,s);
    if(lbl[t] == -1) return false;
    return true;
} //O(v^2)

//(Funcao auxiliar) Dado um digrafo g, verifica se existe um caminho entre os vertices v e t
bool caminhoRecursivo2(Digrafo* g, Vertex v, Vertex t){
    Vertex w;
    lbl[v] = 0;

    if(v == t) return true;
    for(w = 0; w < g->V; w++){
        if(g->adj[v][w] == 1 && lbl[w] == -1){
            if(caminhoRecursivo2(g,w,t)) 
                return true;
        }
    }
    return false;
} //Esse metodo para assim que encontra t

//Dado um digrafo g, verifica se existe um caminho entre os vertices s e t
bool existeCaminho2(Digrafo* g, Vertex s, Vertex t){
    Vertex v;

    for(v = 0; v < g->V; v++){
        lbl[v] = -1;
    }
    return caminhoRecursivo2(g,s,t);
}

//Dado um digrafo g, verifica se existe um caminho entre os vertices s e t (Versao iterativa)
bool existeCaminhoIterativo(Digrafo* g, Vertex s, Vertex t){
    Vertex v, w;
    Vertex caminho[maxV];
    int k;

    for(v = 0; v < g->V; v++){
        lbl[v] = -1;
    }
    lbl[s] = 0;
    caminho[0] = s;

    k = 1;
    v = s; 
    w = 0;

    while(k != 1 || w != g->V){
        if(w == g->V){
            w = v+1; 
            k--;
            v = caminho[k-1];
        } else if(g->adj[v][w] == 1 && lbl[w] == -1){
            lbl[w] = 0; 
            caminho[k++] = w;
            v = w; 
            w = 0;
        } else{
            w++;
        }
    }


    cout << "lbl: " << endl;
    for(int j = 0; j < g->V; j++){
        cout << lbl[j] << " ";
    }
    cout << endl;

    if(lbl[t] == -1) return false;
    return true;
}

//Certificado de inexistencia do caminho S a T
bool st_corte(Digrafo* g, Vertex s, Vertex t){
    Vertex v, w;
    if(lbl[s] == -1 || lbl[t] == 0)
        return false;

    for(v = 0; v < g->V; v++){
        for(w = 0; w < g->V; w++){
            if(g->adj[v][w] == 1 && (lbl[v] == 0 && lbl[w] == -1)) //nao deveria ser lbl[w] == 0?
                return false;
        }
    }
    return true;
} //O(v^2)
//A funcao devolve verdadeiro se nao existe caminho


//Caminho de uma arborescencia que leva da raiz a um vertice v (Resultado inverso)
void caminhoRaizAteV(Digrafo* g, Vertex v){
    Vertex x;
    caminhoDigrafo(g,0,v);
    printf("Caminho de %d ate 0:\n", v);
    for(x = v; parnt[x] != x; x = parnt[x])
        printf("%d-", x);
    printf("%d\n", x);

    printf("Caminho de 0 ate %d:\n", v);
    /*
        implementar uma pilha
    */

}

//Percorre o digrafo criando a arborescencia
bool caminhoDigrafo(Digrafo* g, Vertex s, Vertex t){
    Vertex v;

    for(v = 0; v < g->V; v++){
        lbl[v] = -1;
        parnt[v] = -1;
    }
    parnt[s] = s;
    caminhoArborescencia(g,s);

    if(lbl[t] == -1)
        return false;
    return true;
}
//(Funcao auxiliar) Visita todos os vertices que podem ser atingidos a partir de v
void caminhoArborescencia(Digrafo* g, Vertex v){
    Vertex w;
    lbl[v] = 0;

    for(w = 0; w < g->V; w++){
        if(g->adj[v][w] == 1){
            if(lbl[w] == -1){
                parnt[w] = v;
                caminhoArborescencia(g,w);
            }
        }
    }
}

//Certificado de existencia do caminho de s a t
bool st_caminho(Digrafo* g, Vertex s, Vertex t){
    Vertex v, w;
    if(parnt[t] == -1)
        return false;

    for(w = t; w != parnt[w]; w = v){
        v = parnt[w];
        if(g->adj[v][w] != 1)
            return false;
    }

    if(w != s)
        return false;
    return true;
}//O(V)

//Certificado de existencia do ciclo (passando pelo mesmo vertice mais de uma vez)
bool certificadoCiclo(Digrafo* g, Vertex v, Vertex w){
    if(g->adj[v][w] == 0)
        return false;
    if(!st_caminho(g,v,w))
        return false;
    return true;
}
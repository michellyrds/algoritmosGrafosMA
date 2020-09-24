#define Vertex int
#define maxV 20

typedef struct Arco{
    Vertex v; //ponta inicial
    Vertex w; //ponta final
} Arco; // Um arco eh um par ordenado de vertices
//Dois arcos sao anti-paralelos se a ponta inicial de um eh ponta final de outro

 typedef struct Digrafo{
    int V; //numero de vertices
    int A; //numero de arestas - Numero de aresta de um grafo g: (g->A)/2
    int** adj; //ponteiro para a matrix de adjacencia
} Digrafo;

Arco* alocarArco(Vertex v, Vertex w);
int** alocarMatriz(int r, int c, int val);
Digrafo* inicializarDigrafo(int V);
void inserirArco(Digrafo* g, Vertex v, Vertex w);
void removerArco(Digrafo* g, Vertex v, Vertex w);
void exibirDigrafo(Digrafo* g);
void inserirAresta(Digrafo* g, Vertex v, Vertex w);
void removerAresta(Digrafo* g, Vertex v, Vertex w);
void caminhoRecursivo(Digrafo* g, Vertex v);
bool existeCaminho(Digrafo* g, Vertex s, Vertex t);
bool caminhoRecursivo2(Digrafo* g, Vertex v, Vertex t);
bool existeCaminho2(Digrafo* g, Vertex v, Vertex t);
bool existeCaminhoIterativo(Digrafo* g, Vertex s, Vertex t);
bool st_corte(Digrafo* g, Vertex s, Vertex t);
void caminhoRaizAteV(Digrafo* g, Vertex v);
bool caminhoDigrafo(Digrafo* g, Vertex s, Vertex t);
void caminhoArborescencia(Digrafo* g, Vertex v);
bool st_caminho(Digrafo* g, Vertex s, Vertex t);
bool certificadoCiclo(Digrafo* g, Vertex v, Vertex w);

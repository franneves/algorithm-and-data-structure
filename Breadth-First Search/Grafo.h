//Biblioteca criada para auxiliar a resoluçao do problema TP0 - Hit do verao

//renomeando a estrtura princiapl, struct grafo
typedef struct grafo Grafo;

//criar o grafo
Grafo* criar(int nvert);
//inserir idades
int insereIdade(Grafo* gr, int nvert);
//inserir uma aresta(ler a e b, chama addNode)
int insereAresta(Grafo* gr, int m);
//adicionar relacao entre a e b <-> b e a, na lista de adjacencia
void addEdge(Grafo* gr, int src, int dest);
//funcao base para calcular quantas pessoas gostaram da musica
int relacoes(Grafo *gr, int first, int nvert, int *ouviu);
//desalocar Grafo
int removergrafo(Grafo *gr, int n);

/*Universidade Federal de Minas Gerais
  Algoritmos e Estrutura de dados 03
  TP 03 - Biblioteca para criação e operaçoes em grafos - Tp3 ForçaBruta
  Francielly das Neves Lafaete - 2017023382*/
typedef struct grafo Grafo;


//Funçoes para manipulacao de grafos
Grafo* criaGrafo(int nvert);
void LerArestas(Grafo* gr, int m);
void criaAresta(Grafo* gr, int a, int b);
int removergrafo(Grafo *gr, int n);

//Funçoes para a resoluçao do problema
int valido(int n, int *vetor, Grafo *gr);
int procura_alocacao(Grafo* gr,int *vetor, int n, int index, int aux, int *max);
void salvaRespostas(Grafo* gr, int nvert, int max);

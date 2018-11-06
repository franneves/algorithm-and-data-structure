#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

struct Node {
    int id;
    struct Node* next;
};

struct List {
    struct Node *head; //ponteiro para o primeiro no da lista.
};

//funcao que cria um novo no
struct Node* newNode(int id) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

//definicao do tipo Grafo
struct grafo{
  int nvert; //numero de vertices do Grafo
  int* verificado;//auxiliar na busca, 1 se o numero ja foi analisado, 0 caso contrario
  int* idade;//numero de idades de cada ID, sendo o ID = indice vetor+1
  struct List* vetoradj;//vetor de adjacencias
};

//constroi um Grafo
Grafo* criar(int nvert){
  Grafo *gr;
  int i;
  gr = (Grafo*)malloc(sizeof(struct grafo));
  //tamnho de vertices do grafo
  gr->nvert = nvert;
  // controi um vetor de tamanho nvert, inicio da lista de adjacentes
  gr->vetoradj = (struct List*)malloc(nvert * sizeof(struct List));
  //inicializando
  for (i = 0; i < gr->nvert; ++i)
        gr->vetoradj[i].head = NULL;
  //vetor que armazena idades;
  gr->idade=(int*)calloc(nvert, sizeof(int));
  //auxiliar para realizar a busca pelas pessoas que gostaram da musica
  gr->verificado=(int*)calloc(nvert,sizeof(int));
  return gr;
}

//salvar idades de cada vertice
int insereIdade(Grafo* gr, int nvert){
  int i, aux;
  for(i = 0; i <nvert; i++){
    scanf("%d", &aux);
    scanf("%d", &gr->idade[aux-1]);
  }
  return 1;
}

// Adicionar uma relacao entre dois vertices supondo um grafo nao direcionado
void addNode(Grafo* gr, int a, int b) {
    // adiciona a relacao no inicio da lista de adjacencia de cada um dos vertices
    //adicionando b, na lista de relaçoes de a
    struct Node* novoNode = newNode(b);
    novoNode->next = gr->vetoradj[a].head;
    gr->vetoradj[a].head = novoNode;
    //adicionando a, na lista de relaçoes de b
    novoNode = newNode(a);
    novoNode->next = gr->vetoradj[b].head;
    gr->vetoradj[b].head = novoNode;
}

//inserir aresta (relacao)
int insereAresta(Grafo* gr, int m){
  int i, a, b;
  for(i = 0; i<m; i++){
    //lendo os dois vertices que se relacionam
    scanf("%d %d", &a,&b);
    //diminui 1 de cada id para coincidir id com indice do vetor
    addNode(gr,a-1, b-1);
  }
  return 1;
}

//ver quantas pessoas
int relacoes(Grafo *gr, int first, int nvert, int *ouviu){
  if(first+1 > nvert)
    return 0;
  else if(gr->verificado[first] == 1)
    return 0;
  else if(gr->idade[first] >= 35)
    return 0;
  else{
    gr->verificado[first] = 1;
    if(gr->idade[first]<35){
      (*ouviu)++;
      struct Node* aux = gr->vetoradj[first].head;
      while (aux) {
        relacoes(gr,aux->id, nvert, ouviu);
        aux = aux->next;
      }
    }
  }
  return ouviu[0];
}

//remover Grafo
int removergrafo(Grafo *gr, int n){
  int i;
  free(gr->verificado);
  free(gr->idade);
  for(i = 0; i < n; i++){
      struct Node* aux = gr->vetoradj[i].head;
      while(aux){
          struct Node *del = aux;
          aux = aux->next;
          free(del);
      }
    }
  free(gr->vetoradj);
  free(gr);
  return 1;
}

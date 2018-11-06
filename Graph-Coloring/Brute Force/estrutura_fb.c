/*Universidade Federal de Minas Gerais
  Algoritmos e Estrutura de dados 03
  TP 03 - Biblioteca para criação e operaçoes em grafos
  Francielly das Neves Lafaete - 2017023382*/
#include <stdio.h>
#include <stdlib.h>
#include "estrutura_fb.h"
//Parte1: estruturas e operaçoes basicas para lista de adjacencia: Node, List. 

  struct Node {
    int id;
    struct Node* next;
  };
  struct List {
     //ponteiro para o primeiro no da lista
    struct Node *head; 
  };
  struct Node* newNode(int id) {
    //Cria um novo No.
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
  }
//Parte 2: estrutura e opreaçoes com o Grafo
//definicao do tipo Grafo
  struct grafo{
    int nvert; //numero de vertices do Grafo
    int* rotas;//em qual rota o vertice sera desligado
    struct List* vetoradj;//vetor de adjacencias
  };
  //Criar Grafo
  Grafo* criaGrafo(int nvert){
    Grafo *gr;
    int i;
    gr = (Grafo*)malloc(sizeof(struct grafo));
    // controi um vetor de tamanho nvert, inicio da lista de adjacentes
    gr->nvert = nvert;
    gr->vetoradj = (struct List*)malloc(nvert * sizeof(struct List));
    //inicializando
    for (i = 0; i < gr->nvert; ++i)
      gr->vetoradj[i].head = NULL;
    //vetor que armazena a rota;
    gr->rotas=(int*)malloc(nvert*sizeof(int));
    return gr;
  }
  //Adicionar uma aresta entre dois vertices supondo um grafo nao direcionado
  void criaAresta(Grafo* gr, int a, int b) {
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

  //Ler as Arestas do Grafo
  void LerArestas(Grafo* gr, int m){
    int i, a, b;
    for(i = 0; i < m; i++){
      //lendo os dois vertices que se relacionam
      scanf("%d", &a);
      scanf("%d", &b);
    //diminui 1 de cada id para coincidir id com indice do vetor
    criaAresta(gr,a-1, b-1);
    }
  }
  //remover Grafo
  int removergrafo(Grafo *gr, int n){
    int i;
    free(gr->rotas);
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
/*Parte 3: Funçoes para a resolucao do Problema.
  Abordagem Força Bruta.
  Procura alocacao: Gera todas as combinaçoes possiveis de rodada, a cada combinaçao gerada, e verificado se respeita as regras
  de atualizaçao do servidor, caso afirmativo(1),  é verificado o numero de rodadas gastas, se for menor que a combinaçao salva, atribui 
  ao vetor final. 
  Portanto no final da execuçao teremos uma das menores combinaçoes possiveis salvas no vetor final. */
  int valido(int n, int *vetor, Grafo *gr){
    struct Node* aux;
  for(int i = 0; i < gr->nvert; i++){
    aux = gr->vetoradj[i].head;
    while (aux) {
        if(vetor[i] == vetor[aux->id])
          return 0;
        aux = aux->next;
      }
    }
  return 1;
  }

  int procura_alocacao(Grafo* gr,int *vetor, int n, int index, int aux, int *max){
    int i;
    //Encontrou uma combinaçao completa com n posiçoes
    if(index == n){
      //verifica se esta combinaçao respeita as regras de atualizacao dos servidores
      int pode = valido(n, vetor, gr);
      if(pode){
        //printf("entrou aqui");
        //se respeita as regras:
        //procura-se o maior elemento do vetor == o maior numero de rodadas necessarios
        int maxAux = 0;
        for(int i = 0; i <n; i++){
          if(vetor[i] > maxAux)
            maxAux = vetor[i];
      }
      //se o vetor encontado precisar de menos rodadas que o vetor salvo, realizar a substituicao
      if(*max >maxAux){
        *max = maxAux;
        for(int i = 0; i < n; i++){
          gr->rotas[i] = vetor[i]+1;
          //printf("%d e ",gr->rotas[i]);
          //printf("o q q deu?");
        }
      }
    }
  }else{
    //procurar elementos, para o servidor, vertice index; 
    for(i = 0; i <= n; i++){
      //as possibilidades de rodadas para o servidor index, sao de  0 ate aux
      if(aux == i){
        aux++;//proximo servidor, tem como possibilidade todas as rodadas ate agora +1
        vetor[index] = i;
     
        return procura_alocacao(gr, vetor, n, index+1, aux, max);
      }
      vetor[index] = i;
      procura_alocacao(gr, vetor, n,  index+1, aux, max);
    }
  }
  return 0;
  }
  //Salva a resposta do problema em dois arquviso txt
  //alocacao.txt  = alocacao de cada vertice
  //rodadas.txt = numero total de rodadas necessarias para atualizar todos os servidores
  void salvaRespostas(Grafo* gr, int nvert, int max){
	 int i;
    FILE *fp;
    fp = fopen("alocacao.txt", "w");
    for(i = 0; i < nvert; i++)
		  fprintf(fp,"%d %d\n",i+1, gr->rotas[i]);
    fclose(fp);
    fp = fopen("rodadas.txt", "w");
    fprintf(fp, "%d\n", max+1);
    fclose(fp);
  }
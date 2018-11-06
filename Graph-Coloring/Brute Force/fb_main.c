/*Universidade Federal de Minas Gerais
  Algoritmos e Estrutura de dados 3
  Trabalho pratico 03 - versão Força Bruta
  Nome: francielly das Neves Lafaete - 2017023382*/
#include <stdio.h>
#include <stdlib.h>
#include "estrutura_fb.h"
/*Na versão força Bruta, foi utilizado a abordagem de lista de adjacencia, para o armazenamento das aretas.
  Para uma melhor clareza, foi modularizada, criando-se a biblioteca "estrutura_forcabruta.h", 
  que conta com as operaçoes de criaçao, insersao e remorsao do grafo, 
  assim como a funçao recursiva de encontrar todas as possiveis alocaçoes dos servidores*/ 
int main(){
	int nvert, m, max;
  Grafo* gr;
 	//ler numero de vertices = numero de servidores e arestas = relaçoes entre eles
  scanf("%d",&nvert);
  scanf("%d", &m);
  //criar Grafo
  gr = criaGrafo(nvert);
  //salvar arestas = relaçoes entre servidores
  LerArestas(gr, m);
   max = nvert;
  //vetor auxiliar para salvar as combinaçoes possiveis. 
  int *vetor = (int*)calloc(nvert,sizeof(int));
  procura_alocacao(gr,vetor,nvert, 0,0, &max);
  //Vertice + rodada de atualização
  salvaRespostas(gr, nvert,max);
  //Desalocando o grafo
  removergrafo(gr,nvert);
  //desalocando vetor auxiliar
  free(vetor);
	return 0;
}
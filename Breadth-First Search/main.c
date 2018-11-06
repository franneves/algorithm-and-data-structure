//Universidade Federal de Minas Gerais
//Algoritmos e estrutura de dados 3 - TP0 - O Hit do verão
//Aluna: Francielly das Neves Lafaete

#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){
  int nvert, m, aux, first, ouviu;
  Grafo* gr;

  //ler numero de pessoas e numero de relaçoes
  scanf("%d%d",&nvert, &m);

  //criar Grafo
  gr = criar(nvert);
  if(gr == NULL)
    printf("nao salvou\n");

  //salvar idade
  aux = insereIdade(gr,nvert);
  if(aux == 0)
      printf("idades nao foram salvas\n");

  //salvar relaçoes
  aux = insereAresta(gr, m);
  if(aux == 0)
    printf("relaçoes nao salvas\n");

  //primeira pessoa a escutar
  scanf("%d",&first);
  first = first - 1;

  //contar quantas pessoas gostaram da musica
  ouviu = 0;
  aux = relacoes(gr, first, nvert, &ouviu);
  printf("%d\n", ouviu);

  //desalocar grafo;
  aux = removergrafo(gr, nvert);
  if(aux == 0)
    printf("Grafo nao desalocado\n");

  return 0;
}

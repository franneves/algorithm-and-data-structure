/*Universidade Federal de Minas Gerais
  Algoritmos e Estrutura de dados 03
  TP 03 - Versao Heuristica
  Francielly das Neves Lafaete - 2017023382*/
/*Versao Heuristica do TP03, 
  Ao contrario da versão força bruta, a cada numero adicionado no vetor de combinaçao e verificado qual a menor rodada possivel de se 
  adicionar naquela posiçao, nao repitindo a posiçao dos seus adjacentes que ja foram alocados. O primeiro vetor formado e o escolhido*/
#include<stdio.h>
#include <stdlib.h>
#include <stdio.h>

 /*ve se a cor c, pode ser salva no vetor de cores, 
 ou seja, ve se nao ha nennhum vertice adjacente a v que possui a cor c*/
int valido(int v, int **matriz_adj, int *vrodadas, int c, int V){
    for (int i = 0; i < V; i++)
        if (matriz_adj[v][i] && c == vrodadas[i])
            return 0;
    return 1;
}
 
/*Funçao recursiva, que chama todas as combinaçoes possiveis de rodadas,
  Há uma otimizaçao, assim que se chega a um prefixo nao valido, todas as suas variaçoes nao sao calculadas*/
int procura_alocacao(int **matriz_adj, int m, int *vrodadas, int v, int V, int *rodadas){
    // Se o vetor de cores esta completamente preenchido, encontramos uma soluçao valida. 
    if (v == V){
        //printf("rodadas: %d\n", max);
        return 1;
    }
    /*o maximo valor que uma rodadas que pode ter e o numero de conexoes, considerando um pior caso,
      em que todas as relaçoes sao de um sevidor para todos os outros n-1*/
    for (int c = 1; c <= m; c++){
        if (valido(v, matriz_adj, vrodadas, c, V) == 1){
           /*na rodada c o servidor v pode ser desligado, nenhum servidor adjacente a ele ate a sua posiçao e desligado em c
            ira ser desligado*/
           vrodadas[v] = c;
           if(c > *rodadas)
             *rodadas = c;
            //chamamos a funçao para escolher a rodada do proximo vertice
           if (procura_alocacao(matriz_adj, m, vrodadas, v+1, V, rodadas) == 1)
             return 1;
        }
      }
    return 0;
}

int main(){
   
  int n, m, **matriz_adj, i;
  //ler o numero de vertice e numero de aretas
  scanf("%d", &n);
  scanf("%d", &m);
  //alocar matriz de adjacencia
  matriz_adj= (int**)calloc(n, sizeof(int*));
  for(i = 0; i< n; i++)
    matriz_adj[i] = (int*)calloc(n, sizeof(int));
  //salvar vertice e arestas em uma matriz de adjacencia
  int a, b;
  for(i = 0; i < m; i++){
    scanf("%d%d", &a, &b);
    a=  a-1;
    b= b-1;
    matriz_adj[a][b]=1;
    matriz_adj[b][a]=1;
  }
  //Vetor com a rodada de cada vertice: 
  int *vrodadas;
  vrodadas = (int*)calloc(n, sizeof(int));
  //salvar o numero de rodadas necessarios
  int rodadas = -1;
  //chamdno a funcao recursiva a partir da primeiro vertice
  procura_alocacao(matriz_adj, m, vrodadas, 0, n, &rodadas);
  //desalocando a matriz
  for(i = 0; i < n; i++)
    free(matriz_adj[i]);
  free(matriz_adj);
  //Salvando os dados:
  FILE *fp;
  fp = fopen("rodadas.txt", "w+");
  fprintf(fp, "%d\n", rodadas);
  fclose(fp);
  fp = fopen("alocacao.txt", "w+");
  for(i = 0; i <n; i++)
    fprintf(fp, "%d %d\n",i+1, vrodadas[i]);
  fclose(fp);
  return 0;
}

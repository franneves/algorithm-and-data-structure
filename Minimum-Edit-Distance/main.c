/*Universidade Federal de Minas Gerais
  Algoritmos e Estrutura de Dados 3
  Trabalho Prático 02
  Aluna: Francielly das Neves Lafaete - 2017023382*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//comparaçao entre strings  para funçao qsort
int cstring_cmp(const void *a, const void *b){
	const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

//Calculo Distancia Minima para transformar string A em string B
int MinimumEditDistance(char *dicionario, char *padrao){
	int N, M, remove, insercao, replace, i, j;
	N = strlen(dicionario);
	M = strlen(padrao);
	int EditDistanceTable[N+1][M+1]; //linha == dicionario, coluna == padrao;
	//inicializando minha tabela
	EditDistanceTable[0][0] = 0;
	for(i = 1; i <= M; i++)
		EditDistanceTable[0][i]= i;
	for(i = 1; i<=N; i++)
		EditDistanceTable[i][0] = i;
	//completando a tabela
	for(i =1; i <= N; i++)
		for(j = 1; j <= M; j++){
			if(dicionario[i-1] == padrao[j-1])
				EditDistanceTable[i][j] = EditDistanceTable[i-1][j-1];
			else{
				insercao = EditDistanceTable[i-1][j] +1;
				remove = EditDistanceTable[i][j-1]+1;
				replace =EditDistanceTable[i-1][j-1]+1;
				if(insercao <= remove && insercao <= replace)
					EditDistanceTable[i][j] = insercao;
				else if(remove <= insercao && remove <= replace)
					EditDistanceTable[i][j] = remove;
				else
					EditDistanceTable[i][j] = replace;
			}
		}
	return EditDistanceTable[N][M];
}

int main(){
	int D, k, i, aux, tamN, tamM, res;
	//lendo Tamanho de palavras que compoe o dicionario e o limite K de alteraçoes
	scanf("%d%d", &D, &k);
	//Duas strings uma para o padrao outra para o dicionario
	//um vetor de string para as ocorrencias que respeitam o limite K de alteraçoes
	char *padrao, *dicionario, **resposta;
	padrao = (char*)malloc(501*sizeof(char));
	dicionario = (char*)malloc(6001*sizeof(char));
	//padrao, tamM = tamanho do padrao
	scanf("%s", padrao);
	tamM = strlen(padrao);
	//inicializando o vetor de respostas
	res = 0;//numero de strings dentro do vetor
	resposta = (char**)malloc(D*sizeof(char*));
	for(i = 0; i<D; i++)
		resposta[i] = (char*)calloc((tamM+k+2),sizeof(char));
	/*Ler uma palavra do dicionario, verifica se ela tem um tamanho compativel com o padrao
	  caso tenha, é calculado entao a Minimum Edit Distance, caso ela seja menor que K, 
	  a palavra e salva no vetor dicionario, acrescentamos um caracter no inicio que corresponde
	  a Minimum Edit Distance daquela palavra, para auxiliar na ordenaçao*/
	for(i = 0; i < D; i++){
		scanf("%s\n", dicionario);
		tamN = strlen(dicionario);
		if(tamN <=(tamM + k) && tamN >=(tamM -k)){
			aux = MinimumEditDistance(dicionario, padrao);
			if(aux <= k){
				resposta[res][0] = aux+1;
				strcat(resposta[res], dicionario);
				res++;
			}
		}
	}
	free(padrao);
	free(dicionario);
	/*Ordena o vetor de Strings, como o primeiro caracter corresponde a Minimum Edit Distance,
	  Ele sera o primeiro fator a ser considerado na ordenaçao, caso seja igual sera considerado
	  a ordem da tabela ASCII*/
	qsort(resposta, res,sizeof(char*),cstring_cmp);
	/*Imprime o vetor de strings, pulando o primeiro caracter de cada palavra, que corresponde a
	  Minimum Edit Distance*/
	for(i = 0; i < res; i++){
		printf("%s\n", &resposta[i][1]);
	}
	/*libera a memoria alocada para o vetor de strings*/
	for(i = 0; i < D; i++)
		free(resposta[i]);
	free(resposta);

	return 0;
}

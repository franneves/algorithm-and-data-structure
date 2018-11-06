/*	Universidade Federal de Minas Gerais
 	Algoritmos e Estrutura de Dados 3
	Aluna: Francielly das Neves Lafaete
	Problema: Dado um arquivo de entrada e o tamanho disponivel na memoria principal denominado de M, retorna o arquivo ordenado. 
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mem.h"
/*---------------- Estruturas Auxiliares ---------*/
int a_menor_que_b(char* a, char* b, int len) {
    int i;
    for(i = 0; i < len; i++){
      if(a[i] > b[i])
        return 0;
      else if(b[i] > a[i])
        return 1;
    }
    return 1;
}
//estrutura de dado auxiliar para ordenar 
struct arquivo{
  FILE *f;//arquivo aberto
  int i;//numero do arquivo
  char *buffer;//palavra do topo do arquivo
};
//comparaçao entre strings  para funçao qsort 
int cstring_cmp(const void *a, const void *b){
	const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}
//coloca o primeiro elemento do arquivo na variavel topo
void preencheTopo(struct arquivo* arq){
  int  aux;
  if(arq->f != NULL){
    aux = fscanf(arq->f,"%[^\n]%*c",arq->buffer);
    if(aux == -1){
    		//acabou arquivo
    		//deletar arquivo
            char novo[20];
            sprintf(novo, "Temp%d.txt", arq->i);
            fclose(arq->f);
            mathias_free(arq->buffer);
            remove(novo);
            arq->f = NULL;
    }
  }
 }
 //pecorre todos os arquivos abertos e seleciona o elemento menor
int procuraMenor(struct arquivo* arq, int n_arquivos,int inicio, char *menor){
    int i, idx = -1,len;
    for(i=inicio; i<n_arquivos+inicio; i++){
        if(arq[i].f != NULL){
            if(idx == -1)
                idx = i;
            else{
              len = strlen(arq[idx].buffer);
              if(a_menor_que_b(arq[i].buffer,arq[idx].buffer, len)== 1)
                    idx = i;
            }
        }
    }
    if(idx != -1){
        strcpy(menor,arq[idx].buffer);
        if(arq[idx].f != NULL)
            preencheTopo(&arq[idx]);
        return 1;
    }else
       return 0;
}
/*--------- Ordenaçao: processo divido em  3 casos --------*/
//Primeiro caso: cabe todas as strings do arquivo na memoria principal
//Sendo assim, apenas uma passada e necessaria
void Ordena_em_uma_passada(const char *nome, int len, int M, const char *out){
  int total = 0,  aux = 0, i;
  char **frases;
  //frases = armazena M strings na memoria principal
  frases = (char**)malloc(M*sizeof(char*));
  for(i = 0; i < M; i++)
    frases[i] = (char*)mathias_malloc((len+1)*sizeof(char));
  //abrindo arquivo de entrada
  FILE *f = fopen(nome, "r+");
  fscanf(f, "%u%*c", &len);
  //pecorrendo todas as strings
  while(fscanf(f,"%[^\n]%*c", frases[total])!= EOF){
    total++;//numero de strings em memoria principal
    if(total >= M){//M strings, limite, ordenada e salva no arquivo temporario
      qsort(frases,M,sizeof(char*),cstring_cmp);
      FILE *fp = fopen(out,"w+");
        fprintf(fp, "%d\n", len);
        for(i = 0; i < M; i++){
          fprintf(fp, "%s", frases[i]);
          fprintf(fp, "\n");
        }
        fclose(fp);
        total = 0;//salvo as duas strings, retornamos a zero
        if(aux < M)
          aux++;
        if(aux > M)
          aux = 1;
    }
  }
  //liberando memoria alocada
  for(i = 0;  i< M; i++)
    mathias_free(frases[i]);
  free(frases);
}
//para os demais casos e necessario dividir o meu arquivo inicial em arquivos ordenados auxiliares 
//para maximizar, cada arquivo tem se possivel M strings ordenadas
int criaArquivosOrdenados(const char *nome, int len, int M){
  int total = 0,  aux = 0, i;
  char **frases, *novo;
  M = M - 1;
  //frases = armazena M strings na memoria principal
  frases = (char**)malloc(M*sizeof(char*));
  for(i = 0; i < M; i++)
    frases[i] = (char*)mathias_malloc((len+1)*sizeof(char));
  //novo = nome dos arquivos temporarios
  novo = (char*)malloc(40*sizeof(char));
  //abrindo arquivo de entrada
  FILE *f = fopen(nome, "r+");
  fscanf(f, "%u%*c", &len);
  //pecorrendo todas as strings
  while(fscanf(f,"%[^\n]%*c", frases[total])!= EOF){
    total++;//numero de strings em memoria principal
    if(total >= M){//M strings, limite, ordenada e salva no arquivo temporario
      sprintf(novo, "Temp%d.txt", aux);
      qsort(frases,M,sizeof(char*),cstring_cmp);
      FILE *fp = fopen(novo,"a");
        for(i = 0; i < M; i++){
          fprintf(fp, "%s", frases[i]);
          fprintf(fp, "\n");
        }
        fclose(fp);
        total = 0;//salvo as duas strings, retornamos a zero
	      aux++;
    }
  }//pecorreu todo arquivo de entrada
  if(total > 0){//se restou uma strings nas variaveis auxiliares que nao foi salva
    qsort(frases,total,sizeof(char*),cstring_cmp);
    sprintf(novo, "Temp%d.txt", aux);
    FILE *fp = fopen(novo,"a");
      for(i = 0; i < total; i++)
        fprintf(fp, "%s\n", frases[i]);
      fclose(fp);
    total = 0;
    aux++;
  }
  //liberando memoria alocada
  free(novo);
  for(i = 0;  i< M; i++)
    mathias_free(frases[i]);
  free(frases);
  return aux;
}

//Segundo caso: quando o arquvio principal foi divido
//e o numero de arquivos gerados e <= M.
//sendo assim em uma intercalaçao direta e possivel ordernar
void ordenaa(const char *nome, int n_arquivos, int len, int M, int vez){
  //abrindo arquivo de saida
  FILE *fp = fopen(nome, "w+");
  fprintf(fp, "%d\n", len);
  char novo[20];//novo = nome dos arquivos temporarios
  int i;
  char menor[len];//armazena a menor string = a string que deve ser salva no arquivo de saida
  struct arquivo* arq;
  arq = (struct arquivo*)malloc(n_arquivos*sizeof(struct arquivo));
  for(i = 0; i < n_arquivos; i++){
    if(vez == 1)
    	sprintf(novo, "Saida%d.txt", i);
    else
    	sprintf(novo, "Temp%d.txt", i);
    arq[i].f = fopen(novo, "r");
    arq[i].i = i;
    arq[i].buffer = (char*)mathias_malloc((len+1)*sizeof(char));
    preencheTopo(&arq[i]);
  }
  while(procuraMenor(arq, n_arquivos,0, menor) == 1){
     fprintf(fp, "%s\n", menor);
  }
  fclose(fp);
}
//Terceiro caso: quando o numero principal foi divido em N arquivos, sendo N > M
//Neste caso e necessario mais intercalaçoes
void inter(const char *nome, int n_arquivos, int len, int M){
   int passadas;
   FILE *fp;
  char novo[20];
  int i=0, j=0, idx = 0;
  char menor[len];
  struct arquivo* arq;
  arq = (struct arquivo*)malloc(n_arquivos*sizeof(struct arquivo));
  passadas = n_arquivos/M;
  while(passadas > 0){
  	sprintf(novo, "Saida%d.txt", j);
  	fp = fopen(novo, "w+");
  	
  for(i = idx; i < idx+M; i++){
    sprintf(novo, "Temp%d.txt", i);
    arq[i].f = fopen(novo, "r");
    arq[i].i = i;
    arq[i].buffer = (char*)mathias_malloc((len+1)*sizeof(char));
    preencheTopo(&arq[i]);
    }
    
    while(procuraMenor(arq, M,idx, menor) == 1){
     fprintf(fp, "%s\n", menor);
   }
  fclose(fp);
  idx = idx+M;
  passadas--;
  j++;
}
if(passadas*M < n_arquivos){
	//criar mais um arquivo de saida
	sprintf(novo, "Saida%d.txt", j);
  	fp = fopen(novo, "w+");
  	for(i = idx; i < n_arquivos; i++){
	
    sprintf(novo, "Temp%d.txt", i);
    arq[i].f = fopen(novo, "r");
   	if(arq[i].f == NULL)
   		break;
    arq[i].i = i;
    arq[i].buffer = (char*)mathias_malloc((len+1)*sizeof(char));
    preencheTopo(&arq[i]);
    }
 
    while(procuraMenor(arq, i-idx, idx, menor) == 1){
     fprintf(fp, "%s\n", menor);
    }
  fclose(fp);
  passadas--;
  j++;

}

ordenaa(nome, j, len, M, 1);
//deletar arquivos de saida
while(j>=0){
	sprintf(novo, "Saida%d.txt", j);
	remove(novo);
	j--;
	}
}

void external_sort(const char* input_file, const char* output_file, unsigned int memory) {
  int len, n_arquivos;
  int M, qtd = 0;
  //abrindo o arquivo de entrada
  FILE* in = fopen(input_file, "r");
  //lendo tamanho da string
  fscanf(in, "%d%*c", &len);
  char t[len+1];
  while(fscanf(in,  "%[^\n]%*c", t)!= EOF){
        qtd++;
  }
    M = memory*1000;
    if(M > qtd*len){//ira dar para ordenar em uma unica passada
       	M = qtd;
   		Ordena_em_uma_passada(input_file, len, M, output_file);
 	}else{
 	   M = M/(len+1);
    	n_arquivos = criaArquivosOrdenados(input_file, len, M);
    	if(n_arquivos<= M){
    		//ordena em uma intercalada
    		ordenaa(output_file, n_arquivos, len, M, 0);
    	}else{
   			//ordena em mais de duas etapas\n
   			inter(output_file, n_arquivos, len, M);
     	}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#define BUFFER 256

vetor *ler_ficheiro (FILE *f, int *numero_filmes) {
    vetor *filmes;
    int votos;
    float classificacao;
    char titulo[BUFFER], ano[7];
    int i, ano_int, contador = 0;

    // lê primeira linha:

    fscanf(f, "%*s %*s %*s %*s %*s");
    while(fscanf(f, "%*d %d %f %s %s", &votos, &classificacao, titulo, ano) == 4) {
        //ano -> string para int
        for (i = 0; i < 5; i++) {
            ano[i] = ano[i+1];
        }
        ano[4] = '\0';
        ano_int = atoi(ano);
        //
        filmes->elementos = realloc(filmes->elementos, sizeof(v_elemento)*(contador+1));
        filmes->elementos[contador].titulo = realloc(filmes->elementos->titulo, (strlen(titulo)+1)); 
        filmes->elementos[contador].classificacao = classificacao;
        filmes->elementos[contador].ano = ano_int;
        filmes->elementos[contador].votos = votos;
        contador++;
    }
    *numero_filmes = contador;
    return filmes;
}

int main(){

    FILE *f;
    vetor *filmes;
    int num_filmes;
    f = fopen("IMDB.txt", "r");

    filmes = ler_ficheiro(f, &num_filmes);

    return 0;
}
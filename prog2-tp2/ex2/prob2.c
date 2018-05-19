#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

typedef struct _capital {
    char pais[SIZE];
    char capital[SIZE];
    int habitantes;
} capital;

capital* analisarFicheiro(FILE *ficheiro, int *num_capitais) {
    capital *capitais_guardar;
    int j = 0;
    char pais[SIZE], capital[SIZE];
    int habitantes, i=1;
    capitais_guardar = malloc(0);
    *num_capitais = 0;
    while(1) {
        printf("Hello");    
        if(fscanf(ficheiro, "%s %s %d", pais, capital, &habitantes) != 3) break;

        capitais_guardar = realloc(capitais_guardar, sizeof(capital)*i);
    //    strcpy(capitais_guardar[j].pais, pais);
//        strcpy(capitais_guardar[j].capital, capital);
  //      capitais_guardar[j].habitantes = habitantes;
        *num_capitais++;
        j++; i++;

    }
    return capitais_guardar;
}

capital *ordenarLista(capital *lista_capitais, int numero_capitais) {
    capital aux;
    int passo, imin, i;
    for(passo=0; passo < numero_capitais - 1; passo++) {
        imin = passo;
        i = passo + 1;
        while (i < numero_capitais){
            if (lista_capitais[i].habitantes > lista_capitais[imin].habitantes) imin = i;
                i++;
        }
        if (imin != passo) {
            aux = lista_capitais[passo];
            lista_capitais[passo] = lista_capitais[imin];
            lista_capitais[imin] = aux;
        }
    }
    return lista_capitais;
}


void gerarRelatorio(char *nome_ficheiro, capital *resultados, int num_capitais) {
    FILE *ficheiro;
    int i;
    ficheiro = fopen(nome_ficheiro, "w");
    resultados = analisarFicheiro(ficheiro, &num_capitais);
    resultados = ordenarLista(resultados, num_capitais);
    for (i = 0; i < num_capitais; i++) {
        fprintf(ficheiro, "%s - %s - %d", resultados->pais, resultados->capital, resultados->habitantes);
    }
}

int main() {
    capital *resultados;
    int i;
    int num_capitais;
    FILE *ficheiro;
    ficheiro = fopen("capitais.txt", "r");
    resultados = analisarFicheiro(ficheiro, &num_capitais);
    for (i = 0; i < 100; i++) {
        printf("%s - %s - %d", resultados[i].pais, resultados[i].capital, resultados[i].habitantes);
    }
    //gerarRelatorio("capitais_output.txt", resultados, num_capitais);
}
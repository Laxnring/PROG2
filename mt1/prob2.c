#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUFFER 256

typedef struct {
    char palavra[100];
    int ocorrencias;
} registo;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** exercicio 2.1 ***/
registo *analisarFicheiro(FILE *ficheiro, int *num_palavras)
{
    char linha[BUFFER];
    registo *palavras;
    char *token, separador[2] = " ";
    int tamanho_registo = 0, flag, i;
    palavras = 0; //inicializar pointer
    
    while(fgets(linha, BUFFER, ficheiro) != NULL) {
        token = strtok(linha, separador);

        while (token != NULL) {
            for (i = 0; i < strlen(token); i++) {
                if (token[i] == '\n') {
                    token[i] = '\0';
                }
            }
            flag = 0;
            for (i = 0; i < tamanho_registo; i++) {
                if (!strcmp(token, palavras[i].palavra)) {
                    flag = 1; //token ja existe
                    palavras[i].ocorrencias++;
                    break;
                }
            }
            if (flag == 0) { // se token nao existe
                palavras = realloc(palavras, (tamanho_registo+1)*sizeof(registo));
                if (palavras == NULL) exit(0);
                tamanho_registo++;
                strcpy(palavras[tamanho_registo-1].palavra, token);
                palavras[tamanho_registo-1].ocorrencias = 1;
            }
            token = strtok(NULL, separador);
        }
    }
    *num_palavras = tamanho_registo;
    return palavras;

}

/*** exercicio 2.2 ***/
void gerarRelatorio(FILE *ficheiro, registo *resultados, int num_palavras)
{
    int i, contador = 1;
    if (!ficheiro || !resultados) return;
    for (i = 0; i < num_palavras; i++) {
        fprintf(ficheiro, "%d:  %7s: (%d)\n", contador, resultados[i].palavra, resultados[i].ocorrencias);
        contador++;
    }
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main() {
    FILE *fin, *fout;
    char nomeIn[50], nomeOut[50];
    registo *resultados;
    int n;

    //printf("Ficheiro de entrada? ");
    //scanf("%s", nomeIn);
    //printf("Ficheiro de saida? ");
    //scanf("%s", nomeOut);

    fin = fopen("dialogo.txt", "r");
    if (fin == NULL)
        return 1;

    fout = fopen("out.txt", "w");
    if (fout == NULL)
        return 1;

    resultados = analisarFicheiro(fin, &n);
    gerarRelatorio(fout, resultados, n);

    fclose(fin);
    fclose(fout);
    free(resultados);

    return 0;
}

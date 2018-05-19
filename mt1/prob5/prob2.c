#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char nome[15];
    int vitorias;
} jogador;


/* problema 2 */
jogador* conta_vitorias(FILE* f, int *njogadores)
{
    if (!f || !njogadores) return NULL;
    char nomes[10];
    jogador *vitorias_lista, aux;
    int size_of_lista = 0, flag, i, posicao = 0, j;
    vitorias_lista = 0;

    
    while (fscanf(f, "%s", nomes) == 1) {
        flag = 0;
        for (i = 0; i < size_of_lista; i++) {
            if (!strcmp(vitorias_lista[i].nome, nomes)) {
                flag = 1;
            } 
        }
        if (flag == 0) {
            //aumenta lista e adiciona nome
            size_of_lista++;
            vitorias_lista = realloc(vitorias_lista, sizeof(jogador)*size_of_lista);
            strcpy(vitorias_lista[size_of_lista-1].nome, nomes);
            vitorias_lista[i].vitorias = 0;
        }

        for (i = 0; i < size_of_lista; i++) {
            if (!strcmp(vitorias_lista[i].nome, nomes)) {
                vitorias_lista[i].vitorias++;
            }
        }
    }

    for (i = 0; i < size_of_lista-1; i++) {
        for (j = 0; j < size_of_lista-i-1; j++) {
            if (vitorias_lista[j].vitorias > vitorias_lista[j+1].vitorias) {
                aux = vitorias_lista[j];
                vitorias_lista[j] = vitorias_lista[j+1];
                vitorias_lista[j+1] = aux;
            }
        }
    }

    *njogadores = size_of_lista;

    return vitorias_lista;
    
}

/***************************************************/
/*** não alterar o ficheiro a partir deste ponto ***/
/***************************************************/

int main()
{
    FILE * f = fopen("log.txt", "r");
    jogador *j;
    int i, n=0;

    j = conta_vitorias(f, &n);

    fprintf(stderr, "Vencedores:\n");
    if(j != NULL)
    {
        for(i=0; i<n; i++)
            fprintf(stderr, "%s - %d\n", j[i].nome, j[i].vitorias);
    }

    free(j);
    fclose(f);
    return 0;
}

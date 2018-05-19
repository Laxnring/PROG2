#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

void retira_duplicados(vetor *vec)
{
    int i, j, limite;
    limite = vec->tamanho;
    for (i = 0; i < limite; i++) {
        for (j = i; j < limite; j++) {
            printf("%s %s\n", vec->elementos[i].str, vec->elementos[j].str);
            if (!strcmp(vec->elementos[i].str, vec->elementos[j].str)) {
                vetor_remove(vec, j);
                limite--;
            }
        }
    }
}

vetor *interseta(lista *l1, lista *l2)
{
    int i, j;
    elemento *itera1, *itera2;
    vetor *inter;
    inter = vetor_novo();
    char *elem = malloc(0);
    for (itera1 = l1->inicio; itera1 != NULL; itera1=itera1->proximo) {
        for (itera2 = l2->inicio; itera2 != NULL; itera2=itera2->proximo) {
            if (!strcmp(itera1->str, itera2->str)) {
                elem = realloc(elem, strlen(itera1->str)+1);
                strcpy(elem, itera1->str);
                vetor_insere(inter, elem, inter->tamanho);
            }
        }
    }
    return inter;
}

vetor *anteriores(lista *lst, const int ano)
{
    int j, maximo, ano_filme;
    char anos[5];
    elemento *itera;
    vetor *retorna;
    retorna = vetor_novo();
    char *elem = malloc(0);
    for (itera = lst->inicio; itera != NULL; itera = itera->proximo) {
        //ler ano 
        for (j = 0; j < 4; j++) {
            maximo = strlen(itera->str);
            anos[3-j] = itera->str[maximo-j-2];
        }
        ano_filme = atoi(anos);
        printf("%d\n", ano_filme);

        if (ano_filme < ano) {
            elem = realloc(elem, strlen(itera->str)+1);
            strcpy(elem, itera->str);
            vetor_insere(retorna, elem, retorna->tamanho);
        }
    }
    return retorna;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

vetor *lerAtores(FILE *ficheiro) {
    char buffer[256], *nlptr;
    vetor *atores;

    if (ficheiro == NULL)
        return NULL;

    atores = vetor_novo();

    while (!feof(ficheiro)) {
        fgets(buffer, 255, ficheiro);
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';

        vetor_insere(atores, buffer, atores->tamanho);
    }

    return atores;
}

lista *lerFilmes(FILE *ficheiro) {
    char buffer[256], *nlptr;
    lista *filmes;

    if (ficheiro == NULL)
        return NULL;

    filmes = lista_nova();

    while (!feof(ficheiro)) {
        fgets(buffer, 255, ficheiro);
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';

        lista_insere(filmes, buffer, NULL);
    }

    return filmes;
}

int main() {
    FILE *fa, *ff, *ff2;
    vetor *atores, *resultado, *resultado1;
    lista *filmes, *filmes2;

    /* testes */
    fa = fopen("atores2.txt", "r");
    ff = fopen("filmes.txt", "r");
    ff2 = fopen("filmes2.txt", "r");

    atores = lerAtores(fa);
    filmes = lerFilmes(ff);
    filmes2 = lerFilmes(ff2);

    /* testa retira_duplicados */
    printf("Total inicial: %d\n", vetor_tamanho(atores));
    retira_duplicados(atores);
    printf("Unicos: %d (esperado: 30)\n\n", vetor_tamanho(atores));

    /* testa interseta */
    resultado = interseta(filmes, filmes2);
    if (resultado)
        printf("Intersecao: %d (esperado: 75)\n", vetor_tamanho(resultado));
    else
        printf("Intersecao: vetor NULL\n");

    /* testa anteriores */
    resultado1 = anteriores(filmes, 2000);
    if (resultado1)
        printf("\nAnteriores: %d (esperado: 106)\n", vetor_tamanho(resultado1));
    else
        printf("\nAnteriores: vetor NULL\n");

    vetor_apaga(atores);
    vetor_apaga(resultado);
    vetor_apaga(resultado1);
    lista_apaga(filmes);
    lista_apaga(filmes2);

    fclose(fa);
    fclose(ff);
    fclose(ff2);

    return 0;
}

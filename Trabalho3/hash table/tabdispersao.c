/*****************************************************************/
/*       Tabela de Dispersao | PROG2 | MIEEC | 2017/18           */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"

tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc)
{
    /* aloca memoria para a estrutura tabela_dispersao */
    if (tamanho < 1 || hfunc == NULL)
        return NULL;

    tabela_dispersao *t = (tabela_dispersao*) malloc(sizeof (tabela_dispersao));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (td_elemento **) calloc(tamanho, sizeof (td_elemento*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;
    t->hfunc = hfunc;

    return t;
}

void tabela_apaga(tabela_dispersao *td)
{
    int i;
    td_elemento *elem, *aux;

    if (td == NULL) return;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            free(elem->obj);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vetor e estrutura */
    free(td->elementos);
    free(td);
}

int tabela_insere(tabela_dispersao *td, const char *chave, const char *valor)
{
    int index;
    td_elemento * elem;

    if (!td || !chave || !valor) return TABDISPERSAO_ERRO;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(chave, td->tamanho);

    /* verifica se chave ja' existe na lista */
    elem = td->elementos[index];
    while (elem != NULL && strcmp(elem->obj->chave, chave) != 0)
        elem = elem->proximo;

    if (elem == NULL)
    {
        /* novo elemento, chave nao existe na lista */

        /* aloca memoria para o elemento */
        elem = (td_elemento*) malloc(sizeof (td_elemento));
        if (elem == NULL)
            return TABDISPERSAO_ERRO;

        /* aloca memoria para o objeto */
        elem->obj = (objeto*) malloc(sizeof (objeto));
        if (elem->obj == NULL)
            return TABDISPERSAO_ERRO;

        /* copia chave e valor */
        strcpy(elem->obj->chave, chave);
        strcpy(elem->obj->valor, valor);

        /* insere no inicio da lista */
        elem->proximo = td->elementos[index];
        td->elementos[index] = elem;
    }

    return TABDISPERSAO_OK;
}

int tabela_remove(tabela_dispersao *td, const char *chave)
{
    int index;
    td_elemento * elem, * aux;

    if (!td) return TABDISPERSAO_ERRO;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(chave, td->tamanho);

    elem = td->elementos[index];
    aux = NULL;

    /* para cada elemento na posicao index */
    while(elem != NULL)
    {
        /* se for a string que se procura, e' removida */
        if (strcmp(elem->obj->chave, chave) == 0)
        {
            /* se nao for a primeira da lista */
            if (aux != NULL)
                aux->proximo = elem->proximo;
            else
                td->elementos[index] = elem->proximo;
            free(elem->obj);
            free(elem);

            return TABDISPERSAO_OK;
        }

        aux = elem;
        elem = elem->proximo;
    }
    return TABDISPERSAO_NAOEXISTE;
}

int tabela_existe(tabela_dispersao *td, const char *chave)
{
    int index;
    td_elemento * elem;

    if (!chave || !td) return TABDISPERSAO_ERRO;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(chave, td->tamanho);

    /* percorre lista na posicao index e retorna 1 se encontrar */
    elem = td->elementos[index];

    while(elem != NULL)
    {
        if (!strcmp(elem->obj->chave, chave))
            return TABDISPERSAO_EXISTE;
        elem = elem->proximo;
    }
    return TABDISPERSAO_NAOEXISTE;
}

const char* tabela_valor(tabela_dispersao *td, const char *chave)
{
    int index;
    td_elemento * elem;

    if (!td) return NULL;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(chave, td->tamanho);

    /* percorre lista na posicao index e retorna 1 se encontrar */
    elem = td->elementos[index];

    while(elem != NULL)
    {
        if (!strcmp(elem->obj->chave, chave))
            return elem->obj->valor;
        elem = elem->proximo;
    }
    return NULL;
}

int tabela_esvazia(tabela_dispersao *td)
{
    int i;
    td_elemento * elem, * aux;

    if (!td) return TABDISPERSAO_ERRO;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* apaga todos os elementos da entrada */
        elem = td->elementos[i];
        while(elem != NULL)
        {
            aux = elem->proximo;
            free(elem->obj);
            free(elem);
            elem = aux;
        }
        td->elementos[i] = NULL;
    }
    return TABDISPERSAO_OK;
}

int tabela_numelementos(tabela_dispersao *td)
{
    int i, count = 0;
    td_elemento * elem;

    if (!td) return TABDISPERSAO_ERRO;

    /* percorre todos os elementos da tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        elem = td->elementos[i];
        while(elem != NULL)
        {
            elem = elem->proximo;
            count++;
        }
    }
    return count;
}

objeto * tabela_elementos(tabela_dispersao *td, int *n)
{
    objeto *v;
    int i, j;
    td_elemento * elem;
    objeto * valor;

    *n = tabela_numelementos(td);

    if ((*n) <= 0)
        return NULL;

    v = (objeto*) malloc(sizeof(objeto)*(*n));
    if (!v)
        return NULL;

    for (i=0,j=0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            elem = td->elementos[i];
            while (elem)
            {
                valor = elem->obj;
                v[j++] = *valor;
                elem = elem->proximo;
            }
        }
    }
    return v;
}

unsigned long hash_krm(const char* chave, int tamanho)
{
    unsigned long h, i;
    h = 7;
    i = 0;

    while(chave[i])
        h += chave[i++];

    return h % tamanho;
}

unsigned long hash_djbm(const char* chave, int tamanho)
{
    unsigned long h, i;
    i = 0;
    h = 5347;

    while(chave[i])
    {
        h *= 31;
        h ^= chave[i++];
        h &= 0xffffffff; /* consideram-se apenas 32 bits */
    }

    return h % tamanho;
}

/*================================================================================*/
void mostraTabela(tabela_dispersao *td)
{
    int i;
    td_elemento * elem;
    printf("TABELA DE DISPERSAO (%d elementos)\n", tabela_numelementos(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%s\" :: \"%s\"]", elem->obj->chave, elem->obj->valor);
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}

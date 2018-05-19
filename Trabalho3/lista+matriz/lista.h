/*****************************************************************/
/*      Biblioteca lista ligada | PROG2 | MIEEC | 2017/18        */
/*****************************************************************/

#include "terra_incognita.h"
#ifndef LISTA_H

/**
* registo para armazenar elementos da lista duplamente ligada
* este registo contem uma string e apontadores para o proximo e
* anterior elementos da lista
*/
typedef struct _tuga_ {
    int x;
    int y;
    int type;
} celula;

typedef struct _l_elemento
{
	/* valor armazenado */
	celula* valor;
	/* apontadores para elementos vizinhos */
    struct _l_elemento *proximo;
    struct _l_elemento *anterior;
} l_elemento;

typedef struct
{
	l_elemento *inicio;
	l_elemento *fim;
	int tamanho;
} lista;



#define LISTA_INICIO 0
#define LISTA_FIM 1

/**
 *  cria uma nova lista ligada vazia
 *  retorno: apontador para a lista
 *  observacao: se a lista não foi criada retorna NULL
 */
lista* lista_nova();

void lista_apaga(lista *lst);

/**
 *  insere um elemento na posicao especificada
 *  parametro: lst apontador para a lista
 *  parametro: valor string a inserir
 *  parametro: pos posicao da lista onde se pretende inserir o novo elemento,
 *             se pos=NULL insere no fim da lista
 *  retorno: apontador para novo elemento inserido na lista ou NULL se ocorrer um erro
 */
l_elemento* lista_insere(lista *lst, celula* valor, l_elemento *pos);

/**
 *  remove o elemento especificado
 *  parametro: lst apontador para a lista
 *  parametro: pos elemento que se pretende remover
 *  retorno: apontador para proximo elemento ao que foi removido ou NULL se ocorrer um erro
 */
l_elemento* lista_remove(lista *lst, l_elemento *pos);

/**
*  atribui o valor especificado a um elemento da lista
*  parametro: lst apontador para a lista
*  parametro: pos elemento onde colocar valor
*  parametro: str string pretendida
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou pos se bem sucedido
*/
int lista_atribui(lista *lst, l_elemento *pos, celula* valor);

/**
 *  devolve a posicao do primeiro elemento da lista com a string especificada
 *  parametro: lst apontador para a lista
 *  parametro: str string a pesquisar
 *  parametro: origem origem da pesquisa: a partir do início (LISTA_INICIO) ou a partir do fim (LISTA_FIM)
 *  retorno: elemento ou NULL se nao encontrar elemento ou ocorrer um erro
 */
l_elemento* lista_pesquisa(lista *lst, celula* valor, int origem);


#define LISTA_H
#endif

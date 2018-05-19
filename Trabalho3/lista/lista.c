/*****************************************************************/
/*      Biblioteca lista ligada | PROG2 | MIEEC | 2017/18        */
/*****************************************************************/

#include "lista.h"
#include <string.h>
#include <stdlib.h>
#include "terra_incognita.h"

l_elemento* novo_elemento(celula* valor)
{
	/* aloca memoria para a estrutura lista */
	l_elemento *item = (l_elemento *) malloc(sizeof(l_elemento));
	if(item == NULL)
		return NULL;

	/* aloca memoria para string */
  	item->valor = (celula *) malloc(sizeof(celula));
	if(item->valor == NULL)
	{
		free(item);
		return NULL;
	}

	/* copia valor */
	item->valor = valor;

	/* item ainda nao tem proximo */
  item->proximo = NULL;
  item->anterior = NULL;

	return item;
}

lista* lista_nova()
{
	/* cria lista */
	lista *lst = (lista*) malloc(sizeof(lista));
	if(lst == NULL)
		return NULL;

	/* lista esta' vazia */
	lst->inicio = NULL;
	lst->fim = NULL;
	lst->tamanho = 0;

  return lst;
}


void lista_apaga(lista *lst)
{
	l_elemento *aux;

	if(lst == NULL)
		return;

	/* percorre toda a lista e liberta memoria de
	   cada item e respectiva string */
	while(lst->inicio)
	{
		aux = lst->inicio;
		lst->inicio = lst->inicio->proximo;
		free(aux->valor);
		free(aux);
	}

	free(lst);
	return;
}


l_elemento* lista_elemento(lista *lst, int pos)
{
	int i;
	l_elemento *curr = NULL;

	if (lst == NULL || pos < 0 || pos >= lst->tamanho)
		return NULL;

	curr = lst->inicio;
	for(i=0; i<pos; i++)
		curr = curr->proximo;

	return curr;
}


l_elemento* lista_insere(lista *lst, celula* valor, l_elemento *pos)
{
	l_elemento *curr = NULL;

	if (lst == NULL || valor == NULL)
		return NULL;

	/* cria novo item */
	curr = novo_elemento(valor);

	if (curr == NULL)
        return NULL;

	lst->tamanho++;

	/* caso especial: inserir no fim da lista */
	if(pos == NULL)
	{
		/* se e' primeiro l_elemento */
		if (lst->inicio == NULL)
		{
			lst->inicio = lst->fim = curr;
		}
		else
		{
			curr->anterior = lst->fim;
			lst->fim->proximo = curr;
			lst->fim = curr;
		}
		return curr;
	}

	/* caso especial: inserir no inicio da lista */
	if (pos == lst->inicio)
	{
		curr->proximo = lst->inicio;
		lst->inicio->anterior = curr;
		lst->inicio = curr;
        return curr;
	}

	/* troca apontadores para inserir item */
	curr->anterior = pos->anterior;
	curr->proximo = pos;
	pos->anterior->proximo = curr;
	pos->anterior = curr;

	return curr;
}


l_elemento* lista_remove(lista *lst, l_elemento *pos)
{
	l_elemento *aux;

	if (lst == NULL || pos == NULL)
		return NULL;

	lst->tamanho--;

	/* troca apontadores para remover item */
	if(pos->anterior != NULL)
		pos->anterior->proximo = pos->proximo;
	else /* e' o primeiro */
		lst->inicio = pos->proximo;
	if(pos->proximo != NULL)
		pos->proximo->anterior = pos->anterior;
	else /* e' o ultimo */
		lst->fim = pos->anterior;

	/* liberta memoria associada ao item removido */
	aux = pos->proximo;
	free(pos->valor);
	free(pos);

	return aux;
}


int lista_atribui(lista *lst, l_elemento *pos, celula* valor)
{
	if(lst == NULL || pos == NULL || valor == NULL)
		return -1;

		/* realoca memoria para nova string */
	  pos->valor = (celula *) realloc(pos->valor, sizeof(celula));
		if(pos->valor == NULL)
			return -1;
		pos->valor = valor;

		return 0;
}


l_elemento* lista_pesquisa(lista *lst, celula* valor, int origem)
{
	l_elemento *aux;

	if(lst == NULL || valor == NULL || (origem != LISTA_INICIO && origem != LISTA_FIM))
		return NULL;

	if(origem == LISTA_INICIO)
	{
		/* pesquisa sequencial: a partir do inicio */
		for (aux = lst->inicio; aux != NULL; aux = aux->proximo)
		{
			if (aux->valor == valor)
			{
				return aux;
			}
		}
		return NULL;
	}

	/* pesquisa sequencial: a partir do fim */
	for (aux = lst->fim; aux != NULL; aux = aux->anterior)
	{
		if (aux->valor == valor)
		{
			return aux;
		}
	}
	return NULL;
}

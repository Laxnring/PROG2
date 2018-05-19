/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
DESCRIPTION: Troca pai e filho numa heap
INPUTS: 
  -> heap
  -> pai 
  -> filho
RETURN: NONE
*/
void heap_swap (heap* h, int pai, int filho){
  
  elemento* aux;

  aux = h->elementos[filho];
  h->elementos[filho] = h->elementos[pai];
  h->elementos[pai] = aux;
}

heap* heap_nova(int capacidade)
{
  if (capacidade < 0) {
    return NULL;
  }

  heap *nova_heap;

  nova_heap = (heap*)malloc(sizeof(heap));
  if (nova_heap == NULL) {
    return NULL;
  }

  nova_heap->capacidade = capacidade;
  nova_heap->elementos = (elemento**)malloc(sizeof(elemento) * (capacidade));
  if (nova_heap->elementos == NULL) {
    return NULL;
  }
  nova_heap->tamanho = 0;
  
  return nova_heap;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
  int i;
  elemento *aux;
  if (!h || !texto || h->tamanho == h->capacidade) {
    return 0;
  }
  
  h->tamanho++;
  aux = (elemento*)malloc(sizeof(elemento));
  if (!aux) return 0;

  aux->valor = (char*)malloc(strlen(texto)+1);
  if (!aux->valor) return 0;

  strcpy(aux->valor, texto);
  aux->prioridade = prioridade;
  
  for (i = h->tamanho; i > 1 && h->elementos[i/2]->prioridade > prioridade; i /= 2) {
    h->elementos[i] = h->elementos[i/2];
  }
  
  h->elementos[i] = aux;

  return 1;
}

void heap_apaga(heap *h)
{
  int i;
  if (!h) {
    return;
  }

  for (i = 1; i <= h->tamanho; i++) {
    free(h->elementos[i]->valor);
    free(h->elementos[i]);
  }

  free(h->elementos);
  free(h);
  return;
}

char* heap_remove(heap * h)
{
  if (!h || !h->tamanho) {
    return NULL;
  }

  int i = 1, flag = 1;

  elemento* aux,*keep;
  keep = (elemento*)malloc(sizeof(elemento));
  if (!keep) 
    return NULL;

  keep->valor = (char*)malloc(sizeof(char)*strlen(h->elementos[1]->valor)+1);
  
  if (!keep->valor)
    return NULL;

  aux = h->elementos[h->tamanho];
  strcpy (keep->valor, h->elementos[1]->valor);

  free(h->elementos[1]->valor);
  free(h->elementos[1]);

  h->elementos[h->tamanho] = NULL;
  h->tamanho--;
  
  if(!h->tamanho){
    return keep->valor;
  }

  for(i = 2; i < h->tamanho; i = i*2){
    if(h->elementos[i] == NULL && h->elementos[i+1] == NULL){
      break;
    }
    if(h->elementos[i]->prioridade < h->elementos[i+1]->prioridade && h->elementos[i+1] != NULL){
      if(aux->prioridade < h->elementos[i]->prioridade){
        h->elementos[i/2] = aux;
        flag = 0;
        break;
      }
      h->elementos[i/2] = h->elementos[i];
    }
  
    else if(h->elementos[i+1]->prioridade < h->elementos[i]->prioridade && h->elementos[i+1] != NULL){
      if(aux->prioridade < h->elementos[i+1]->prioridade){
        h->elementos[i/2] = aux;
        flag = 0;
        break;
      }
      h->elementos[i/2] = h->elementos[i+1];
      i++;
    }
  }

  if(flag == 1){
    h->elementos[i/2] = aux;
  }
  
  return keep->valor;
}


heap* heap_constroi(elemento* v, int n_elementos)
{
  if (!v || !v->valor || n_elementos < 0) {
    return NULL;
  }

  heap *h;
  int i, res;
  
  h = heap_nova(n_elementos);
  if (!h) {
    return NULL;
  }

  for (i = 0; i < n_elementos; i++) {
    res = heap_insere(h, v[i].valor, v[i].prioridade); 
    if (!res) return NULL;  
  }
  return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
  if(!h || indice < 1) {
    return -1;
  }
  int i;

  h->elementos[indice]->prioridade = nova_prioridade;

  for(i = indice; i > 1 && nova_prioridade < h->elementos[i/2]->prioridade; i = i/2){
    if(h->elementos[i]->prioridade < h->elementos[i/2]->prioridade){
      heap_swap(h,i/2,i);
    }
  }
  if(nova_prioridade > h->elementos[indice/2]->prioridade) {
    for(int i=indice*2; i< h->tamanho; i = i*2) {

      if(h->elementos[i] == NULL && h->elementos[i+1] == NULL) {
        break;
      }
      if(h->elementos[i]->prioridade < h->elementos[i+1]->prioridade) {
        if(h->elementos[i/2]->prioridade > h->elementos[i]->prioridade) {
          heap_swap(h,i/2,i);      
        }
      }
      else if(h->elementos[i]->prioridade > h->elementos[i+1]->prioridade) {
        if(h->elementos[i/2]->prioridade > h->elementos[i+1]->prioridade) {
          heap_swap(h,i/2,i+1);
          i++;
        }
      }
    }
  } 
  return 1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;
  
  if (indice <= h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    mostraHeap(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);
    
    mostraHeap(h, indice*2+1);
  }
}


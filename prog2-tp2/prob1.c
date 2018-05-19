#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <time.h>

void ordena_lista(lista *lst, int n) {
  int passo, i;
  l_elemento *curr, *imin, *next;
  char *aux;

  for(curr = lst->inicio; curr->proximo != NULL; curr = curr->proximo) {
    imin = curr;
    next = curr->proximo;
    while (next != NULL) {
      if (strcmp(next->str, imin->str) < 0)
         imin = curr;
      next = next->proximo;
    } 
    if (imin != curr) {
      aux = curr->str;
      curr->str = imin->str;
      imin->str = aux;
    } 
  }
}


int main() {
  FILE *f, *fp;
  char str[100];
  lista *jogos, *lista_sem, *oldies, *lista_junta;
  l_elemento *posicao, *pesquisa;
  l_elemento *iterador;
  int contador = 0;
  int i = 0, j, numero_jogos;

  f = fopen("arquivo.txt", "r");
  fp = fopen("oldies.txt", "r");

  jogos = lista_nova();
  lista_sem = lista_nova();
  oldies = lista_nova();
  lista_junta = lista_nova();

  while(fgets(str, sizeof(str), f) != NULL) {
    lista_insere(jogos, str, NULL);
  }
  while(fgets(str, sizeof(str), fp) != NULL) {
    lista_insere(oldies, str, NULL);
  }

  posicao = jogos->inicio;

  //printf("Foram lidos %d jogos\n", numero_jogos);
  //lista_imprime(jogos);

  lista_sem = lista_pesquisa_substring(jogos, "PS2");
  posicao = jogos->inicio;
  for (i = 0; i < lista_sem->tamanho; i++) {
    if (lista_pesquisa(jogos, posicao->str, LISTA_INICIO) != NULL) {
      lista_remove(jogos, posicao);
    }
    posicao = posicao->proximo;
  }
  //lista_imprime(jogos);
  lista_junta = lista_concatena(jogos, oldies);
  //lista_imprime(lista_junta);
  lista_ordena(lista_junta);
  //lista_imprime(lista_junta);

  pesquisa = lista_pesquisa(lista_junta, "L.A. Noire (PC)", LISTA_INICIO);
  //
lista_imprime(lista_junta);
  if (pesquisa != NULL) {
    printf("%d", sizeof(pesquisa));
  
  for (iterador = lista_junta->inicio; iterador != NULL; iterador = iterador->proximo) {
    if (strcmp(iterador->str, pesquisa->str) == 0) {
      printf("O jogo foi encontrado na posição %d", contador);
      break;
    } else contador++;
  }
  }
  if (contador == lista_junta->tamanho) printf("Nao foi encontrado");
  return 0;
}
